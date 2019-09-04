#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  rtcPop; } ;
typedef  TYPE_1__ cpu_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  EndOfAllTime ; 
 int /*<<< orphan*/  clock_timebase_init () ; 
 TYPE_1__* getCpuDatap () ; 
 int /*<<< orphan*/  mach_absolute_time () ; 
 int /*<<< orphan*/  ml_init_lock_timeout () ; 
 int /*<<< orphan*/  timer_resync_deadlines () ; 

int
rtclock_init(void)
{
	uint64_t     abstime;
	cpu_data_t * cdp;

	clock_timebase_init();
	ml_init_lock_timeout();

	cdp = getCpuDatap();

	abstime = mach_absolute_time();
	cdp->rtcPop = EndOfAllTime;					/* Init Pop time */
	timer_resync_deadlines();					/* Start the timers going */

	return (1);
}