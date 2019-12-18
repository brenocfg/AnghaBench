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
typedef  int timer_tick_count_t ;
typedef  int timer_msec_t ;

/* Variables and functions */
 int timer_get_tick_rate () ; 

timer_msec_t timer_ticks_to_msec(timer_tick_count_t ticks)
{
	static int tickRateMsec;

	if (tickRateMsec == 0) {
		tickRateMsec = timer_get_tick_rate() / 1000;
	}

	return ticks / tickRateMsec;
}