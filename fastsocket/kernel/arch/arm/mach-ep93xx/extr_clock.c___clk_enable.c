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
typedef  int /*<<< orphan*/  u32 ;
struct clk {scalar_t__ enable_reg; scalar_t__ sw_locked; int /*<<< orphan*/  enable_mask; struct clk* parent; int /*<<< orphan*/  users; } ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ep93xx_syscon_swlocked_write (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void __clk_enable(struct clk *clk)
{
	if (!clk->users++) {
		if (clk->parent)
			__clk_enable(clk->parent);

		if (clk->enable_reg) {
			u32 v;

			v = __raw_readl(clk->enable_reg);
			v |= clk->enable_mask;
			if (clk->sw_locked)
				ep93xx_syscon_swlocked_write(v, clk->enable_reg);
			else
				__raw_writel(v, clk->enable_reg);
		}
	}
}