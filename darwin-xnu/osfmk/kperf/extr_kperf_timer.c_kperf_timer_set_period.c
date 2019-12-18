#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {scalar_t__ period; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ kperf_timer_min_period_abstime () ; 
 scalar_t__ kperf_timer_min_pet_period_abstime () ; 
 unsigned int kperf_timerc ; 
 TYPE_1__* kperf_timerv ; 
 unsigned int pet_timer_id ; 

int
kperf_timer_set_period(unsigned int timerid, uint64_t period_abstime)
{
	uint64_t min_period;

	if (timerid >= kperf_timerc) {
		return EINVAL;
	}

	if (pet_timer_id == timerid) {
		min_period = kperf_timer_min_pet_period_abstime();
	} else {
		min_period = kperf_timer_min_period_abstime();
	}

	if (period_abstime > 0 && period_abstime < min_period) {
		period_abstime = min_period;
	}

	kperf_timerv[timerid].period = period_abstime;

	/* FIXME: re-program running timers? */

	return 0;
}