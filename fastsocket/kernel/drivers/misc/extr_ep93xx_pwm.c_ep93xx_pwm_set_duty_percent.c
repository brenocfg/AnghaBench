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
typedef  int u32 ;
struct platform_device {int dummy; } ;
struct ep93xx_pwm {long duty_percent; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int ep93xx_pwm_read_tc (struct ep93xx_pwm*) ; 
 int /*<<< orphan*/  ep93xx_pwm_write_dc (struct ep93xx_pwm*,int) ; 
 struct ep93xx_pwm* platform_get_drvdata (struct platform_device*) ; 
 int strict_strtol (char const*,int,long*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static ssize_t ep93xx_pwm_set_duty_percent(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct ep93xx_pwm *pwm = platform_get_drvdata(pdev);
	long val;
	int err;

	err = strict_strtol(buf, 10, &val);
	if (err)
		return -EINVAL;

	if (val > 0 && val < 100) {
		u32 term = ep93xx_pwm_read_tc(pwm);
		ep93xx_pwm_write_dc(pwm, ((term + 1) * val / 100) - 1);
		pwm->duty_percent = val;
		return count;
	}

	return -EINVAL;
}