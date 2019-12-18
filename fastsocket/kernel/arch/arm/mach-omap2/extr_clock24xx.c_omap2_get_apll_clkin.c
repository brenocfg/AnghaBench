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
 int APLLS_CLKIN_12MHZ ; 
 int APLLS_CLKIN_13MHZ ; 
 int APLLS_CLKIN_19_2MHZ ; 
 int /*<<< orphan*/  CM_CLKSEL1 ; 
 int OMAP24XX_APLLS_CLKIN_MASK ; 
 int OMAP24XX_APLLS_CLKIN_SHIFT ; 
 int /*<<< orphan*/  PLL_MOD ; 
 int cm_read_mod_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 omap2_get_apll_clkin(void)
{
	u32 aplls, srate = 0;

	aplls = cm_read_mod_reg(PLL_MOD, CM_CLKSEL1);
	aplls &= OMAP24XX_APLLS_CLKIN_MASK;
	aplls >>= OMAP24XX_APLLS_CLKIN_SHIFT;

	if (aplls == APLLS_CLKIN_19_2MHZ)
		srate = 19200000;
	else if (aplls == APLLS_CLKIN_13MHZ)
		srate = 13000000;
	else if (aplls == APLLS_CLKIN_12MHZ)
		srate = 12000000;

	return srate;
}