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
typedef  scalar_t__ u8 ;
struct clk {int /*<<< orphan*/  name; TYPE_1__* dpll_data; } ;
struct TYPE_2__ {int modes; } ;

/* Variables and functions */
 int DPLL_LOW_POWER_BYPASS ; 
 int EINVAL ; 
 int /*<<< orphan*/  _omap3_dpll_write_clken (struct clk*,int) ; 
 int _omap3_wait_dpll_status (struct clk*,int /*<<< orphan*/ ) ; 
 struct clk dpll3_ck ; 
 int /*<<< orphan*/  omap3_dpll_allow_idle (struct clk*) ; 
 scalar_t__ omap3_dpll_autoidle_read (struct clk*) ; 
 int /*<<< orphan*/  omap3_dpll_deny_idle (struct clk*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _omap3_noncore_dpll_bypass(struct clk *clk)
{
	int r;
	u8 ai;

	if (clk == &dpll3_ck)
		return -EINVAL;

	if (!(clk->dpll_data->modes & (1 << DPLL_LOW_POWER_BYPASS)))
		return -EINVAL;

	pr_debug("clock: configuring DPLL %s for low-power bypass\n",
		 clk->name);

	ai = omap3_dpll_autoidle_read(clk);

	_omap3_dpll_write_clken(clk, DPLL_LOW_POWER_BYPASS);

	r = _omap3_wait_dpll_status(clk, 0);

	if (ai)
		omap3_dpll_allow_idle(clk);
	else
		omap3_dpll_deny_idle(clk);

	return r;
}