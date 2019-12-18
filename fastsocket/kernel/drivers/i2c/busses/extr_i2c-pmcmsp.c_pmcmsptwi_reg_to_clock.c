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
typedef  int u32 ;
struct pmcmsptwi_clock {int filter; int clock; } ;

/* Variables and functions */

__attribute__((used)) static inline void pmcmsptwi_reg_to_clock(
			u32 reg, struct pmcmsptwi_clock *clock)
{
	clock->filter = (reg >> 12) & 0xf;
	clock->clock = reg & 0x03ff;
}