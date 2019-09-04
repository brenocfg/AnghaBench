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
struct TYPE_6__ {TYPE_1__* First; } ;
struct TYPE_5__ {int /*<<< orphan*/  FreeTimers; TYPE_3__ Timers; } ;
struct TYPE_4__ {long TriggerTime; int /*<<< orphan*/  ID; int /*<<< orphan*/  (* Callback ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  Node; } ;
typedef  TYPE_1__ SFG_Timer ;

/* Variables and functions */
 long fgElapsedTime () ; 
 int /*<<< orphan*/  fgListAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fgListRemove (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_2__ fgState ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fghCheckTimers( void )
{
    long checkTime = fgElapsedTime( );

    while( fgState.Timers.First )
    {
        SFG_Timer *timer = fgState.Timers.First;

        if( timer->TriggerTime > checkTime )
            break;

        fgListRemove( &fgState.Timers, &timer->Node );
        fgListAppend( &fgState.FreeTimers, &timer->Node );

        timer->Callback( timer->ID );
    }
}