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
struct clk {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  S3C2410_TCFG0 ; 
 unsigned long S3C2410_TCFG_PRESCALER0_MASK ; 
 unsigned long S3C2410_TCFG_PRESCALER1_MASK ; 
 unsigned long S3C2410_TCFG_PRESCALER1_SHIFT ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 unsigned long clk_pwm_scaler_round_rate (struct clk*,unsigned long) ; 
 struct clk* clk_timer_scaler ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static int clk_pwm_scaler_set_rate(struct clk *clk, unsigned long rate)
{
	unsigned long round = clk_pwm_scaler_round_rate(clk, rate);
	unsigned long tcfg0;
	unsigned long divisor;
	unsigned long flags;

	divisor = clk_get_rate(clk->parent) / round;
	divisor--;

	local_irq_save(flags);
	tcfg0 = __raw_readl(S3C2410_TCFG0);

	if (clk == &clk_timer_scaler[1]) {
		tcfg0 &= ~S3C2410_TCFG_PRESCALER1_MASK;
		tcfg0 |= divisor << S3C2410_TCFG_PRESCALER1_SHIFT;
	} else {
		tcfg0 &= ~S3C2410_TCFG_PRESCALER0_MASK;
		tcfg0 |= divisor;
	}

	__raw_writel(tcfg0, S3C2410_TCFG0);
	local_irq_restore(flags);

	return 0;
}