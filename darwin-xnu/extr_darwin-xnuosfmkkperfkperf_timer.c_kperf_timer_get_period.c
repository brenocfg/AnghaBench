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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  period; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int kperf_timerc ; 
 TYPE_1__* kperf_timerv ; 

int
kperf_timer_get_period(unsigned int timerid, uint64_t *period_abstime)
{
	if (timerid >= kperf_timerc) {
		return EINVAL;
	}

	*period_abstime = kperf_timerv[timerid].period;
	return 0;
}