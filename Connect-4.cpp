#include <iostream>
using namespace std;

class Grid
{
    private:
    enum Direction
    {
        horizontal,
        vertical,
        backdiagonal,
        frontdiagonal
    };
    int matrix[7][6] = {0};
    int total = 0;
    struct Position
    {
        int row;
        int col;
    }pos;

    public:

        //Displays the matrix for the user.
        void MatrixDisplay()
        { 
            cout<<"_______________"<<endl;
            for(int i=5; i>=0; i--)
            {
                cout<<"|";
                for(int j=0; j<7; j++)
                {
                    switch(matrix[j][i])
                    {
                        case 0: cout<<" ";
                            break;
                        case 1: cout<<"\033[1;31mR\033[0m";
                            break;
                        case 2: cout<<"\033[1;34mB\033[0m";
                            break;
                        case 3: cout<<"\033[1;32mR\033[0m";
                            break;
                        case 4: cout<<"\033[1;32mB\033[0m";
                            break;
                    }  
                    cout<<"|";
                }
                cout<<endl;
            }
            cout<<"|1|2|3|4|5|6|7|"<<endl;
            cout<<"_______________"<<endl;
            cout<<endl;
        }

        //Getter for position
        Position GetPos(){
            return pos;
        }

        //Checks if there is a vacancy in the specified column
        bool VacancyCheck(int row)
        {
            if(matrix[row-1][5] == 0)
            {
                return true;
            }
            else 
            {
                return false;
            }
        }

        //adding an element
        void Admission(int row, int value)
        {
            for(int i=0; i<6; i++)
            {
                if(matrix[row-1][i] == 0)
                {
                    matrix[row-1][i] = value;
                    pos.row = row-1;
                    pos.col = i;
                    total++;
                    return;
                }
            }
        }

        //Win Condition Check
        bool WinCheck(int value)
        {
            if(HoriSearch(value)){return true;}
            if(VertiSearch(value)){return true;}
            if(BackDiagSearch(value)){return true;}
            if(FrontDiagSearch(value)){return true;}
            return false;
        }

        //Draw Check
        bool IsDraw()
        {
            if(total<42){return false;}
            else {return true;}
        }

        //Horizontal search : I traverse the horizontal line of currently added element
        bool HoriSearch(int value)
        {
            int col = pos.col;

            int count = 0;
            for(int i= 0; i<7; i++)
            {
                if(matrix[i][col] == value)
                {
                    count++;
                    if(count == 4){
                        matrix[i][col] = value+2;
                        matrix[i-1][col] = value+2;
                        matrix[i-2][col] = value+2;
                        matrix[i-3][col] = value+2;
                        return true;}
                }
                else
                {
                    count = 0;
                }
            }
            return false;
        }

        //Vertical search : I traverse the vertical line of currently added element
        bool VertiSearch(int value)
        {
            int row = pos.row;

            int count = 0;
            for(int i= 0; i<6; i++)
            {
                if(matrix[row][i] == value)
                {
                    count++;
                    if(count == 4){
                        matrix[row][i] = value+2;
                        matrix[row][i-1] = value+2;
                        matrix[row][i-2] = value+2;
                        matrix[row][i-3] = value+2;
                        return true;}
                }
                else
                {
                    count = 0;
                }
            }
            return false;
        }

        //BackDiagonal Search: diagonal that looks like "\"
        bool BackDiagSearch(int value)
        {
            int diagSum = pos.row + pos.col;
            int count = 0;
            int j=min(diagSum,5);
            int i =diagSum - j;
            for(; j>=0 && i<7; j--,i++)
            {
                if(matrix[i][j] == value)
                {
                    count++;
                    if(count == 4){
                        matrix[i][j] = value+2;
                        matrix[i-1][j+1] = value+2;
                        matrix[i-2][j+2] = value+2;
                        matrix[i-3][j+3] = value+2;
                        return true;}
                }
                else
                {
                    count = 0;
                }
            }
            return false;
        }

