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

/* Variables and functions */
 int /*<<< orphan*/  CORE_MOD ; 
 int /*<<< orphan*/  OMAP3430ES2_USBHOST_MOD ; 
 int /*<<< orphan*/  OMAP3430_PER_MOD ; 
 scalar_t__ OMAP3430_REV_ES1_0 ; 
 int /*<<< orphan*/  WKUP_MOD ; 
 scalar_t__ omap_rev () ; 
 int prcm_clear_mod_irqs (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int _prcm_int_handle_wakeup(void)
{
	int c;

	c = prcm_clear_mod_irqs(WKUP_MOD, 1);
	c += prcm_clear_mod_irqs(CORE_MOD, 1);
	c += prcm_clear_mod_irqs(OMAP3430_PER_MOD, 1);
	if (omap_rev() > OMAP3430_REV_ES1_0) {
		c += prcm_clear_mod_irqs(CORE_MOD, 3);
		c += prcm_clear_mod_irqs(OMAP3430ES2_USBHOST_MOD, 1);
	}

	return c;
}