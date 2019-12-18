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

/* Variables and functions */
 int AU1000_SRC_CLK ; 
 unsigned long CONFIG_SOC_AU1000_FREQUENCY ; 
 int /*<<< orphan*/  SYS_CPUPLL ; 
 int /*<<< orphan*/  SYS_POWERCTRL ; 
 scalar_t__ au1xxx_cpu_has_pll_wo () ; 
 int au_readl (int /*<<< orphan*/ ) ; 
 unsigned long mips_hpt_frequency ; 
 int /*<<< orphan*/  set_au1x00_speed (unsigned long) ; 
 int /*<<< orphan*/  set_au1x00_uart_baud_base (unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  time_lock ; 

unsigned long au1xxx_calc_clock(void)
{
	unsigned long cpu_speed;
	unsigned long flags;

	spin_lock_irqsave(&time_lock, flags);

	/*
	 * On early Au1000, sys_cpupll was write-only. Since these
	 * silicon versions of Au1000 are not sold by AMD, we don't bend
	 * over backwards trying to determine the frequency.
	 */
	if (au1xxx_cpu_has_pll_wo())
#ifdef CONFIG_SOC_AU1000_FREQUENCY
		cpu_speed = CONFIG_SOC_AU1000_FREQUENCY;
#else
		cpu_speed = 396000000;
#endif
	else
		cpu_speed = (au_readl(SYS_CPUPLL) & 0x0000003f) * AU1000_SRC_CLK;

	/* On Alchemy CPU:counter ratio is 1:1 */
	mips_hpt_frequency = cpu_speed;
	/* Equation: Baudrate = CPU / (SD * 2 * CLKDIV * 16) */
	set_au1x00_uart_baud_base(cpu_speed / (2 * ((int)(au_readl(SYS_POWERCTRL)
							  & 0x03) + 2) * 16));

	spin_unlock_irqrestore(&time_lock, flags);

	set_au1x00_speed(cpu_speed);

	return cpu_speed;
}