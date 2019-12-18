#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {TYPE_1__* ptr; } ;
struct clockdomain {int flags; TYPE_2__ pwrdm; int /*<<< orphan*/  clktrctrl_mask; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  prcm_offs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int CLKDM_CAN_FORCE_WAKEUP ; 
 int /*<<< orphan*/  CM_CLKSTCTRL ; 
 int EINVAL ; 
 int /*<<< orphan*/  OMAP24XX_FORCESTATE ; 
 int OMAP34XX_CLKSTCTRL_FORCE_WAKEUP ; 
 int /*<<< orphan*/  PM_PWSTCTRL ; 
 int __ffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_clear_mod_reg_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_rmw_mod_reg_bits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_is_omap24xx () ; 
 scalar_t__ cpu_is_omap34xx () ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

int omap2_clkdm_wakeup(struct clockdomain *clkdm)
{
	if (!clkdm)
		return -EINVAL;

	if (!(clkdm->flags & CLKDM_CAN_FORCE_WAKEUP)) {
		pr_debug("clockdomain: %s does not support forcing "
			 "wakeup via software\n", clkdm->name);
		return -EINVAL;
	}

	pr_debug("clockdomain: forcing wakeup on %s\n", clkdm->name);

	if (cpu_is_omap24xx()) {

		cm_clear_mod_reg_bits(OMAP24XX_FORCESTATE,
				      clkdm->pwrdm.ptr->prcm_offs, PM_PWSTCTRL);

	} else if (cpu_is_omap34xx()) {

		u32 v = (OMAP34XX_CLKSTCTRL_FORCE_WAKEUP <<
			 __ffs(clkdm->clktrctrl_mask));

		cm_rmw_mod_reg_bits(clkdm->clktrctrl_mask, v,
				    clkdm->pwrdm.ptr->prcm_offs, CM_CLKSTCTRL);

	} else {
		BUG();
	};

	return 0;
}