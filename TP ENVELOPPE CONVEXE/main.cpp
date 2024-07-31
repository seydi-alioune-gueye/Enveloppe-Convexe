#include <iostream>
#include <vector>
#include "graphics.h"
#include <ctime>
#include <cstdlib>
#define H 600
#define L 800

using namespace std;

struct Point
{
int x, y;
};

void trace(const Point &p){
   plot(p.x, H-p.y);
}

void trace(const Point &a, const Point &b){
    line(a.x,H-a.y,b.x,H-b.y);
}

void tracePoints(const vector<Point> &T){
     for(int i=0;i<T.size();i++){
        trace(T[i]);
    }
}

void traceLigne(const vector<Point> &T){
    int i;
  for(i=0;i<T.size()-1;i++){
        trace(T[i],T[i+1]);
    }
   // trace(T[i-1],T[0]);
}

vector<Point> saisieDespoints(){
  /*  int nbrDePoints;
    cout<<"Veuillez indiquez le nombre de points necessaire : ";
    cin>>nbrDePoints;*/
    vector<Point>tab(10);
    for(int i=0;i<tab.size();i++){
        tab[i].x=((rand() * (500 - 10)/RAND_MAX)) + 10;
        tab[i].y=((rand() * (500 - 10)/RAND_MAX)) + 10;
    }
    return tab;

}

/*int *tableauPoints(const vector<Point> &tab){
   int n=2*tab.size();
   int t[n],
   j=0;
   for(int i=0;i<tab.size();i+=2){
    t[j]=tab[i].x;
    j++;
    t[j]=tab[i+1].y;
    j++;
   }
   return t;
}*/

void affichage(const vector<Point>&tab){
    cout<<"# POINTS DE L'ENVELOPPE CONVEXE #"<<endl;
    for(int i=0;i<tab.size();i++){
        cout<<"("<<tab[i].x<<","<<tab[i].y<<")"<<"\t";
    }
    cout<<"\n";
}

bool estInferieur(const Point &a, const Point &b){
 return (a.x<b.x);
}

void tri(vector<Point> &T)
{
    for (int i=1; i<T.size(); i++)
    {
        Point aux = T[i];
         int j = i-1;
        while (j>=0 && estInferieur(T[j],aux))
        {
            T[j+1] = T[j];
            j--;
        }
        T[j+1] = aux;
    }
}

int aGauche(const Point &a, const Point &b, const Point &c){
    int determinant = (b.x - a.x)*(c.y - a.y) - (c.x - a.x)*(b.y - a.y);
    if (determinant == 0)
        return 0;
    else
        return determinant > 0 ? 1 : -1;
}

void enveloppe(vector<Point> &T, vector<Point> &envSup,
vector<Point> &envInf) {
   for(int i=0;i<=T.size()-1;i++){
    while(envSup.size() > 1 && aGauche(envSup.back(),envSup[envSup.size()-2],T[i])==-1)
    envSup.pop_back();
    envSup.push_back(T[i]);
   while(envInf.size() > 1 && aGauche(envInf.back(),envInf[envInf.size()-2],T[i])==1)
    envInf.pop_back();
    envInf.push_back(T[i]);
   }
}
//#######################################################################################

void Dragon(int n, vector<bool> &code)
{
     code.push_back(false);
     //vue qu'on a ajouter false donc on commence par 2
    for(int i=2;i<=n;i++)
    {
        code.push_back(false);
        for(int j=code.size()-2 ;j>=0;j--)
        {
           code.push_back(!code[j]);
        }
    }
}
void nouvellexy(int &x,int &y,int direction,int longueur)
{
    if(direction==0)
      {
        x+=longueur;
      }
     if(direction==1)
       {
         y-=longueur;
       }
     if(direction==2)
       {
          x-=longueur;
       }
     if(direction==3)
       {
         y+=longueur;
       }
}
void tracedragon( const vector<bool> &code, int x, int y,int direction, int longueur, int couleur )
{
    setcolor(couleur);
    moveto(x,y);
    nouvellexy(x,y, direction,longueur);
    lineto(x,y);

    for(int i=0 ;i<code.size();i++)
    {
        if(code[i]==false)
        {
            direction++;
            if(direction==4)
                direction=0;
        }
        else
        {
            direction--;
            if(direction==-1)
                direction=3;
        }


        nouvellexy(x,y,direction, longueur);
        lineto(x,y);

    }
}
void afficheCode(const vector<bool> &code)
{
    for(int i=0;i<code.size();i++)
    {
        cout<<code[i];
    }
}
void test()
{
    vector<bool> code;
    Dragon(15,code);
//    afficheCode(code);
    tracedragon(code, 900, 450,0, 1, RED);


}



int main()
{
    /*srand(time(0));
    opengraphsize(L,H);
    setbkcolor(BLACK);
    cleardevice();
    setcolor(WHITE);
    vector<Point> envSup;
    vector<Point> envInf;
    vector<Point>points=saisieDespoints();
    tri(points);
    enveloppe(points,envSup,envInf);
    affichage(envSup);
    affichage(envInf);
    traceLigne(envSup);
    traceLigne(envInf);
    getch();
    closegraph();*/


    opengraphsize(1800,900);
    cleardevice();
    //setcolor(BLUE);
    test();
    getch();
    closegraph();


    return 0;
}
