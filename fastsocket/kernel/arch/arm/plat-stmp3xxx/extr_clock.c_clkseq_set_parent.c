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
struct clk {int saved_div; int bypass_shift; scalar_t__ bypass_reg; } ;
struct TYPE_2__ {scalar_t__ rate; } ;

/* Variables and functions */
 int BM_CLKCTRL_CPU_DIV_CPU ; 
 int BM_CLKCTRL_HBUS_DIV ; 
 int BM_CLKCTRL_HBUS_DIV_FRAC_EN ; 
 int EINVAL ; 
 scalar_t__ HW_CLKCTRL_CPU ; 
 scalar_t__ HW_CLKCTRL_HBUS ; 
 scalar_t__ REGS_CLKCTRL_BASE ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 struct clk cpu_clk ; 
 TYPE_1__ hclk ; 
 scalar_t__ machine_is_stmp378x () ; 
 struct clk osc_24M ; 

__attribute__((used)) static int clkseq_set_parent(struct clk *clk, struct clk *parent)
{
	int ret = -EINVAL;
	int shift = 8;

	/* bypass? */
	if (parent == &osc_24M)
		shift = 4;

	if (clk->bypass_reg) {
#ifdef CONFIG_ARCH_STMP378X
		u32 hbus_val, cpu_val;

		if (clk == &cpu_clk && shift == 4) {
			hbus_val = __raw_readl(REGS_CLKCTRL_BASE +
					HW_CLKCTRL_HBUS);
			cpu_val = __raw_readl(REGS_CLKCTRL_BASE +
					HW_CLKCTRL_CPU);

			hbus_val &= ~(BM_CLKCTRL_HBUS_DIV_FRAC_EN |
				      BM_CLKCTRL_HBUS_DIV);
			clk->saved_div = cpu_val & BM_CLKCTRL_CPU_DIV_CPU;
			cpu_val &= ~BM_CLKCTRL_CPU_DIV_CPU;
			cpu_val |= 1;

			if (machine_is_stmp378x()) {
				__raw_writel(hbus_val,
					REGS_CLKCTRL_BASE + HW_CLKCTRL_HBUS);
				__raw_writel(cpu_val,
					REGS_CLKCTRL_BASE + HW_CLKCTRL_CPU);
				hclk.rate = 0;
			}
		} else if (clk == &cpu_clk && shift == 8) {
			hbus_val = __raw_readl(REGS_CLKCTRL_BASE +
							HW_CLKCTRL_HBUS);
			cpu_val = __raw_readl(REGS_CLKCTRL_BASE +
							HW_CLKCTRL_CPU);
			hbus_val &= ~(BM_CLKCTRL_HBUS_DIV_FRAC_EN |
				      BM_CLKCTRL_HBUS_DIV);
			hbus_val |= 2;
			cpu_val &= ~BM_CLKCTRL_CPU_DIV_CPU;
			if (clk->saved_div)
				cpu_val |= clk->saved_div;
			else
				cpu_val |= 2;

			if (machine_is_stmp378x()) {
				__raw_writel(hbus_val,
					REGS_CLKCTRL_BASE + HW_CLKCTRL_HBUS);
				__raw_writel(cpu_val,
					REGS_CLKCTRL_BASE + HW_CLKCTRL_CPU);
				hclk.rate = 0;
			}
		}
#endif
		__raw_writel(1 << clk->bypass_shift, clk->bypass_reg + shift);

		ret = 0;
	}

	return ret;
}