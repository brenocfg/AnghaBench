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
typedef  unsigned long u32 ;
struct clk {unsigned long rate; TYPE_1__* parent; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {unsigned long rate; } ;

/* Variables and functions */
 unsigned long omap2_clksel_get_divisor (struct clk*) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long,...) ; 

unsigned long omap2_clksel_recalc(struct clk *clk)
{
	unsigned long rate;
	u32 div = 0;

	pr_debug("clock: recalc'ing clksel clk %s\n", clk->name);

	div = omap2_clksel_get_divisor(clk);
	if (div == 0)
		return clk->rate;

	rate = clk->parent->rate / div;

	pr_debug("clock: new clock rate is %ld (div %d)\n", rate, div);

	return rate;
}