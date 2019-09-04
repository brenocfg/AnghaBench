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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 scalar_t__ mach_continuous_time () ; 

void
clock_continuoustime_interval_to_deadline(
	uint64_t			conttime,
	uint64_t			*result)
{
	*result = mach_continuous_time() + conttime;
}