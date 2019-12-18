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
struct clk {unsigned int enable_bit; int /*<<< orphan*/  enable_reg; } ;

/* Variables and functions */
 unsigned int __raw_readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long omap1_uart_recalc(struct clk *clk)
{
	unsigned int val = __raw_readl(clk->enable_reg);
	return val & clk->enable_bit ? 48000000 : 12000000;
}