#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ CPU_CHECKIN_MIN_INTERVAL_MAX_US ; 
 int /*<<< orphan*/  NSEC_PER_USEC ; 
 int /*<<< orphan*/  clock_interval_to_absolutetime_interval (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_checkin_min_interval ; 
 scalar_t__ cpu_checkin_min_interval_us ; 

void
cpu_quiescent_counter_set_min_interval_us(uint32_t new_value_us)
{
	/* clamp to something vaguely sane */
	if (new_value_us > CPU_CHECKIN_MIN_INTERVAL_MAX_US)
		new_value_us = CPU_CHECKIN_MIN_INTERVAL_MAX_US;

	cpu_checkin_min_interval_us = new_value_us;

	uint64_t abstime = 0;
	clock_interval_to_absolutetime_interval(cpu_checkin_min_interval_us,
	                                        NSEC_PER_USEC, &abstime);
	cpu_checkin_min_interval = abstime;
}