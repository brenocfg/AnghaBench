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
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 scalar_t__ AMS_DELTA_LATCH2_VIRT ; 
 int /*<<< orphan*/  ams_delta_latch2_reg ; 

void ams_delta_latch2_write(u16 mask, u16 value)
{
	ams_delta_latch2_reg &= ~mask;
	ams_delta_latch2_reg |= value;
	*(volatile __u16 *) AMS_DELTA_LATCH2_VIRT = ams_delta_latch2_reg;
}