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
struct clk {int enable_bit; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_CLKEN ; 
 int /*<<< orphan*/  CM_IDLEST ; 
 int EN_APLL_LOCKED ; 
 int OMAP24XX_ST_54M_APLL ; 
 int OMAP24XX_ST_96M_APLL ; 
 int /*<<< orphan*/  OMAP_CM_REGADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLL_MOD ; 
 struct clk apll54_ck ; 
 struct clk apll96_ck ; 
 int cm_read_mod_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_write_mod_reg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap2_cm_wait_idlest (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap2_clk_fixed_enable(struct clk *clk)
{
	u32 cval, apll_mask;

	apll_mask = EN_APLL_LOCKED << clk->enable_bit;

	cval = cm_read_mod_reg(PLL_MOD, CM_CLKEN);

	if ((cval & apll_mask) == apll_mask)
		return 0;   /* apll already enabled */

	cval &= ~apll_mask;
	cval |= apll_mask;
	cm_write_mod_reg(cval, PLL_MOD, CM_CLKEN);

	if (clk == &apll96_ck)
		cval = OMAP24XX_ST_96M_APLL;
	else if (clk == &apll54_ck)
		cval = OMAP24XX_ST_54M_APLL;

	omap2_cm_wait_idlest(OMAP_CM_REGADDR(PLL_MOD, CM_IDLEST), cval,
			     clk->name);

	/*
	 * REVISIT: Should we return an error code if omap2_wait_clock_ready()
	 * fails?
	 */
	return 0;
}