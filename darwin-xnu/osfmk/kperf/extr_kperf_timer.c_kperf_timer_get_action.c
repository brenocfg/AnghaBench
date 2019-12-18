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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  actionid; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int kperf_timerc ; 
 TYPE_1__* kperf_timerv ; 

int
kperf_timer_get_action(unsigned int timerid, uint32_t *action)
{
	if (timerid >= kperf_timerc) {
		return EINVAL;
	}

	*action = kperf_timerv[timerid].actionid;
	return 0;
}