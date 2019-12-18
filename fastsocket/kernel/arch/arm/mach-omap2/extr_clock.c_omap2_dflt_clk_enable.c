#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct clk {int flags; int enable_bit; TYPE_1__* ops; int /*<<< orphan*/ * enable_reg; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {scalar_t__ find_idlest; } ;

/* Variables and functions */
 int INVERT_ENABLE ; 
 int __raw_readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap2_module_wait_ready (struct clk*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int omap2_dflt_clk_enable(struct clk *clk)
{
	u32 v;

	if (unlikely(clk->enable_reg == NULL)) {
		pr_err("clock.c: Enable for %s without enable code\n",
		       clk->name);
		return 0; /* REVISIT: -EINVAL */
	}

	v = __raw_readl(clk->enable_reg);
	if (clk->flags & INVERT_ENABLE)
		v &= ~(1 << clk->enable_bit);
	else
		v |= (1 << clk->enable_bit);
	__raw_writel(v, clk->enable_reg);
	v = __raw_readl(clk->enable_reg); /* OCP barrier */

	if (clk->ops->find_idlest)
		omap2_module_wait_ready(clk);

	return 0;
}