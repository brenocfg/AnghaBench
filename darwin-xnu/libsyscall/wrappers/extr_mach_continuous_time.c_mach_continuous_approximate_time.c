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
typedef  scalar_t__ volatile uint64_t ;

/* Variables and functions */
 scalar_t__ volatile _mach_continuous_time_base () ; 
 scalar_t__ volatile mach_approximate_time () ; 

uint64_t
mach_continuous_approximate_time(void)
{
	/*
	 * No retry loop here because if we use a slightly too old timebase that's
	 * okay, we are approximate time anyway.
	*/
	volatile register uint64_t time_base = _mach_continuous_time_base();
	return time_base + mach_approximate_time();
}