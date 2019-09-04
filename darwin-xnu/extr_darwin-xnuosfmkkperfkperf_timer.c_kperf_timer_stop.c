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
struct TYPE_2__ {scalar_t__ period; int /*<<< orphan*/  tcall; scalar_t__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  kperf_pet_config (int /*<<< orphan*/ ) ; 
 unsigned int kperf_timerc ; 
 TYPE_1__* kperf_timerv ; 
 int /*<<< orphan*/  timer_call_cancel (int /*<<< orphan*/ *) ; 

void
kperf_timer_stop(void)
{
	for (unsigned int i = 0; i < kperf_timerc; i++) {
		if (kperf_timerv[i].period == 0) {
			continue;
		}

		/* wait for the timer to stop */
		while (kperf_timerv[i].active);

		timer_call_cancel(&kperf_timerv[i].tcall);
	}

	/* wait for PET to stop, too */
	kperf_pet_config(0);
}