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
struct clk {int enable_shift; scalar_t__ enable_wait; scalar_t__ enable_reg; scalar_t__ enable_negate; } ;

/* Variables and functions */
 int EINVAL ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  udelay (scalar_t__) ; 

__attribute__((used)) static int std_clk_enable(struct clk *clk)
{
	if (clk->enable_reg) {
		u32 clk_reg = __raw_readl(clk->enable_reg);
		if (clk->enable_negate)
			clk_reg &= ~(1 << clk->enable_shift);
		else
			clk_reg |= (1 << clk->enable_shift);
		__raw_writel(clk_reg, clk->enable_reg);
		if (clk->enable_wait)
			udelay(clk->enable_wait);
		return 0;
	} else
		return -EINVAL;
}