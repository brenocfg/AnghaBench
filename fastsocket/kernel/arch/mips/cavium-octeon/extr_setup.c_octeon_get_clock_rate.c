#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_2__ {int eclock_hz; } ;

/* Variables and functions */
 TYPE_1__* octeon_bootinfo ; 
 scalar_t__ octeon_is_simulation () ; 

uint64_t octeon_get_clock_rate(void)
{
	if (octeon_is_simulation())
		octeon_bootinfo->eclock_hz = 6000000;
	return octeon_bootinfo->eclock_hz;
}