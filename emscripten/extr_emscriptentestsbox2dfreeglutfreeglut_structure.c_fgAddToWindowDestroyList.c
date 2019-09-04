#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * CurrentWindow; int /*<<< orphan*/  WindowsToDestroy; } ;
struct TYPE_3__ {int /*<<< orphan*/  node; int /*<<< orphan*/ * window; } ;
typedef  TYPE_1__ SFG_WindowList ;
typedef  int /*<<< orphan*/  SFG_Window ;
typedef  int /*<<< orphan*/  FGCBDestroy ;

/* Variables and functions */
 int /*<<< orphan*/  Destroy ; 
 int /*<<< orphan*/  FETCH_WCB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_WCB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fgListAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__ fgStructure ; 
 int /*<<< orphan*/  fghClearCallBacks (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 

void fgAddToWindowDestroyList( SFG_Window* window )
{
    SFG_WindowList *new_list_entry =
        ( SFG_WindowList* )malloc( sizeof(SFG_WindowList ) );
    new_list_entry->window = window;
    fgListAppend( &fgStructure.WindowsToDestroy, &new_list_entry->node );

    /* Check if the window is the current one... */
    if( fgStructure.CurrentWindow == window )
        fgStructure.CurrentWindow = NULL;

    /*
     * Clear all window callbacks except Destroy, which will
     * be invoked later.  Right now, we are potentially carrying
     * out a freeglut operation at the behest of a client callback,
     * so we are reluctant to re-enter the client with the Destroy
     * callback, right now.  The others are all wiped out, however,
     * to ensure that they are no longer called after this point.
     */
    {
        FGCBDestroy destroy = (FGCBDestroy)FETCH_WCB( *window, Destroy );
        fghClearCallBacks( window );
        SET_WCB( *window, Destroy, destroy );
    }
}