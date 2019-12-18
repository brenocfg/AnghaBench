#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  numitems; } ;
struct TYPE_10__ {TYPE_1__* prevMenu; } ;
struct TYPE_9__ {int x; int y; int /*<<< orphan*/  routine; } ;
struct TYPE_8__ {int /*<<< orphan*/  routine; } ;
struct TYPE_7__ {int y; int /*<<< orphan*/  numitems; int /*<<< orphan*/  lastOn; } ;

/* Variables and functions */
 TYPE_6__ EpiDef ; 
 int /*<<< orphan*/  M_DrawReadThis1 ; 
 int /*<<< orphan*/  M_FinishReadThis ; 
 TYPE_1__ MainDef ; 
 int /*<<< orphan*/ * MainMenu ; 
 TYPE_4__ NewDef ; 
 TYPE_3__ ReadDef1 ; 
 TYPE_2__* ReadMenu1 ; 
#define  commercial 131 
 TYPE_1__* currentMenu ; 
 int gamemode ; 
 int /*<<< orphan*/  itemOn ; 
 scalar_t__ menuactive ; 
 scalar_t__ messageLastMenuActive ; 
 int /*<<< orphan*/ * messageString ; 
 scalar_t__ messageToPrint ; 
 int quickSaveSlot ; 
 size_t quitdoom ; 
 size_t readthis ; 
#define  registered 130 
#define  retail 129 
 scalar_t__ screenSize ; 
 scalar_t__ screenblocks ; 
#define  shareware 128 
 int skullAnimCounter ; 
 scalar_t__ whichSkull ; 

void M_Init (void)
{
    currentMenu = &MainDef;
    menuactive = 0;
    itemOn = currentMenu->lastOn;
    whichSkull = 0;
    skullAnimCounter = 10;
    screenSize = screenblocks - 3;
    messageToPrint = 0;
    messageString = NULL;
    messageLastMenuActive = menuactive;
    quickSaveSlot = -1;

    // Here we could catch other version dependencies,
    //  like HELP1/2, and four episodes.

  
    switch ( gamemode )
    {
      case commercial:
	// This is used because DOOM 2 had only one HELP
        //  page. I use CREDIT as second page now, but
	//  kept this hack for educational purposes.
	MainMenu[readthis] = MainMenu[quitdoom];
	MainDef.numitems--;
	MainDef.y += 8;
	NewDef.prevMenu = &MainDef;
	ReadDef1.routine = M_DrawReadThis1;
	ReadDef1.x = 330;
	ReadDef1.y = 165;
	ReadMenu1[0].routine = M_FinishReadThis;
	break;
      case shareware:
	// Episode 2 and 3 are handled,
	//  branching to an ad screen.
      case registered:
	// We need to remove the fourth episode.
	EpiDef.numitems--;
	break;
      case retail:
	// We are fine.
      default:
	break;
    }
    
}