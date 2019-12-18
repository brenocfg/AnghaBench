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

__attribute__((used)) static int calc_clk(int time, int bus_speed)
{
	int clocks;

	clocks = (time*bus_speed+999)/1000 - 1;

	if (clocks < 0)
		clocks = 0;

	if (clocks > 0x0F)
		clocks = 0x0F;

	return clocks;
}