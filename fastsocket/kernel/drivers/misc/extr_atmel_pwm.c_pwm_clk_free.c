#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned int PWM_CPR_CLKA ; 
 unsigned int PWM_CPR_CLKB ; 
 int /*<<< orphan*/  PWM_MR ; 
 TYPE_1__* pwm ; 
 int pwm_readl (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwm_writel (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void pwm_clk_free(unsigned clk)
{
	unsigned long	flags;
	u32		mr;

	spin_lock_irqsave(&pwm->lock, flags);
	mr = pwm_readl(pwm, PWM_MR);
	if (clk == PWM_CPR_CLKA)
		pwm_writel(pwm, PWM_MR, mr & ~(0xffff << 0));
	if (clk == PWM_CPR_CLKB)
		pwm_writel(pwm, PWM_MR, mr & ~(0xffff << 16));
	spin_unlock_irqrestore(&pwm->lock, flags);
}