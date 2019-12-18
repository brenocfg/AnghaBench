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
struct clk {int scale_shift; long rate; scalar_t__ scale_reg; TYPE_1__* parent; } ;
struct TYPE_2__ {int rate; } ;

/* Variables and functions */
 scalar_t__ HW_CLKCTRL_CPU ; 
 scalar_t__ REGS_CLKCTRL_BASE ; 
 int __raw_readl (scalar_t__) ; 

__attribute__((used)) static long cpu_get_rate(struct clk *clk)
{
	long rate = clk->parent->rate * 18;

	rate /= (__raw_readl(clk->scale_reg) >> clk->scale_shift) & 0x3f;
	rate /= __raw_readl(REGS_CLKCTRL_BASE + HW_CLKCTRL_CPU) & 0x3f;
	rate = ((rate + 9) / 10) * 10;
	clk->rate = rate;

	return rate;
}