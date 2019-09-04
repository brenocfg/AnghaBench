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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ clock_usec_t ;
typedef  int clock_sec_t ;

/* Variables and functions */
 int rtclock_sec_divisor ; 
 int rtclock_usec_divisor ; 

void
absolutetime_to_microtime(uint64_t       abstime,
                          clock_sec_t *  secs,
                          clock_usec_t * microsecs)
{
	uint64_t t64;

	*secs = t64 = abstime / rtclock_sec_divisor;
	abstime -= (t64 * rtclock_sec_divisor);

	*microsecs = (uint32_t)(abstime / rtclock_usec_divisor);
}