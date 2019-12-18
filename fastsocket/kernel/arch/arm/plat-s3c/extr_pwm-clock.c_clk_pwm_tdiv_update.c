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
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct pwm_tdiv_clk {TYPE_1__ clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  S3C2410_TCFG1 ; 
 unsigned long S3C2410_TCFG1_MUX_MASK ; 
 unsigned long S3C2410_TCFG1_SHIFT (int /*<<< orphan*/ ) ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long clk_pwm_tdiv_bits (struct pwm_tdiv_clk*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static void clk_pwm_tdiv_update(struct pwm_tdiv_clk *divclk)
{
	unsigned long tcfg1 = __raw_readl(S3C2410_TCFG1);
	unsigned long bits = clk_pwm_tdiv_bits(divclk);
	unsigned long flags;
	unsigned long shift =  S3C2410_TCFG1_SHIFT(divclk->clk.id);

	local_irq_save(flags);

	tcfg1 = __raw_readl(S3C2410_TCFG1);
	tcfg1 &= ~(S3C2410_TCFG1_MUX_MASK << shift);
	tcfg1 |= bits << shift;
	__raw_writel(tcfg1, S3C2410_TCFG1);

	local_irq_restore(flags);
}