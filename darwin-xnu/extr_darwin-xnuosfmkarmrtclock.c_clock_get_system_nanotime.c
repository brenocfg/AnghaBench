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
typedef  int uint64_t ;
typedef  int clock_sec_t ;
typedef  scalar_t__ clock_nsec_t ;

/* Variables and functions */
 int NSEC_PER_SEC ; 
 int mach_absolute_time () ; 
 int rtclock_sec_divisor ; 

void
clock_get_system_nanotime(clock_sec_t *  secs,
                          clock_nsec_t * nanosecs)
{
	uint64_t abstime;
	uint64_t t64;

	abstime = mach_absolute_time();
	*secs = (t64 = abstime / rtclock_sec_divisor);
	abstime -= (t64 * rtclock_sec_divisor);

	*nanosecs = (clock_nsec_t)((abstime * NSEC_PER_SEC) / rtclock_sec_divisor);
}