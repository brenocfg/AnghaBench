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
typedef  long u32 ;
struct platform_device {int dummy; } ;
struct ep93xx_pwm {long duty_percent; int /*<<< orphan*/  clk; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 long EP93XX_PWM_MAX_COUNT ; 
 long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ep93xx_pwm_disable (struct ep93xx_pwm*) ; 
 int /*<<< orphan*/  ep93xx_pwm_enable (struct ep93xx_pwm*) ; 
 int /*<<< orphan*/  ep93xx_pwm_is_enabled (struct ep93xx_pwm*) ; 
 long ep93xx_pwm_read_tc (struct ep93xx_pwm*) ; 
 int /*<<< orphan*/  ep93xx_pwm_write_dc (struct ep93xx_pwm*,long) ; 
 int /*<<< orphan*/  ep93xx_pwm_write_tc (struct ep93xx_pwm*,long) ; 
 struct ep93xx_pwm* platform_get_drvdata (struct platform_device*) ; 
 int strict_strtol (char const*,int,long*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static ssize_t ep93xx_pwm_set_freq(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct ep93xx_pwm *pwm = platform_get_drvdata(pdev);
	long val;
	int err;

	err = strict_strtol(buf, 10, &val);
	if (err)
		return -EINVAL;

	if (val == 0) {
		ep93xx_pwm_disable(pwm);
	} else if (val <= (clk_get_rate(pwm->clk) / 2)) {
		u32 term, duty;

		val = (clk_get_rate(pwm->clk) / val) - 1;
		if (val > EP93XX_PWM_MAX_COUNT)
			val = EP93XX_PWM_MAX_COUNT;
		if (val < 1)
			val = 1;

		term = ep93xx_pwm_read_tc(pwm);
		duty = ((val + 1) * pwm->duty_percent / 100) - 1;

		/* If pwm is running, order is important */
		if (val > term) {
			ep93xx_pwm_write_tc(pwm, val);
			ep93xx_pwm_write_dc(pwm, duty);
		} else {
			ep93xx_pwm_write_dc(pwm, duty);
			ep93xx_pwm_write_tc(pwm, val);
		}

		if (!ep93xx_pwm_is_enabled(pwm))
			ep93xx_pwm_enable(pwm);
	} else {
		return -EINVAL;
	}

	return count;
}