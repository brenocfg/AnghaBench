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
 int /*<<< orphan*/  SIGVTALRM ; 
 int UM_HZ ; 
 int UM_NSEC_PER_SEC ; 
 int /*<<< orphan*/  alarm_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned long long last_tick ; 
 unsigned long long os_nsecs () ; 
 int skew ; 

__attribute__((used)) static void deliver_alarm(void)
{
	unsigned long long this_tick = os_nsecs();
	int one_tick = UM_NSEC_PER_SEC / UM_HZ;

	/* Protection against the host's time going backwards */
	if ((last_tick != 0) && (this_tick < last_tick))
		this_tick = last_tick;

	if (last_tick == 0)
		last_tick = this_tick - one_tick;

	skew += this_tick - last_tick;

	while (skew >= one_tick) {
		alarm_handler(SIGVTALRM, NULL);
		skew -= one_tick;
	}

	last_tick = this_tick;
}