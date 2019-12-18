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
typedef  int /*<<< orphan*/  uint8 ;

/* Variables and functions */
 int /*<<< orphan*/  ButtonConfigBegin () ; 
 int /*<<< orphan*/  ButtonConfigEnd () ; 
#define  FCFGD_GAMEPAD 131 
#define  FCFGD_HYPERSHOT 130 
#define  FCFGD_POWERPAD 129 
#define  FCFGD_QUIZKING 128 
 int /*<<< orphan*/ ** GamePadConfig ; 
 int /*<<< orphan*/ * HyperShotButtons ; 
 int /*<<< orphan*/ * QuizKingButtons ; 
 int /*<<< orphan*/ ** powerpadsc ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  subcon (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ConfigDevice(int which, int arg)
{
 uint8 buf[256];
 int x;

 ButtonConfigBegin();
 switch(which)
 {
  case FCFGD_QUIZKING:
   for(x=0;x<6;x++)
   {
    sprintf(buf,"Quiz King Buzzer #%d", x+1);
    subcon(buf,&QuizKingButtons[x]);
   }
   break;
  case FCFGD_HYPERSHOT:
   for(x=0;x<4;x++)
   {
    sprintf(buf,"Hyper Shot %d: %s",((x&2)>>1)+1,(x&1)?"JUMP":"RUN");
    subcon(buf,&HyperShotButtons[x]);
   } 
   break;
  case FCFGD_POWERPAD:
   for(x=0;x<12;x++)
   {
    sprintf(buf,"PowerPad %d: %d", (arg&1)+1,x+11);
    subcon(buf,&powerpadsc[arg&1][x]);
   }
   break;

  case FCFGD_GAMEPAD:
  {
   char *str[10]={"A","B","SELECT","START","UP","DOWN","LEFT","RIGHT","Rapid A","Rapid B"};
   for(x=0;x<10;x++)
   {
    sprintf(buf,"GamePad #%d: %s",arg+1,str[x]);
    subcon(buf,&GamePadConfig[arg][x]);
   }
  }
  break;
 }

 ButtonConfigEnd();
}