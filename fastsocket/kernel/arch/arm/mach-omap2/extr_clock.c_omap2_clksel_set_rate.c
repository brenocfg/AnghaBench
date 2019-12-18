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
struct clk {unsigned long clksel_mask; unsigned long rate; TYPE_1__* parent; int /*<<< orphan*/  clksel_reg; } ;
struct TYPE_2__ {unsigned long rate; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long __ffs (unsigned long) ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _omap2xxx_clk_commit (struct clk*) ; 
 unsigned long omap2_clksel_round_rate_div (struct clk*,unsigned long,unsigned long*) ; 
 unsigned long omap2_divisor_to_clksel (struct clk*,unsigned long) ; 

int omap2_clksel_set_rate(struct clk *clk, unsigned long rate)
{
	u32 v, field_val, validrate, new_div = 0;

	if (!clk->clksel_mask)
		return -EINVAL;

	validrate = omap2_clksel_round_rate_div(clk, rate, &new_div);
	if (validrate != rate)
		return -EINVAL;

	field_val = omap2_divisor_to_clksel(clk, new_div);
	if (field_val == ~0)
		return -EINVAL;

	v = __raw_readl(clk->clksel_reg);
	v &= ~clk->clksel_mask;
	v |= field_val << __ffs(clk->clksel_mask);
	__raw_writel(v, clk->clksel_reg);
	v = __raw_readl(clk->clksel_reg); /* OCP barrier */

	clk->rate = clk->parent->rate / new_div;

	_omap2xxx_clk_commit(clk);

	return 0;
}