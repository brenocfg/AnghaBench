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
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int lowpri_throttle_enabled ; 

void
sys_override_io_throttle(boolean_t enable_override)
{
	if (enable_override)
		lowpri_throttle_enabled = 0;
	else
		lowpri_throttle_enabled = 1;
}