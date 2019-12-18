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
struct clk {int flags; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int CLKFLAG_USE_MIN_MAX_TO_SET ; 
 int pc_clk_set_max_rate (int /*<<< orphan*/ ,unsigned long) ; 
 int pc_clk_set_min_rate (int /*<<< orphan*/ ,unsigned long) ; 
 int pc_clk_set_rate (int /*<<< orphan*/ ,unsigned long) ; 

int clk_set_rate(struct clk *clk, unsigned long rate)
{
	int ret;
	if (clk->flags & CLKFLAG_USE_MIN_MAX_TO_SET) {
		ret = pc_clk_set_max_rate(clk->id, rate);
		if (ret)
			return ret;
		return pc_clk_set_min_rate(clk->id, rate);
	}
	return pc_clk_set_rate(clk->id, rate);
}