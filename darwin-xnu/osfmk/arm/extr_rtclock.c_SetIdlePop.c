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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {scalar_t__ rtcPop; scalar_t__ cpu_idle_latency; scalar_t__ cpu_idle_pop; } ;
typedef  TYPE_1__ cpu_data_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int deadline_to_decrementer (scalar_t__,scalar_t__) ; 
 TYPE_1__* getCpuDatap () ; 
 scalar_t__ mach_absolute_time () ; 
 int /*<<< orphan*/  ml_set_decrementer (int /*<<< orphan*/ ) ; 

boolean_t
SetIdlePop(void)
{
	int          delay_time;
	uint64_t     time;
	uint64_t     current_time;
	cpu_data_t * cdp;

	cdp = getCpuDatap();
	current_time = mach_absolute_time();

	if (((cdp->rtcPop < current_time) ||
	    (cdp->rtcPop - current_time) < cdp->cpu_idle_latency))
		return FALSE;

	time = cdp->rtcPop - cdp->cpu_idle_latency;

	delay_time = deadline_to_decrementer(time, current_time);
	cdp->cpu_idle_pop = delay_time + current_time;
	ml_set_decrementer((uint32_t) delay_time);

	return TRUE;
}