        //FrontDiagonal Search: diagonal that looks like "/"
        bool FrontDiagSearch(int value)
        {
            int diagSum = 6 - pos.row + pos.col;
            int count = 0;
            int j=min(diagSum,5);
            int i= diagSum-j;
            for(; j>=0 && i<7; j--,i++)
            {
                if(matrix[6 - i][j] == value)
                {
                    count++;
                    if(count == 4){
                        matrix[6-i][j] = value+2;
                        matrix[7-i][j+1] = value+2;
                        matrix[8-i][j+2] = value+2;
                        matrix[9-i][j+3] = value+2;
                        return true;}
                }
                else
                {
                    count = 0;
                }
            }
            return false;
        }
        
};

class Gameplay : Grid
{
    private:
        enum GameState
        {
            redWin,
            blueWin,
            draw
        };
    public:

        void endMessage()
        {
            cout<<endl;
            cout<<"+-------------------------------------------+"<<endl;
            cout<<"|                 GAME ENDS                 |"<<endl;
            cout<<"|                 THANK YOU                 |"<<endl;
            cout<<"|              SEE YOU NEXT TIME            |"<<endl;
            cout<<"+-------------------------------------------+"<<endl;
            
        }

        bool rulesMessage()
        {
            char input;
            cout<<endl;
            cout<<"RULES:"<<endl<<endl;
            cout<<"1. Two-player (red(R) & blue(B)) game."<<endl;
            cout<<"2. Board size is 6 rows and 7 columns."<<endl;
            cout<<"3. A Player wins if he/she is able to connect 4 dots horizontally,"
                    " vertically or diagonally."<<endl;
            cout<<"4. Game is a Draw when the board is completely filled."<<endl;
            cout<<endl;
            cout<<"HOW TO PLAY:"<<endl<<endl;
            cout<<"1. Game always starts with player-1 i.e. Red(R)."<<endl;
            cout<<"2. In each step, choose the column number in which "
                    "you want to drop the coin."<<endl;
            cout<<"3. Rows will be filled from botton to top in any column."<<endl;
            cout<<endl<<endl;
            cout<<"ARE YOU READY TO PLAY (Y/N):"<<endl;
            
            cin>>input;
            system("clear");
            if(input=='Y' || input=='y'){return true;}
            else {return false;}
        }

        void welcomeMessage()
        {
            cout<<endl<<endl;
            cout<<"+-------------------------------------------+"<<endl;
            cout<<"|                GAME STARTS                |"<<endl;
            cout<<"+-------------------------------------------+"<<endl<<endl;
            cout<<"WELCOME TO CONNECT-4 !!!"<<endl<<endl;
            cout<<"PRESS ENTER TO CONTINUE:"<<endl;
            cin.ignore();
            getchar();
            system("clear");
        }

        void winMessage(GameState state)
        {
            string s;
            switch(state)
            {
                case redWin: s = " RED WON ";
                break;
                case blueWin: s = "BLUE WON ";
                break;
                case draw: s = "GAME DRAW";
                break;
            }
            cout<<"+-------------------------------------------+"<<endl;
            cout<<"|                	"<<s<<"               |"<<endl;
            cout<<"+-------------------------------------------+"<<endl<<endl;
            endMessage();
        }

        GameState gameMain()
        {
            int input;
            bool isDraw;
            do
            {
                //Red Move
                MatrixDisplay();
                cout<<"\033[1;31mRed(R)\033[0m: Please Enter the column number: ";
                cin>>input;
                cout<<endl;
                while(!VacancyCheck(input))
                {
                    cout<<"Column not available. Enter a different column: ";
                    cin>>input;
                    cout<<endl;
                }
                Admission(input, 1);
                system("clear");
                if(WinCheck(1))
                {
                    MatrixDisplay();
                    return redWin;
                }
                //------------------------------------------------------------

                //Blue Move
                MatrixDisplay();
                cout<<"\033[1;34mBlue(B)\033[0m: Please Enter the column number: ";
                cin>>input;
                cout<<endl;
                while(!VacancyCheck(input))
                {
                    cout<<"Column not available. Enter a different column: ";
                    cin>>input;
                    cout<<endl;
                }
                Admission(input, 2); 
                system("clear");
                if(WinCheck(2))
                {
                    MatrixDisplay();
                    return blueWin;
                }
                isDraw = IsDraw();
                
            }while(!isDraw);
            return draw;
        }
      
};

int main() 
{
    Gameplay g; 
    if(!g.rulesMessage())
    {
        g.endMessage();
        return 0;
    }
    g.welcomeMessage();
    g.winMessage(g.gameMain()); 
}
