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
struct pll_data {int input_rate; scalar_t__ base; } ;
struct clk {int rate; int flags; scalar_t__ div_reg; TYPE_1__* parent; scalar_t__ pll_data; } ;
struct TYPE_2__ {int rate; struct pll_data* pll_data; } ;

/* Variables and functions */
 int PLLDIV_EN ; 
 int PLLDIV_RATIO_MASK ; 
 int PRE_PLL ; 
 scalar_t__ WARN_ON (int) ; 
 int __raw_readl (scalar_t__) ; 

__attribute__((used)) static void clk_sysclk_recalc(struct clk *clk)
{
	u32 v, plldiv;
	struct pll_data *pll;

	/* If this is the PLL base clock, no more calculations needed */
	if (clk->pll_data)
		return;

	if (WARN_ON(!clk->parent))
		return;

	clk->rate = clk->parent->rate;

	/* Otherwise, the parent must be a PLL */
	if (WARN_ON(!clk->parent->pll_data))
		return;

	pll = clk->parent->pll_data;

	/* If pre-PLL, source clock is before the multiplier and divider(s) */
	if (clk->flags & PRE_PLL)
		clk->rate = pll->input_rate;

	if (!clk->div_reg)
		return;

	v = __raw_readl(pll->base + clk->div_reg);
	if (v & PLLDIV_EN) {
		plldiv = (v & PLLDIV_RATIO_MASK) + 1;
		if (plldiv)
			clk->rate /= plldiv;
	}
}