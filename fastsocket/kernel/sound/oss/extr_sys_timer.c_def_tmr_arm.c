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
 int curr_ticks ; 
 long next_event_time ; 
 long prev_event_time ; 

__attribute__((used)) static void
def_tmr_arm(int dev, long time)
{
	if (time < 0)
		time = curr_ticks + 1;
	else if (time <= curr_ticks)	/* It's the time */
		return;

	next_event_time = prev_event_time = time;

	return;
}