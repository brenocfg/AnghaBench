#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pwm_channel {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  clk; int /*<<< orphan*/ ** handler; int /*<<< orphan*/ ** channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  PWM_DIS ; 
 int /*<<< orphan*/  PWM_IDR ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 TYPE_1__* pwm ; 
 int /*<<< orphan*/  pwm_writel (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int pwmcheck (struct pwm_channel*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int pwm_channel_free(struct pwm_channel *ch)
{
	unsigned long	flags;
	int		t;

	spin_lock_irqsave(&pwm->lock, flags);
	t = pwmcheck(ch);
	if (t >= 0) {
		pwm->channel[t] = NULL;
		pwm->handler[t] = NULL;

		/* channel and irq are always disabled when we return */
		pwm_writel(pwm, PWM_DIS, 1 << t);
		pwm_writel(pwm, PWM_IDR, 1 << t);

		clk_disable(pwm->clk);
		t = 0;
	}
	spin_unlock_irqrestore(&pwm->lock, flags);
	return t;
}