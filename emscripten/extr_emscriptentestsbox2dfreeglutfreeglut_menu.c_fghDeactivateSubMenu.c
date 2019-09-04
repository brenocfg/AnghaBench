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
struct TYPE_11__ {int /*<<< orphan*/ * ActiveMenu; } ;
struct TYPE_8__ {scalar_t__ Next; } ;
struct TYPE_10__ {TYPE_3__* SubMenu; void* IsActive; TYPE_2__ Node; } ;
struct TYPE_7__ {scalar_t__ First; } ;
struct TYPE_9__ {TYPE_6__* ParentWindow; TYPE_1__ Entries; int /*<<< orphan*/ * ActiveEntry; void* IsActive; TYPE_6__* Window; } ;
typedef  TYPE_4__ SFG_MenuEntry ;

/* Variables and functions */
 void* GL_FALSE ; 
 int /*<<< orphan*/  fgSetWindow (TYPE_6__*) ; 
 int /*<<< orphan*/  glutHideWindow () ; 

__attribute__((used)) static void fghDeactivateSubMenu( SFG_MenuEntry *menuEntry )
{
    SFG_MenuEntry *subMenuIter;
    /* Hide the present menu's window */
    fgSetWindow( menuEntry->SubMenu->Window );
    glutHideWindow( );

    /* Forget about having that menu active anymore, now: */
    menuEntry->SubMenu->Window->ActiveMenu = NULL;
    menuEntry->SubMenu->IsActive = GL_FALSE;
    menuEntry->SubMenu->ActiveEntry = NULL;

    /* Hide all submenu windows, and the root menu's window. */
    for ( subMenuIter = (SFG_MenuEntry *)menuEntry->SubMenu->Entries.First;
          subMenuIter;
          subMenuIter = (SFG_MenuEntry *)subMenuIter->Node.Next )
    {
        subMenuIter->IsActive = GL_FALSE;

        /* Is that an active submenu by any case? */
        if( subMenuIter->SubMenu )
            fghDeactivateSubMenu( subMenuIter );
    }

    fgSetWindow ( menuEntry->SubMenu->ParentWindow ) ;
}