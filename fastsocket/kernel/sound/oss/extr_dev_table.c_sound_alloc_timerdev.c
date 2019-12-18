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
 int MAX_TIMER_DEV ; 
 int num_sound_timers ; 
 int /*<<< orphan*/ ** sound_timer_devs ; 

int sound_alloc_timerdev(void)
{
	int i;

	for (i = 0; i < MAX_TIMER_DEV; i++) {
		if (sound_timer_devs[i] == NULL) {
			if (i >= num_sound_timers)
				num_sound_timers++;
			return i;
		}
	}
	return -1;
}