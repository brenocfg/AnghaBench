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
struct clk {int enable_bit; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_CLKEN ; 
 int EN_APLL_LOCKED ; 
 int /*<<< orphan*/  PLL_MOD ; 
 int cm_read_mod_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_write_mod_reg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap2_clk_fixed_disable(struct clk *clk)
{
	u32 cval;

	cval = cm_read_mod_reg(PLL_MOD, CM_CLKEN);
	cval &= ~(EN_APLL_LOCKED << clk->enable_bit);
	cm_write_mod_reg(cval, PLL_MOD, CM_CLKEN);
}