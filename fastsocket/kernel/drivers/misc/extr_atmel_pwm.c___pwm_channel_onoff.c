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
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  PWM_DIS ; 
 int /*<<< orphan*/  PWM_ENA ; 
 TYPE_1__* pwm ; 
 int /*<<< orphan*/  pwm_dumpregs (struct pwm_channel*,char*) ; 
 int /*<<< orphan*/  pwm_writel (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int pwmcheck (struct pwm_channel*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int __pwm_channel_onoff(struct pwm_channel *ch, int enabled)
{
	unsigned long	flags;
	int		t;

	/* OMITTED FUNCTIONALITY:  starting several channels in synch */

	spin_lock_irqsave(&pwm->lock, flags);
	t = pwmcheck(ch);
	if (t >= 0) {
		pwm_writel(pwm, enabled ? PWM_ENA : PWM_DIS, 1 << t);
		t = 0;
		pwm_dumpregs(ch, enabled ? "enable" : "disable");
	}
	spin_unlock_irqrestore(&pwm->lock, flags);

	return t;
}