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
struct dpll_data {int autoidle_mask; int /*<<< orphan*/  autoidle_reg; } ;
struct clk {struct dpll_data* dpll_data; } ;

/* Variables and functions */
 int DPLL_AUTOIDLE_LOW_POWER_STOP ; 
 int __ffs (int) ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap3_dpll_allow_idle(struct clk *clk)
{
	const struct dpll_data *dd;
	u32 v;

	if (!clk || !clk->dpll_data)
		return;

	dd = clk->dpll_data;

	/*
	 * REVISIT: CORE DPLL can optionally enter low-power bypass
	 * by writing 0x5 instead of 0x1.  Add some mechanism to
	 * optionally enter this mode.
	 */
	v = __raw_readl(dd->autoidle_reg);
	v &= ~dd->autoidle_mask;
	v |= DPLL_AUTOIDLE_LOW_POWER_STOP << __ffs(dd->autoidle_mask);
	__raw_writel(v, dd->autoidle_reg);
}