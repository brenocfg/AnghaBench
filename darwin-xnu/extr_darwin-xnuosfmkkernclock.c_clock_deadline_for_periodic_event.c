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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ mach_absolute_time () ; 

void
clock_deadline_for_periodic_event(
	uint64_t			interval,
	uint64_t			abstime,
	uint64_t			*deadline)
{
	assert(interval != 0);

	*deadline += interval;

	if (*deadline <= abstime) {
		*deadline = abstime + interval;
		abstime = mach_absolute_time();

		if (*deadline <= abstime)
			*deadline = abstime + interval;
	}
}