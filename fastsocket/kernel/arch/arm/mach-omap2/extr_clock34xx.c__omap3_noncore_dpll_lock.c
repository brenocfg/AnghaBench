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
typedef  scalar_t__ u8 ;
struct clk {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPLL_LOCKED ; 
 int EINVAL ; 
 int /*<<< orphan*/  _omap3_dpll_write_clken (struct clk*,int /*<<< orphan*/ ) ; 
 int _omap3_wait_dpll_status (struct clk*,int) ; 
 struct clk dpll3_ck ; 
 int /*<<< orphan*/  omap3_dpll_allow_idle (struct clk*) ; 
 scalar_t__ omap3_dpll_autoidle_read (struct clk*) ; 
 int /*<<< orphan*/  omap3_dpll_deny_idle (struct clk*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _omap3_noncore_dpll_lock(struct clk *clk)
{
	u8 ai;
	int r;

	if (clk == &dpll3_ck)
		return -EINVAL;

	pr_debug("clock: locking DPLL %s\n", clk->name);

	ai = omap3_dpll_autoidle_read(clk);

	omap3_dpll_deny_idle(clk);

	_omap3_dpll_write_clken(clk, DPLL_LOCKED);

	r = _omap3_wait_dpll_status(clk, 1);

	if (ai)
		omap3_dpll_allow_idle(clk);

	return r;
}