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
struct TYPE_4__ {TYPE_2__* First; } ;
struct TYPE_6__ {TYPE_1__ Timers; } ;
struct TYPE_5__ {long TriggerTime; } ;
typedef  TYPE_2__ SFG_Timer ;

/* Variables and functions */
 long INT_MAX ; 
 long fgElapsedTime () ; 
 TYPE_3__ fgState ; 

__attribute__((used)) static long fghNextTimer( void )
{
    long ret = INT_MAX;
    SFG_Timer *timer = fgState.Timers.First;

    if( timer )
        ret = timer->TriggerTime - fgElapsedTime();
    if( ret < 0 )
        ret = 0;

    return ret;
}