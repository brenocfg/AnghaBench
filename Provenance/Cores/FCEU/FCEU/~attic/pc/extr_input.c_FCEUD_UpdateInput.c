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
 int /*<<< orphan*/  GetMouseData (int /*<<< orphan*/ ) ; 
 int* InputType ; 
 int /*<<< orphan*/  KeyboardCommands () ; 
 int /*<<< orphan*/  MouseData ; 
#define  SIFC_ARKANOID 142 
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
 int /*<<< orphan*/  UpdateFKB () ; 
 int /*<<< orphan*/  UpdateFTrainer () ; 
 int /*<<< orphan*/  UpdateGamepad () ; 
 int /*<<< orphan*/  UpdateHyperShot () ; 
 int /*<<< orphan*/  UpdateMahjong () ; 
 int /*<<< orphan*/  UpdatePPadData (int) ; 
 int /*<<< orphan*/  UpdatePhysicalInput () ; 
 int /*<<< orphan*/  UpdateQuizKing () ; 
 int /*<<< orphan*/  UpdateTopRider () ; 
 int /*<<< orphan*/  cidisabled ; 
 int /*<<< orphan*/ * powerpadbuf ; 

void FCEUD_UpdateInput(void)
{
  int x;
  int t=0;

  UpdatePhysicalInput();
  KeyboardCommands();

  for(x=0;x<2;x++)
   switch(InputType[x])
   {
    case SI_GAMEPAD:t|=1;break;
    case SI_ARKANOID:t|=2;break;
    case SI_ZAPPER:t|=2;break;
    case SI_POWERPADA:
    case SI_POWERPADB:powerpadbuf[x]=UpdatePPadData(x);break;
   }

  switch(InputType[2])
  {
   case SIFC_ARKANOID:t|=2;break;
   case SIFC_SHADOW:t|=2;break;
   case SIFC_FKB:if(cidisabled) UpdateFKB();break;
   case SIFC_HYPERSHOT: UpdateHyperShot();break;
   case SIFC_MAHJONG: UpdateMahjong();break;
   case SIFC_QUIZKING: UpdateQuizKing();break;
   case SIFC_FTRAINERB:
   case SIFC_FTRAINERA: UpdateFTrainer();break;
   case SIFC_TOPRIDER: UpdateTopRider();break;
   case SIFC_OEKAKIDS:t|=2;break;

  }

  if(t&1)
   UpdateGamepad();

  if(t&2)
   GetMouseData(MouseData);
}