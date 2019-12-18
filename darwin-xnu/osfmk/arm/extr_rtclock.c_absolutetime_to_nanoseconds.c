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
absolutetime_to_nanoseconds(uint64_t   abstime,
                            uint64_t * result)
{
	uint64_t        t64;

	*result = (t64 = abstime / rtclock_sec_divisor) * NSEC_PER_SEC;
	abstime -= (t64 * rtclock_sec_divisor);
	*result += (abstime * NSEC_PER_SEC) / rtclock_sec_divisor;
}