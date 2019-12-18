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
struct clockdomain {int /*<<< orphan*/  name; int /*<<< orphan*/  usecount; } ;
struct clk {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 int OMAP24XX_CLKSTCTRL_ENABLE_AUTO ; 
 int OMAP34XX_CLKSTCTRL_ENABLE_AUTO ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  _clkdm_del_autodeps (struct clockdomain*) ; 
 int /*<<< orphan*/  _omap2_clkdm_set_hwsup (struct clockdomain*,int) ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ cpu_is_omap24xx () ; 
 scalar_t__ cpu_is_omap34xx () ; 
 int omap2_clkdm_clktrctrl_read (struct clockdomain*) ; 
 int /*<<< orphan*/  omap2_clkdm_sleep (struct clockdomain*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwrdm_clkdm_state_switch (struct clockdomain*) ; 

int omap2_clkdm_clk_disable(struct clockdomain *clkdm, struct clk *clk)
{
	int v;

	/*
	 * XXX Rewrite this code to maintain a list of enabled
	 * downstream clocks for debugging purposes?
	 */

	if (!clkdm || !clk)
		return -EINVAL;

#ifdef DEBUG
	if (atomic_read(&clkdm->usecount) == 0) {
		WARN_ON(1); /* underflow */
		return -ERANGE;
	}
#endif

	if (atomic_dec_return(&clkdm->usecount) > 0)
		return 0;

	/* All downstream clocks of this clockdomain are now disabled */

	pr_debug("clockdomain: clkdm %s: clk %s now disabled\n", clkdm->name,
		 clk->name);

	v = omap2_clkdm_clktrctrl_read(clkdm);

	if ((cpu_is_omap34xx() && v == OMAP34XX_CLKSTCTRL_ENABLE_AUTO) ||
	    (cpu_is_omap24xx() && v == OMAP24XX_CLKSTCTRL_ENABLE_AUTO)) {
		/* Disable HW transitions when we are changing deps */
		_omap2_clkdm_set_hwsup(clkdm, 0);
		_clkdm_del_autodeps(clkdm);
		_omap2_clkdm_set_hwsup(clkdm, 1);
	} else {
		omap2_clkdm_sleep(clkdm);
	}

	pwrdm_clkdm_state_switch(clkdm);

	return 0;
}