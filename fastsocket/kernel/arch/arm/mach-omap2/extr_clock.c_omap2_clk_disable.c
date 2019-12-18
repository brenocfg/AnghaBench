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
struct clk {scalar_t__ usecount; scalar_t__ clkdm; struct clk* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  _omap2_clk_disable (struct clk*) ; 
 int /*<<< orphan*/  omap2_clkdm_clk_disable (scalar_t__,struct clk*) ; 

void omap2_clk_disable(struct clk *clk)
{
	if (clk->usecount > 0 && !(--clk->usecount)) {
		_omap2_clk_disable(clk);
		if (clk->parent)
			omap2_clk_disable(clk->parent);
		if (clk->clkdm)
			omap2_clkdm_clk_disable(clk->clkdm, clk);

	}
}