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
typedef  int u32 ;
struct clk {int scale_shift; scalar_t__ busy_reg; int /*<<< orphan*/  scale_reg; TYPE_1__* parent; } ;
struct TYPE_2__ {int rate; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_is_busy (struct clk*) ; 

__attribute__((used)) static int io_set_rate(struct clk *clk, u32 rate)
{
	u32 reg_frac, clkctrl_frac;
	int i, ret = 0, mask = 0x1f;

	clkctrl_frac = (clk->parent->rate * 18 + rate - 1) / rate;

	if (clkctrl_frac < 18 || clkctrl_frac > 35) {
		ret = -EINVAL;
		goto out;
	}

	reg_frac = __raw_readl(clk->scale_reg);
	reg_frac &= ~(mask << clk->scale_shift);
	__raw_writel(reg_frac | (clkctrl_frac << clk->scale_shift),
				clk->scale_reg);
	if (clk->busy_reg) {
		for (i = 10000; i; i--)
			if (!clk_is_busy(clk))
				break;
		if (!i)
			ret = -ETIMEDOUT;
		else
			ret = 0;
	}
out:
	return ret;
}