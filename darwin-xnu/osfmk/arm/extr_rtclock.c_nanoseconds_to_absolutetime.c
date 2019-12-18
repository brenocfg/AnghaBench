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

/* Variables and functions */
 int NSEC_PER_SEC ; 
 int rtclock_sec_divisor ; 

void
nanoseconds_to_absolutetime(uint64_t   nanosecs,
                            uint64_t * result)
{
	uint64_t        t64;

	*result = (t64 = nanosecs / NSEC_PER_SEC) * rtclock_sec_divisor;
	nanosecs -= (t64 * NSEC_PER_SEC);
	*result += (nanosecs * rtclock_sec_divisor) / NSEC_PER_SEC;
}