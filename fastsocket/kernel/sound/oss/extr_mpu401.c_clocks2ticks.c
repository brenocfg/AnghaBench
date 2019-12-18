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

/* Variables and functions */
 unsigned long curr_timebase ; 
 int hw_timebase ; 

__attribute__((used)) static unsigned long clocks2ticks(unsigned long clocks)
{
	/*
	 * The MPU-401 supports just a limited set of possible timebase values.
	 * Since the applications require more choices, the driver has to
	 * program the HW to do its best and to convert between the HW and
	 * actual timebases.
	 */
	return ((clocks * curr_timebase) + (hw_timebase / 2)) / hw_timebase;
}