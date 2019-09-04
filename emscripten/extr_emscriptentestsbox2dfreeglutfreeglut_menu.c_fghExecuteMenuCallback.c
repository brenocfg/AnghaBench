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
struct TYPE_11__ {TYPE_4__* CurrentMenu; } ;
struct TYPE_7__ {scalar_t__ First; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* Callback ) (int /*<<< orphan*/ ) ;TYPE_1__ Entries; } ;
struct TYPE_8__ {scalar_t__ Next; } ;
struct TYPE_9__ {int /*<<< orphan*/  ID; TYPE_4__* SubMenu; scalar_t__ IsActive; TYPE_2__ Node; } ;
typedef  TYPE_3__ SFG_MenuEntry ;
typedef  TYPE_4__ SFG_Menu ;

/* Variables and functions */
 TYPE_6__ fgStructure ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fghExecuteMenuCallback( SFG_Menu* menu )
{
    SFG_MenuEntry *menuEntry;

    /* First of all check any of the active sub menus... */
    for( menuEntry = (SFG_MenuEntry *)menu->Entries.First;
         menuEntry;
         menuEntry = (SFG_MenuEntry *)menuEntry->Node.Next)
    {
        if( menuEntry->IsActive )
        {
            if( menuEntry->SubMenu )
                fghExecuteMenuCallback( menuEntry->SubMenu );
            else
                if( menu->Callback )
                {
                    SFG_Menu *save_menu = fgStructure.CurrentMenu;
                    fgStructure.CurrentMenu = menu;
                    menu->Callback( menuEntry->ID );
                    fgStructure.CurrentMenu = save_menu;
                }

            return;
        }
    }
}