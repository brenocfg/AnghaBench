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
struct timespec {scalar_t__ tv_sec; scalar_t__ tv_nsec; } ;

/* Variables and functions */
 scalar_t__ INT32_MAX ; 
 unsigned long long NSEC_PER_SEC ; 

int
timespec_is_valid(const struct timespec *ts)
{
	/* The INT32_MAX limit ensures the timespec is safe for clock_*() functions
	 * which accept 32-bit ints. */
	if (ts->tv_sec < 0 || ts->tv_sec > INT32_MAX ||
			ts->tv_nsec < 0 || (unsigned long long)ts->tv_nsec > NSEC_PER_SEC) {
		return 0;
	}
	return 1;
}