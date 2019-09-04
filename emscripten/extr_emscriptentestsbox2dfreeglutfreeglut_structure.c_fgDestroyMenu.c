#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ Next; } ;
struct TYPE_17__ {scalar_t__ First; } ;
struct TYPE_22__ {scalar_t__ Window; TYPE_13__ Node; struct TYPE_22__* Text; TYPE_12__ Entries; int /*<<< orphan*/  (* Destroy ) () ;} ;
struct TYPE_20__ {scalar_t__ Next; } ;
struct TYPE_21__ {TYPE_2__ Node; } ;
struct TYPE_19__ {scalar_t__ First; } ;
struct TYPE_16__ {scalar_t__ CurrentWindow; TYPE_4__* CurrentMenu; TYPE_12__ Menus; TYPE_1__ Windows; } ;
typedef  TYPE_3__ SFG_Window ;
typedef  TYPE_4__ SFG_MenuEntry ;
typedef  TYPE_4__ SFG_Menu ;

/* Variables and functions */
 int /*<<< orphan*/  FREEGLUT_INTERNAL_ERROR_EXIT (TYPE_4__*,char*,char*) ; 
 int /*<<< orphan*/  fgDestroyWindow (scalar_t__) ; 
 int /*<<< orphan*/  fgListRemove (TYPE_12__*,TYPE_13__*) ; 
 int /*<<< orphan*/  fgSetWindow (int /*<<< orphan*/ *) ; 
 TYPE_11__ fgStructure ; 
 int /*<<< orphan*/  fghRemoveMenuFromMenu (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  fghRemoveMenuFromWindow (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 () ; 

void fgDestroyMenu( SFG_Menu* menu )
{
    SFG_Window *window;
    SFG_Menu *from;

    FREEGLUT_INTERNAL_ERROR_EXIT ( menu, "Menu destroy function called with null menu",
                                   "fgDestroyMenu" );

    /* First of all, have all references to this menu removed from all windows: */
    for( window = (SFG_Window *)fgStructure.Windows.First;
         window;
         window = (SFG_Window *)window->Node.Next )
        fghRemoveMenuFromWindow( window, menu );

    /* Now proceed with removing menu entries that lead to this menu */
    for( from = ( SFG_Menu * )fgStructure.Menus.First;
         from;
         from = ( SFG_Menu * )from->Node.Next )
        fghRemoveMenuFromMenu( from, menu );

    /*
     * If the programmer defined a destroy callback, call it
     * A. Donev: But first make this the active menu
     */
    if( menu->Destroy )
    {
        SFG_Menu *activeMenu=fgStructure.CurrentMenu;
        fgStructure.CurrentMenu = menu;
        menu->Destroy( );
        fgStructure.CurrentMenu = activeMenu;
    }

    /*
     * Now we are pretty sure the menu is not used anywhere
     * and that we can remove all of its entries
     */
    while( menu->Entries.First )
    {
        SFG_MenuEntry *entry = ( SFG_MenuEntry * ) menu->Entries.First;

        fgListRemove( &menu->Entries, &entry->Node );

        if( entry->Text )
            free( entry->Text );
        entry->Text = NULL;

        free( entry );
    }

    if( fgStructure.CurrentWindow == menu->Window )
        fgSetWindow( NULL );
    fgDestroyWindow( menu->Window );
    fgListRemove( &fgStructure.Menus, &menu->Node );
    if( fgStructure.CurrentMenu == menu )
        fgStructure.CurrentMenu = NULL;

    free( menu );
}