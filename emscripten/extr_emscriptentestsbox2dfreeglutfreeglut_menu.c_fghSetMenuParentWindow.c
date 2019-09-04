#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ First; } ;
struct TYPE_9__ {TYPE_1__ Entries; int /*<<< orphan*/ * ParentWindow; } ;
struct TYPE_7__ {scalar_t__ Next; } ;
struct TYPE_8__ {TYPE_4__* SubMenu; TYPE_2__ Node; } ;
typedef  int /*<<< orphan*/  SFG_Window ;
typedef  TYPE_3__ SFG_MenuEntry ;
typedef  TYPE_4__ SFG_Menu ;

/* Variables and functions */

__attribute__((used)) static void fghSetMenuParentWindow( SFG_Window *window, SFG_Menu *menu )
{
    SFG_MenuEntry *menuEntry;

    menu->ParentWindow = window;

    for( menuEntry = ( SFG_MenuEntry * )menu->Entries.First;
         menuEntry;
         menuEntry = ( SFG_MenuEntry * )menuEntry->Node.Next )
        if( menuEntry->SubMenu )
            fghSetMenuParentWindow( window, menuEntry->SubMenu );
}