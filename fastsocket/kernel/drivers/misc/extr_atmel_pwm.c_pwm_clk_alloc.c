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
 int EBUSY ; 
 int EINVAL ; 
 int PWM_CPR_CLKA ; 
 int PWM_CPR_CLKB ; 
 int /*<<< orphan*/  PWM_MR ; 
 TYPE_1__* pwm ; 
 int pwm_readl (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwm_writel (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int pwm_clk_alloc(unsigned prescale, unsigned div)
{
	unsigned long	flags;
	u32		mr;
	u32		val = (prescale << 8) | div;
	int		ret = -EBUSY;

	if (prescale >= 10 || div == 0 || div > 255)
		return -EINVAL;

	spin_lock_irqsave(&pwm->lock, flags);
	mr = pwm_readl(pwm, PWM_MR);
	if ((mr & 0xffff) == 0) {
		mr |= val;
		ret = PWM_CPR_CLKA;
	} else if ((mr & (0xffff << 16)) == 0) {
		mr |= val << 16;
		ret = PWM_CPR_CLKB;
	}
	if (ret > 0)
		pwm_writel(pwm, PWM_MR, mr);
	spin_unlock_irqrestore(&pwm->lock, flags);
	return ret;
}