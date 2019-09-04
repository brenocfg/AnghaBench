#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* CurrentMenu; int /*<<< orphan*/  Menus; scalar_t__ MenuID; int /*<<< orphan*/ * CurrentWindow; } ;
struct TYPE_4__ {int /*<<< orphan*/  Node; int /*<<< orphan*/  Entries; int /*<<< orphan*/ * ActiveEntry; int /*<<< orphan*/  Callback; scalar_t__ ID; int /*<<< orphan*/ * Window; int /*<<< orphan*/ * ParentWindow; } ;
typedef  int /*<<< orphan*/  SFG_Window ;
typedef  TYPE_1__ SFG_Menu ;
typedef  int /*<<< orphan*/  FGCBMenu ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_TRUE ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  fgCreateWindow (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fgDisplayMenu ; 
 int /*<<< orphan*/  fgListAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fgListInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fgSetWindow (int /*<<< orphan*/ *) ; 
 TYPE_2__ fgStructure ; 
 int /*<<< orphan*/  glutDisplayFunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glutHideWindow () ; 

SFG_Menu* fgCreateMenu( FGCBMenu menuCallback )
{
    int x = 100, y = 100, w = 100, h = 100;
    SFG_Window *current_window = fgStructure.CurrentWindow;

    /* Have the menu object created */
    SFG_Menu* menu = (SFG_Menu *)calloc( sizeof(SFG_Menu), 1 );

    menu->ParentWindow = NULL;

    /* Create a window for the menu to reside in. */

    fgCreateWindow( NULL, "freeglut menu", GL_TRUE, x, y, GL_TRUE, w, h,
                    GL_FALSE, GL_TRUE );
    menu->Window = fgStructure.CurrentWindow;
    glutDisplayFunc( fgDisplayMenu );

    glutHideWindow( );  /* Hide the window for now */
    fgSetWindow( current_window );

    /* Initialize the object properties: */
    menu->ID       = ++fgStructure.MenuID;
    menu->Callback = menuCallback;
    menu->ActiveEntry = NULL;

    fgListInit( &menu->Entries );
    fgListAppend( &fgStructure.Menus, &menu->Node );

    /* Newly created menus implicitly become current ones */
    fgStructure.CurrentMenu = menu;

    return menu;
}