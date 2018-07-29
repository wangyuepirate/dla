#include "neillncurses.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define XC 50
#define YC 50
#define XLEFT 0 
#define XRIGHT 49
#define YABOVE 0 
#define YBELOW 49 
#define DIRECTION 4
#define SIDES 4
#define PARTICLES 250



void DLAinitial(char c[XC][YC]);
void release(int *px,int *py);
void wander(int *px,int *py);
int adjacent(int px,int py,char c[XC][YC]);

int main(void)
{

   char grid[XC][YC];
   int n;/*the sum of particles*/
   int xf,yf;/*x first,y first*/
   srand(time(0));
  NCURS_Simplewin sw;

  DLAinitial(grid);
   n=0;
   while((n<PARTICLES)&&(!sw.finished)){
      release(&xf,&yf);
      do{
         wander(&xf,&yf);
      }while(adjacent(xf,yf,grid)==0);
      grid[yf][xf]='#';
      n++;
    Neill_NCURS_Init(&sw);
  Neill_NCURS_CharStyle(&sw, "#", COLOR_RED, COLOR_BLACK, A_NORMAL);
  Neill_NCURS_CharStyle(&sw, " ", COLOR_BLACK, COLOR_BLACK, A_BOLD | A_ALTCHARSET);
  
     Neill_NCURS_PrintArray(&grid[0][0], XC, YC, &sw);
     Neill_NCURS_Delay(50.0);
     Neill_NCURS_Events(&sw);
  
 
  }
  atexit(Neill_NCURS_Done);
  exit(EXIT_SUCCESS);
   }






void DLAinitial(char c[XC][YC]){
   int i,j;
   int xcenter,ycenter;
   xcenter=XC/2;
   ycenter=YC/2;
   for(i=0;i<YC;i++){
      for(j=0;j<XC;j++){
      c[i][j]=' ';
      }
   }
   c[xcenter][ycenter]='#';
}




void release(int *px,int *py){
   int side,loc;
   side=rand()%SIDES;
   loc=rand()%XC;
   if(side==0){
      *py=YABOVE;
      *px=loc; 
   }
   if(side==1){
      *py=loc;
      *px=XRIGHT;
   }
   if(side==2){
      *py=YBELOW;
      *px=loc;
   }
   if(side==3){
      *py=loc;
      *px=XLEFT;
   }
}


void wander(int *px,int *py){
   int move;
   move=rand()%DIRECTION;
   switch(move){/*the former location is [py][px]*/
   case 0:
      (*px)++;/*right*/
      break;
   case 1:
      (*px)--;/*left*/
      break;
   case 2:
      (*py)--;/*up*/
      break;
   case 3:
      (*py)++;/*down*/
      break;
   default:
      break;
   } 

   if(*px<XLEFT){
      *px=XRIGHT;
   }
   if(*px>XRIGHT){
      *px=XLEFT;
   }
   if(*py<YABOVE){
      *py=YBELOW;
   }
   if(*py>YBELOW){
      *py=YABOVE;
   }
}





int adjacent(int px,int py,char c[XC][YC]){
   int xn,yn;
   xn=px+1;
   if(xn>XRIGHT){
      xn=XLEFT;
   }
   if(c[py][xn]=='#'){
      return 1;/*right*/
   }

   xn=px-1;
   if(xn<XLEFT){
      xn=XRIGHT;
   }
   if(c[py][xn]=='#'){
      return 1;/*left*/
   }

   yn=py+1;
   if(yn>YBELOW){
      yn=YABOVE;
   }
   if(c[yn][px]=='#'){
      return 1;/*down*/
   }

   yn=py-1;
   if(yn<YABOVE){
      yn=YBELOW;
   }
   if(c[yn][px]=='#'){
      return 1;/*up*/
   }

   return 0;
}




















