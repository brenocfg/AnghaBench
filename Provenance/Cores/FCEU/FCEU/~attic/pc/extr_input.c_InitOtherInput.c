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
 void* BWorldData ; 
 int EO_NOFOURSCORE ; 
 int /*<<< orphan*/  FCEUI_DisableFourScore (int) ; 
 int /*<<< orphan*/  FCEUI_SetInput (int,int,void*,int) ; 
 int /*<<< orphan*/  FCEUI_SetInputFC (int,void*,int) ; 
 int /*<<< orphan*/  FTrainerData ; 
 int /*<<< orphan*/  HyperShotData ; 
 int /*<<< orphan*/  InitMouse () ; 
 int* InputType ; 
 int /*<<< orphan*/  JSreturn ; 
 int /*<<< orphan*/  MahjongData ; 
 void* MouseData ; 
 int /*<<< orphan*/  QuizKingData ; 
#define  SIFC_ARKANOID 143 
#define  SIFC_BWORLD 142 
#define  SIFC_FKB 141 
#define  SIFC_FTRAINERA 140 
#define  SIFC_FTRAINERB 139 
#define  SIFC_HYPERSHOT 138 
#define  SIFC_MAHJONG 137 
#define  SIFC_OEKAKIDS 136 
#define  SIFC_QUIZKING 135 
#define  SIFC_SHADOW 134 
#define  SIFC_TOPRIDER 133 
#define  SI_ARKANOID 132 
#define  SI_GAMEPAD 131 
#define  SI_POWERPADA 130 
#define  SI_POWERPADB 129 
#define  SI_ZAPPER 128 
 int /*<<< orphan*/  TopRiderData ; 
 int eoptions ; 
 void* fkbkeys ; 
 int /*<<< orphan*/ * powerpadbuf ; 

void InitOtherInput(void)
{
   void *InputDPtr;

   int t;
   int x;
   int attrib;

   for(t=0,x=0;x<2;x++)
   {
    attrib=0;
    InputDPtr=0;
    switch(InputType[x])
    {
     case SI_POWERPADA:
     case SI_POWERPADB:InputDPtr=&powerpadbuf[x];break;
     case SI_GAMEPAD:InputDPtr=&JSreturn;break;     
     case SI_ARKANOID:InputDPtr=MouseData;t|=1;break;
     case SI_ZAPPER:InputDPtr=MouseData;
                                t|=1;
                                attrib=1;
                                break;
    }
    FCEUI_SetInput(x,InputType[x],InputDPtr,attrib);
   }

   attrib=0;
   InputDPtr=0;
   switch(InputType[2])
   {
    case SIFC_SHADOW:InputDPtr=MouseData;t|=1;attrib=1;break;
    case SIFC_OEKAKIDS:InputDPtr=MouseData;t|=1;attrib=1;break;
    case SIFC_ARKANOID:InputDPtr=MouseData;t|=1;break;
    case SIFC_FKB:InputDPtr=fkbkeys;break;
    case SIFC_HYPERSHOT:InputDPtr=&HyperShotData;break;
    case SIFC_MAHJONG:InputDPtr=&MahjongData;break;
    case SIFC_QUIZKING:InputDPtr=&QuizKingData;break;
    case SIFC_TOPRIDER:InputDPtr=&TopRiderData;break;
    case SIFC_BWORLD:InputDPtr=BWorldData;break;
    case SIFC_FTRAINERA:
    case SIFC_FTRAINERB:InputDPtr=&FTrainerData;break;
   }

   FCEUI_SetInputFC(InputType[2],InputDPtr,attrib);
   FCEUI_DisableFourScore(eoptions&EO_NOFOURSCORE);

   if(t) 
    InitMouse();
}