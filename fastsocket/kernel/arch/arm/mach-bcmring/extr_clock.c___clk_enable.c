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
struct clk {int /*<<< orphan*/  csp_id; int /*<<< orphan*/  rate_hz; int /*<<< orphan*/  use_cnt; struct clk* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  chipcHw_bypassClockEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chipcHw_pll1Enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chipcHw_pll2Enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chipcHw_setClockEnable (int /*<<< orphan*/ ) ; 
 scalar_t__ clk_is_pll1 (struct clk*) ; 
 scalar_t__ clk_is_pll2 (struct clk*) ; 
 int /*<<< orphan*/  clk_is_primary (struct clk*) ; 
 scalar_t__ clk_is_using_xtal (struct clk*) ; 

__attribute__((used)) static void __clk_enable(struct clk *clk)
{
	if (!clk)
		return;

	/* enable parent clock first */
	if (clk->parent)
		__clk_enable(clk->parent);

	if (clk->use_cnt++ == 0) {
		if (clk_is_pll1(clk)) {	/* PLL1 */
			chipcHw_pll1Enable(clk->rate_hz, 0);
		} else if (clk_is_pll2(clk)) {	/* PLL2 */
			chipcHw_pll2Enable(clk->rate_hz);
		} else if (clk_is_using_xtal(clk)) {	/* source is crystal */
			if (!clk_is_primary(clk))
				chipcHw_bypassClockEnable(clk->csp_id);
		} else {	/* source is PLL */
			chipcHw_setClockEnable(clk->csp_id);
		}
	}
}