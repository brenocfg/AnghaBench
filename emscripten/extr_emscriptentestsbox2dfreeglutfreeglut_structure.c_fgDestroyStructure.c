#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ First; } ;
struct TYPE_4__ {scalar_t__ First; } ;
struct TYPE_6__ {TYPE_2__ Windows; TYPE_1__ Menus; } ;
typedef  int /*<<< orphan*/  SFG_Window ;
typedef  int /*<<< orphan*/  SFG_Menu ;

/* Variables and functions */
 int /*<<< orphan*/  fgCloseWindows () ; 
 int /*<<< orphan*/  fgDestroyMenu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fgDestroyWindow (int /*<<< orphan*/ *) ; 
 TYPE_3__ fgStructure ; 

void fgDestroyStructure( void )
{
    /* Clean up the WindowsToDestroy list. */
    fgCloseWindows( );

    /* Make sure all windows and menus have been deallocated */
    while( fgStructure.Menus.First )
        fgDestroyMenu( ( SFG_Menu * )fgStructure.Menus.First );

    while( fgStructure.Windows.First )
        fgDestroyWindow( ( SFG_Window * )fgStructure.Windows.First );
}