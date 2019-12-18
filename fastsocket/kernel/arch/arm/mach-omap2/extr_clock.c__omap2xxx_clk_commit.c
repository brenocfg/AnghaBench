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
struct clk {int flags; } ;

/* Variables and functions */
 int DELAYED_APP ; 
 int /*<<< orphan*/  OMAP24XX_GR_MOD ; 
 int /*<<< orphan*/  OMAP24XX_VALID_CONFIG ; 
 int /*<<< orphan*/  OMAP2_PRCM_CLKCFG_CTRL_OFFSET ; 
 int /*<<< orphan*/  cpu_is_omap24xx () ; 
 int /*<<< orphan*/  prm_read_mod_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prm_write_mod_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _omap2xxx_clk_commit(struct clk *clk)
{
	if (!cpu_is_omap24xx())
		return;

	if (!(clk->flags & DELAYED_APP))
		return;

	prm_write_mod_reg(OMAP24XX_VALID_CONFIG, OMAP24XX_GR_MOD,
		OMAP2_PRCM_CLKCFG_CTRL_OFFSET);
	/* OCP barrier */
	prm_read_mod_reg(OMAP24XX_GR_MOD, OMAP2_PRCM_CLKCFG_CTRL_OFFSET);
}