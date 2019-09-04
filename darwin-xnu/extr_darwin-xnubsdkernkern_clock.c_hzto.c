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
struct timeval {long tv_sec; int tv_usec; } ;

/* Variables and functions */
 int hz ; 
 int /*<<< orphan*/  microtime (struct timeval*) ; 
 int tick ; 

int
hzto(struct timeval *tv)
{
	struct timeval now;
	long ticks;
	long sec;

	microtime(&now);
	/*
	 * If number of milliseconds will fit in 32 bit arithmetic,
	 * then compute number of milliseconds to time and scale to
	 * ticks.  Otherwise just compute number of hz in time, rounding
	 * times greater than representible to maximum value.
	 *
	 * Delta times less than 25 days can be computed ``exactly''.
	 * Maximum value for any timeout in 10ms ticks is 250 days.
	 */
	sec = tv->tv_sec - now.tv_sec;
	if (sec <= 0x7fffffff / 1000 - 1000)
		ticks = ((tv->tv_sec - now.tv_sec) * 1000 +
			(tv->tv_usec - now.tv_usec) / 1000)
				/ (tick / 1000);
	else if (sec <= 0x7fffffff / hz)
		ticks = sec * hz;
	else
		ticks = 0x7fffffff;

	return (ticks);
}