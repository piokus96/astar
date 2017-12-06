#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdio>

using namespace std;

int maps[20][20];
int steps[20][20];
int been[20][20];
int test[20][20];
int posX=19,posY=0;
int wayUp,wayDown,wayRight,wayLeft;

double heuristic(int i,int j)
{
    return floorf(sqrt((0 - i)*(0 - i) + (19 - j)*(19 - j)));
}
void canWeMove()
{
    double heurResult;
    wayUp=0;wayDown=0;wayRight=0;wayLeft=0;
    int temp=steps[posX][posY];
    been[posX][posY]=1;
    if(maps[posX-1][posY]==0 && posX>0 && been[posX-1][posY]==0 )
    {
        wayUp=1;
        heurResult = heuristic(posX-1,posY);
        steps[posX-1][posY]=temp+1+heurResult;
        been[posX-1][posY]=2;

    }
    if(maps[posX][posY+1]==0 && posY<19 && been[posX][posY+1]==0 )
    {
        wayRight=1;
        heurResult=heuristic(posX,posY+1);
        steps[posX][posY+1]=temp+1+heurResult;
        been[posX][posY+1]=2;
    }
    if(maps[posX+1][posY]==0 && posX<19 && been[posX+1][posY]==0)
    {
        wayDown=1;
        heurResult=heuristic(posX+1,posY);
        steps[posX+1][posY]=temp+1+heurResult;
        been[posX+1][posY]=2;
    }
    if(maps[posX][posY-1]==0 && posY>0 && been[posX][posY-1]==0)
    {
        wayLeft=1;
        heurResult=heuristic(posX,posY-1);
        steps[posX][posY-1]=temp+1+heurResult;
        been[posX][posY-1]=2;
    }
}
void Move()
{
    for (int k=0;k<20;k++)
    for (int i=0;i<20;i++)
    {
        for(int j=0;j<20;j++)
        {
            if (been[i][j]==2)
            {
                posX = i;
                posY = j;
                canWeMove();
            }
        }
    }
    posX = 0;
    posY = 19;
    int minimal=steps[posX][posY];
    //while(maps[19][0]!=3)
    for (int k=0;k<50;k++)
    {
        minimal=steps[posX][posY];
        if(steps[posX-1][posY] < minimal && posX>0 && steps[posX-1][posY]!=0)
        {
            minimal=steps[posX-1][posY];
            maps[posX-1][posY] = 3;
            posX--;
        }
        if(steps[posX][posY+1] < minimal && posY<19 && steps[posX][posY+1]!=0)
        {
            minimal=steps[posX][posY+1];
            maps[posX][posY+1] = 3;
            posY++;
        }
        if(steps[posX][posY-1] < minimal && posY>0 && steps[posX][posY-1]!=0)
        {
            minimal=steps[posX][posY-1];
            maps[posX][posY-1] = 3;
            posY--;
        }
        if(steps[posX+1][posY] < minimal && posX<19 && steps[posX+1][posY]!=0)
        {
            minimal=steps[posX+1][posY];
            maps[posX+1][posY] = 3;
            posX++;
        }
    }

}
void showCost()
{
    cout << endl;
    for (int i=0;i<20;i++)
    {
        for(int j=0;j<20;j++)
        {
            if(steps[i][j]<10)cout << steps[i][j] << "  ";
            else cout << steps[i][j] << " ";
        }
        cout << endl;
    }
}
void showTest()
{
    cout << endl;
    for (int i=0;i<20;i++)
    {
        for(int j=0;j<20;j++)
        {
            if(test[i][j]<10)cout << test[i][j] << "  ";
            else cout << test[i][j] << " ";
        }
        cout << endl;
    }
}
void showMaps()
{
    cout << endl;
    for (int i=0;i<20;i++)
    {
        for(int j=0;j<20;j++)
        {
            cout << maps[i][j];
        }
        cout << endl;
    }
}

int main()
{
    fstream file;
    file.open("grid.txt", ios :: in);
    for (int i=0;i<20;i++)
    {
        for(int j=0;j<20;j++)
        {
            file >> maps[i][j];
            cout << maps[i][j];
        }
        cout << endl;
    }
    file.close();

    steps[posX][posY]=0;
    been[19][0]=1;
    //canWeMove();
    canWeMove();
    Move();
    maps[19][0] = 3;
    maps[0][19] = 3;
    showCost();
    showMaps();

    return 0;
}
