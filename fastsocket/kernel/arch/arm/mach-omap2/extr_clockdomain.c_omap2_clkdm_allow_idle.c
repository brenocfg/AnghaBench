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
struct clockdomain {int flags; int /*<<< orphan*/  usecount; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int CLKDM_CAN_ENABLE_AUTO ; 
 int /*<<< orphan*/  _clkdm_add_autodeps (struct clockdomain*) ; 
 int /*<<< orphan*/  _omap2_clkdm_set_hwsup (struct clockdomain*,int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwrdm_clkdm_state_switch (struct clockdomain*) ; 

void omap2_clkdm_allow_idle(struct clockdomain *clkdm)
{
	if (!clkdm)
		return;

	if (!(clkdm->flags & CLKDM_CAN_ENABLE_AUTO)) {
		pr_debug("clock: automatic idle transitions cannot be enabled "
			 "on clockdomain %s\n", clkdm->name);
		return;
	}

	pr_debug("clockdomain: enabling automatic idle transitions for %s\n",
		 clkdm->name);

	if (atomic_read(&clkdm->usecount) > 0)
		_clkdm_add_autodeps(clkdm);

	_omap2_clkdm_set_hwsup(clkdm, 1);

	pwrdm_clkdm_state_switch(clkdm);
}