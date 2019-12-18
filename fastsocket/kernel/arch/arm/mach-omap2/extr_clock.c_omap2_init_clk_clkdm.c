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
struct clockdomain {int dummy; } ;
struct clk {int /*<<< orphan*/  clkdm_name; int /*<<< orphan*/  name; struct clockdomain* clkdm; } ;

/* Variables and functions */
 struct clockdomain* clkdm_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void omap2_init_clk_clkdm(struct clk *clk)
{
	struct clockdomain *clkdm;

	if (!clk->clkdm_name)
		return;

	clkdm = clkdm_lookup(clk->clkdm_name);
	if (clkdm) {
		pr_debug("clock: associated clk %s to clkdm %s\n",
			 clk->name, clk->clkdm_name);
		clk->clkdm = clkdm;
	} else {
		pr_debug("clock: could not associate clk %s to "
			 "clkdm %s\n", clk->name, clk->clkdm_name);
	}
}