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
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP3430_GR_MOD ; 
 int /*<<< orphan*/  OMAP_RST_DPLL3 ; 
 int /*<<< orphan*/  RM_RSTCTRL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WKUP_MOD ; 
 scalar_t__ cpu_is_omap24xx () ; 
 scalar_t__ cpu_is_omap34xx () ; 
 int /*<<< orphan*/  omap2_clk_prepare_for_reboot () ; 
 int /*<<< orphan*/  prm_set_mod_reg_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void omap_prcm_arch_reset(char mode)
{
	s16 prcm_offs;
	omap2_clk_prepare_for_reboot();

	if (cpu_is_omap24xx())
		prcm_offs = WKUP_MOD;
	else if (cpu_is_omap34xx())
		prcm_offs = OMAP3430_GR_MOD;
	else
		WARN_ON(1);

	prm_set_mod_reg_bits(OMAP_RST_DPLL3, prcm_offs, RM_RSTCTRL);
}