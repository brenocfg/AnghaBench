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
struct gpio_private {int minor; } ;

/* Variables and functions */
 int EINVAL ; 
 int GPIO_MINOR_PWM0 ; 
#define  IO_PWM_SET_DUTY 130 
#define  IO_PWM_SET_MODE 129 
#define  IO_PWM_SET_PERIOD 128 
 int _IOC_NR (unsigned int) ; 
 int gpio_pwm_set_duty (unsigned long,int) ; 
 int gpio_pwm_set_mode (unsigned long,int) ; 
 int gpio_pwm_set_period (unsigned long,int) ; 

__attribute__((used)) static int gpio_pwm_ioctl(struct gpio_private *priv, unsigned int cmd,
	unsigned long arg)
{
	int pwm_port = priv->minor - GPIO_MINOR_PWM0;

	switch (_IOC_NR(cmd)) {
	case IO_PWM_SET_MODE:
		return gpio_pwm_set_mode(arg, pwm_port);
	case IO_PWM_SET_PERIOD:
		return gpio_pwm_set_period(arg, pwm_port);
	case IO_PWM_SET_DUTY:
		return gpio_pwm_set_duty(arg, pwm_port);
	default:
		return -EINVAL;
	}
	return 0;
}