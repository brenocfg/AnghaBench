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
typedef  int u32 ;

/* Variables and functions */
 int OMAP24XX_EN_GPT1 ; 
 int /*<<< orphan*/  PM_WKEN ; 
 int /*<<< orphan*/  WKUP_MOD ; 
 int /*<<< orphan*/  omap2_enter_full_retention () ; 
 int omap_readl (int) ; 
 int /*<<< orphan*/  omap_uart_prepare_suspend () ; 
 int /*<<< orphan*/  omap_writel (int,int) ; 
 int prm_read_mod_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prm_write_mod_reg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap2_pm_suspend(void)
{
	u32 wken_wkup, mir1;

	wken_wkup = prm_read_mod_reg(WKUP_MOD, PM_WKEN);
	prm_write_mod_reg(wken_wkup & ~OMAP24XX_EN_GPT1, WKUP_MOD, PM_WKEN);

	/* Mask GPT1 */
	mir1 = omap_readl(0x480fe0a4);
	omap_writel(1 << 5, 0x480fe0ac);

	omap_uart_prepare_suspend();
	omap2_enter_full_retention();

	omap_writel(mir1, 0x480fe0a4);
	prm_write_mod_reg(wken_wkup, WKUP_MOD, PM_WKEN);

	return 0;
}