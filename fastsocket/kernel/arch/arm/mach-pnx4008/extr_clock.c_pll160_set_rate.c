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
struct clk {int rate; int flags; int /*<<< orphan*/  scale_reg; TYPE_1__* parent; } ;
struct TYPE_2__ {int rate; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int PLL160_MAX_FCCO ; 
 int PLL160_MIN_FCCO ; 
 int RATE_PROPAGATES ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_reg_disable (struct clk*) ; 
 int /*<<< orphan*/  clk_reg_disable1 (struct clk*) ; 
 int /*<<< orphan*/  clk_reg_enable (struct clk*) ; 
 int /*<<< orphan*/  clk_reg_enable1 (struct clk*) ; 
 scalar_t__ clk_wait_for_pll_lock (struct clk*) ; 
 int /*<<< orphan*/  propagate_rate (struct clk*) ; 

__attribute__((used)) static int pll160_set_rate(struct clk *clk, u32 rate)
{
	u32 tmp_reg, tmp_m, tmp_2p, i;
	u32 parent_rate;
	int ret = -EINVAL;

	parent_rate = clk->parent->rate;

	if (!parent_rate)
		goto out;

	/* set direct run for ARM or disable output for others  */
	clk_reg_disable(clk);

	/* disable source input as well (ignored for ARM) */
	clk_reg_disable1(clk);

	tmp_reg = __raw_readl(clk->scale_reg);
	tmp_reg &= ~0x1ffff;	/*clear all settings, power down */
	__raw_writel(tmp_reg, clk->scale_reg);

	rate -= rate % parent_rate;	/*round down the input */

	if (rate > PLL160_MAX_FCCO)
		rate = PLL160_MAX_FCCO;

	if (!rate) {
		clk->rate = 0;
		ret = 0;
		goto out;
	}

	clk_reg_enable1(clk);
	tmp_reg = __raw_readl(clk->scale_reg);

	if (rate == parent_rate) {
		/*enter direct bypass mode */
		tmp_reg |= ((1 << 14) | (1 << 15));
		__raw_writel(tmp_reg, clk->scale_reg);
		clk->rate = parent_rate;
		clk_reg_enable(clk);
		ret = 0;
		goto out;
	}

	i = 0;
	for (tmp_2p = 1; tmp_2p < 16; tmp_2p <<= 1) {
		if (rate * tmp_2p >= PLL160_MIN_FCCO)
			break;
		i++;
	}

	if (tmp_2p > 1)
		tmp_reg |= ((i - 1) << 11);
	else
		tmp_reg |= (1 << 14);	/*direct mode, no divide */

	tmp_m = rate * tmp_2p;
	tmp_m /= parent_rate;

	tmp_reg |= (tmp_m - 1) << 1;	/*calculate M */
	tmp_reg |= (1 << 16);	/*power up PLL */
	__raw_writel(tmp_reg, clk->scale_reg);

	if (clk_wait_for_pll_lock(clk) < 0) {
		clk_reg_disable(clk);
		clk_reg_disable1(clk);

		tmp_reg = __raw_readl(clk->scale_reg);
		tmp_reg &= ~0x1ffff;	/*clear all settings, power down */
		__raw_writel(tmp_reg, clk->scale_reg);
		clk->rate = 0;
		ret = -EFAULT;
		goto out;
	}

	clk->rate = (tmp_m * parent_rate) / tmp_2p;

	if (clk->flags & RATE_PROPAGATES)
		propagate_rate(clk);

	clk_reg_enable(clk);
	ret = 0;

out:
	return ret;
}