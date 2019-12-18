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
struct extif_timings {int clk_div; int converted; int* tim; } ;

/* Variables and functions */
 int calc_rd_timings (struct extif_timings*) ; 
 int calc_wr_timings (struct extif_timings*) ; 

__attribute__((used)) static int sossi_convert_timings(struct extif_timings *t)
{
	int r = 0;
	int div = t->clk_div;

	t->converted = 0;

	if (div <= 0 || div > 8)
		return -1;

	/* no CS on SOSSI, so ignore cson, csoff, cs_pulsewidth */
	if ((r = calc_rd_timings(t)) < 0)
		return r;

	if ((r = calc_wr_timings(t)) < 0)
		return r;

	t->tim[4] = div;

	t->converted = 1;

	return 0;
}