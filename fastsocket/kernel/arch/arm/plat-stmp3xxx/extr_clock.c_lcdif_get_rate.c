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
struct clk {int const scale_shift; long rate; scalar_t__ scale_reg; TYPE_1__* parent; } ;
struct TYPE_2__ {long rate; } ;

/* Variables and functions */
 int const BM_CLKCTRL_FRAC_PIXFRAC ; 
 int const BP_CLKCTRL_FRAC_PIXFRAC ; 
 scalar_t__ HW_CLKCTRL_FRAC ; 
 scalar_t__ REGS_CLKCTRL_BASE ; 
 int const __raw_readl (scalar_t__) ; 

__attribute__((used)) static long lcdif_get_rate(struct clk *clk)
{
	long rate = clk->parent->rate;
	long div;
	const int mask = 0xff;

	div = (__raw_readl(clk->scale_reg) >> clk->scale_shift) & mask;
	if (div) {
		rate /= div;
		div = (__raw_readl(REGS_CLKCTRL_BASE + HW_CLKCTRL_FRAC) &
			BM_CLKCTRL_FRAC_PIXFRAC) >> BP_CLKCTRL_FRAC_PIXFRAC;
		rate /= div;
	}
	clk->rate = rate;

	return rate;
}