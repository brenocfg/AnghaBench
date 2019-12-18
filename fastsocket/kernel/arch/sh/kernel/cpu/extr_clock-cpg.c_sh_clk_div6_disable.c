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
struct clk {int /*<<< orphan*/  enable_reg; } ;

/* Variables and functions */
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh_clk_div6_disable(struct clk *clk)
{
	unsigned long value;

	value = __raw_readl(clk->enable_reg);
	value |= 0x100; /* stop clock */
	value |= 0x3f; /* VDIV bits must be non-zero, overwrite divider */
	__raw_writel(value, clk->enable_reg);
}