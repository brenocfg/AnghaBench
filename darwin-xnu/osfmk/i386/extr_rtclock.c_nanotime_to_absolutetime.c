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
typedef  scalar_t__ clock_sec_t ;
typedef  int clock_nsec_t ;

/* Variables and functions */
 int NSEC_PER_SEC ; 

void
nanotime_to_absolutetime(
	clock_sec_t			secs,
	clock_nsec_t		nanosecs,
	uint64_t			*result)
{
	*result = ((uint64_t)secs * NSEC_PER_SEC) + nanosecs;
}