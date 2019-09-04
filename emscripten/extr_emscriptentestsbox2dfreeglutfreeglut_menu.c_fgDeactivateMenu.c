#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  ActiveMenus; } ;
struct TYPE_12__ {scalar_t__ First; } ;
struct TYPE_16__ {TYPE_1__ Entries; int /*<<< orphan*/ * ActiveEntry; void* IsActive; TYPE_3__* ParentWindow; TYPE_3__* Window; } ;
struct TYPE_13__ {scalar_t__ Next; } ;
struct TYPE_15__ {scalar_t__ SubMenu; void* IsActive; TYPE_2__ Node; } ;
struct TYPE_14__ {TYPE_5__* ActiveMenu; } ;
typedef  TYPE_3__ SFG_Window ;
typedef  TYPE_4__ SFG_MenuEntry ;
typedef  TYPE_5__ SFG_Menu ;

/* Variables and functions */
 void* GL_FALSE ; 
 int /*<<< orphan*/  fgSetWindow (TYPE_3__*) ; 
 TYPE_9__ fgState ; 
 int /*<<< orphan*/  fghDeactivateSubMenu (TYPE_4__*) ; 
 int /*<<< orphan*/  fghSetMenuParentWindow (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  freeglut_return_if_fail (TYPE_5__*) ; 
 int /*<<< orphan*/  glutHideWindow () ; 

void fgDeactivateMenu( SFG_Window *window )
{
    SFG_Window *parent_window = NULL;

    /* Check if there is an active menu attached to this window... */
    SFG_Menu* menu = window->ActiveMenu;
    SFG_MenuEntry *menuEntry;

    /* Did we find an active window? */
    freeglut_return_if_fail( menu );

    parent_window = menu->ParentWindow;

    /* Hide the present menu's window */
    fgSetWindow( menu->Window );
    glutHideWindow( );

    /* Forget about having that menu active anymore, now: */
    menu->Window->ActiveMenu = NULL;
    menu->ParentWindow->ActiveMenu = NULL;
    fghSetMenuParentWindow ( NULL, menu );
    menu->IsActive = GL_FALSE;
    menu->ActiveEntry = NULL;

    fgState.ActiveMenus--;

    /* Hide all submenu windows, and the root menu's window. */
    for ( menuEntry = ( SFG_MenuEntry * )menu->Entries.First;
          menuEntry;
          menuEntry = ( SFG_MenuEntry * )menuEntry->Node.Next )
    {
        menuEntry->IsActive = GL_FALSE;

        /* Is that an active submenu by any case? */
        if( menuEntry->SubMenu )
            fghDeactivateSubMenu( menuEntry );
    }

    fgSetWindow ( parent_window ) ;
}