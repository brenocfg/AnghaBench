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
struct TYPE_2__ {scalar_t__ period; int /*<<< orphan*/  actionid; } ;

/* Variables and functions */
 int /*<<< orphan*/  kperf_pet_config (int /*<<< orphan*/ ) ; 
 scalar_t__ kperf_timer_min_pet_period_abstime () ; 
 unsigned int kperf_timerc ; 
 TYPE_1__* kperf_timerv ; 
 unsigned int pet_timer_id ; 

int
kperf_timer_set_petid(unsigned int timerid)
{
	if (timerid < kperf_timerc) {
		uint64_t min_period;

		min_period = kperf_timer_min_pet_period_abstime();
		if (kperf_timerv[timerid].period < min_period) {
			kperf_timerv[timerid].period = min_period;
		}
		kperf_pet_config(kperf_timerv[timerid].actionid);
	} else {
		/* clear the PET trigger if it's a bogus ID */
		kperf_pet_config(0);
	}

	pet_timer_id = timerid;

	return 0;
}