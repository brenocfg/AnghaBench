#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  BACKGROUND ; 
 int SelectItem (char*,int*,int /*<<< orphan*/ ,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int choosekey (char*,int) ; 
 char** keynames ; 
 int** keysets ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

void setupkeyset(int no)
{
  int select,key,i;
  int keyset[9];
  char tUL[80],tU[80],tUR[80],tL[80],tR[80],tDL[80],tDR[80],tD[80],tF[80];

  for (i=0;i<9;i++) keyset[i]=keysets[no][i];
  select=0;
  do{
    sprintf(tF,"Fire: %s",keynames[keyset[0]]);
    sprintf(tDL,"Down+left: %s",keynames[keyset[1]]);
    sprintf(tD,"Down: %s",keynames[keyset[2]]);
    sprintf(tDR,"Down+right: %s",keynames[keyset[3]]);
    sprintf(tL,"Left: %s",keynames[keyset[4]]);
    sprintf(tR,"Right: %s",keynames[keyset[5]]);
    sprintf(tUL,"Up+left: %s",keynames[keyset[6]]);
    sprintf(tU,"Up: %s",keynames[keyset[7]]);
    sprintf(tUR,"Up+right: %s",keynames[keyset[8]]);

    key=SelectItem("Change settings:",&select,BACKGROUND,
        tUL,tU,tUR,tL,tR,tDL,tD,tDR,tF,"-","Clear all","-",
        "Accept changes",
        "Discard changes",NULL);
    if (key==13)
      switch(select)
      {
        case 0:keyset[6]=choosekey("up+left",keyset[6]);select++;break;
        case 1:keyset[7]=choosekey("up",keyset[7]);select++;break;
        case 2:keyset[8]=choosekey("up+right",keyset[8]);select++;break;
        case 3:keyset[4]=choosekey("left",keyset[4]);select++;break;
        case 4:keyset[5]=choosekey("right",keyset[5]);select++;break;
        case 5:keyset[1]=choosekey("down+left",keyset[1]);select++;break;
        case 6:keyset[2]=choosekey("down",keyset[2]);select++;break;
        case 7:keyset[3]=choosekey("down+right",keyset[3]);select++;break;
        case 8:keyset[0]=choosekey("fire",keyset[0]);break;
        case 10:for (i=0;i<9;i++) keyset[i]=255;break;
      }
  }while (key!=27 && !(key==13 && select>11));
  if (key==13 && select==12)
    for (i=0;i<9;i++) keysets[no][i]=keyset[i];
}