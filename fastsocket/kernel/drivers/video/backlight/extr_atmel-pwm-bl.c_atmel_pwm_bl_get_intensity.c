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
typedef  int u8 ;
struct backlight_device {int dummy; } ;
struct atmel_pwm_bl {int /*<<< orphan*/  pwmc; TYPE_1__* pdata; } ;
struct TYPE_2__ {int pwm_duty_min; int pwm_duty_max; scalar_t__ pwm_active_low; } ;

/* Variables and functions */
 int /*<<< orphan*/  PWM_CDTY ; 
 struct atmel_pwm_bl* bl_get_data (struct backlight_device*) ; 
 int pwm_channel_readl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_pwm_bl_get_intensity(struct backlight_device *bd)
{
	struct atmel_pwm_bl *pwmbl = bl_get_data(bd);
	u8 intensity;

	if (pwmbl->pdata->pwm_active_low) {
		intensity = pwm_channel_readl(&pwmbl->pwmc, PWM_CDTY) -
			pwmbl->pdata->pwm_duty_min;
	} else {
		intensity = pwmbl->pdata->pwm_duty_max -
			pwm_channel_readl(&pwmbl->pwmc, PWM_CDTY);
	}

	return intensity;
}