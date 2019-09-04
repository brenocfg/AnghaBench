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

/* Variables and functions */
 scalar_t__ KPERF_SAMPLING_OFF ; 
 scalar_t__ KPERF_SAMPLING_ON ; 
 scalar_t__ KPERF_SAMPLING_SHUTDOWN ; 
 int /*<<< orphan*/  kperf_lightweight_pet_active_update () ; 
 int /*<<< orphan*/  kperf_timer_stop () ; 
 scalar_t__ sampling_status ; 

int
kperf_sampling_disable(void)
{
	if (sampling_status != KPERF_SAMPLING_ON) {
		return 0;
	}

	/* mark a shutting down */
	sampling_status = KPERF_SAMPLING_SHUTDOWN;

	/* tell timers to disable */
	kperf_timer_stop();

	/* mark as off */
	sampling_status = KPERF_SAMPLING_OFF;
	kperf_lightweight_pet_active_update();

	return 0;
}