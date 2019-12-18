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
struct TYPE_2__ {scalar_t__ avail; } ;

/* Variables and functions */
 int MFGPT_DOMAIN_WORKING ; 
 int MFGPT_MAX_TIMERS ; 
 int /*<<< orphan*/  geode_mfgpt_detect () ; 
 int mfgpt_get (int) ; 
 TYPE_1__* mfgpt_timers ; 
 int timers ; 

int geode_mfgpt_alloc_timer(int timer, int domain)
{
	int i;

	if (timers == -1) {
		/* timers haven't been detected yet */
		geode_mfgpt_detect();
	}

	if (!timers)
		return -1;

	if (timer >= MFGPT_MAX_TIMERS)
		return -1;

	if (timer < 0) {
		/* Try to find an available timer */
		for (i = 0; i < MFGPT_MAX_TIMERS; i++) {
			if (mfgpt_timers[i].avail)
				return mfgpt_get(i);

			if (i == 5 && domain == MFGPT_DOMAIN_WORKING)
				break;
		}
	} else {
		/* If they requested a specific timer, try to honor that */
		if (mfgpt_timers[timer].avail)
			return mfgpt_get(timer);
	}

	/* No timers available - too bad */
	return -1;
}