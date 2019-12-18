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
struct clk {scalar_t__ use_cnt; struct clk* parent; int /*<<< orphan*/  csp_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  chipcHw_bypassClockDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chipcHw_pll1Disable () ; 
 int /*<<< orphan*/  chipcHw_pll2Disable () ; 
 int /*<<< orphan*/  chipcHw_setClockDisable (int /*<<< orphan*/ ) ; 
 scalar_t__ clk_is_pll1 (struct clk*) ; 
 scalar_t__ clk_is_pll2 (struct clk*) ; 
 int /*<<< orphan*/  clk_is_primary (struct clk*) ; 
 scalar_t__ clk_is_using_xtal (struct clk*) ; 

__attribute__((used)) static void __clk_disable(struct clk *clk)
{
	if (!clk)
		return;

	BUG_ON(clk->use_cnt == 0);

	if (--clk->use_cnt == 0) {
		if (clk_is_pll1(clk)) {	/* PLL1 */
			chipcHw_pll1Disable();
		} else if (clk_is_pll2(clk)) {	/* PLL2 */
			chipcHw_pll2Disable();
		} else if (clk_is_using_xtal(clk)) {	/* source is crystal */
			if (!clk_is_primary(clk))
				chipcHw_bypassClockDisable(clk->csp_id);
		} else {	/* source is PLL */
			chipcHw_setClockDisable(clk->csp_id);
		}
	}

	if (clk->parent)
		__clk_disable(clk->parent);
}