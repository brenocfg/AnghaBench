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
 int /*<<< orphan*/  R14_24XX_MCBSP2_FSX ; 
 int /*<<< orphan*/  V14_24XX_GPIO117 ; 
 int /*<<< orphan*/  V15_24XX_MCBSP2_DX ; 
 int /*<<< orphan*/  W15_24XX_MCBSP2_DR ; 
 int /*<<< orphan*/  Y15_24XX_MCBSP2_CLKX ; 
 int /*<<< orphan*/  omap_cfg_reg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap2_mcbsp2_mux_setup(void)
{
	omap_cfg_reg(Y15_24XX_MCBSP2_CLKX);
	omap_cfg_reg(R14_24XX_MCBSP2_FSX);
	omap_cfg_reg(W15_24XX_MCBSP2_DR);
	omap_cfg_reg(V15_24XX_MCBSP2_DX);
	omap_cfg_reg(V14_24XX_GPIO117);
	/*
	 * TODO: Need to add MUX settings for OMAP 2430 SDP
	 */
}