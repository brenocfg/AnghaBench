#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* First; } ;
struct TYPE_6__ {TYPE_4__ WindowsToDestroy; } ;
struct TYPE_5__ {int /*<<< orphan*/  node; int /*<<< orphan*/  window; } ;
typedef  TYPE_1__ SFG_WindowList ;

/* Variables and functions */
 int /*<<< orphan*/  fgDestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fgListRemove (TYPE_4__*,int /*<<< orphan*/ *) ; 
 TYPE_3__ fgStructure ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void fgCloseWindows( )
{
    while( fgStructure.WindowsToDestroy.First )
    {
        SFG_WindowList *window_ptr = fgStructure.WindowsToDestroy.First;
        fgDestroyWindow( window_ptr->window );
        fgListRemove( &fgStructure.WindowsToDestroy, &window_ptr->node );
        free( window_ptr );
    }
}