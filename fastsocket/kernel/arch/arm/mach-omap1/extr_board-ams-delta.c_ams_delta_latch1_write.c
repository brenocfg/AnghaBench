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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 scalar_t__ AMS_DELTA_LATCH1_VIRT ; 
 int /*<<< orphan*/  ams_delta_latch1_reg ; 

void ams_delta_latch1_write(u8 mask, u8 value)
{
	ams_delta_latch1_reg &= ~mask;
	ams_delta_latch1_reg |= value;
	*(volatile __u8 *) AMS_DELTA_LATCH1_VIRT = ams_delta_latch1_reg;
}