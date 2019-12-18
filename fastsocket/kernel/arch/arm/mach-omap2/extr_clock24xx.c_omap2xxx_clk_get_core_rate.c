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
typedef  long long u32 ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_CLKSEL2 ; 
 long long CORE_CLK_SRC_32K ; 
 long long OMAP24XX_CORE_CLK_SRC_MASK ; 
 int /*<<< orphan*/  PLL_MOD ; 
 long long cm_read_mod_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long long omap2_get_dpll_rate (struct clk*) ; 

__attribute__((used)) static unsigned long omap2xxx_clk_get_core_rate(struct clk *clk)
{
	long long core_clk;
	u32 v;

	core_clk = omap2_get_dpll_rate(clk);

	v = cm_read_mod_reg(PLL_MOD, CM_CLKSEL2);
	v &= OMAP24XX_CORE_CLK_SRC_MASK;

	if (v == CORE_CLK_SRC_32K)
		core_clk = 32768;
	else
		core_clk *= v;

	return core_clk;
}