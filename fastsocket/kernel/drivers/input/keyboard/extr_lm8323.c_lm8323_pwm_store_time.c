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
struct lm8323_pwm {unsigned long fade_time; } ;
struct led_classdev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct lm8323_pwm* cdev_to_pwm (struct led_classdev*) ; 
 struct led_classdev* dev_get_drvdata (struct device*) ; 
 int strict_strtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static ssize_t lm8323_pwm_store_time(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t len)
{
	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	struct lm8323_pwm *pwm = cdev_to_pwm(led_cdev);
	int ret;
	unsigned long time;

	ret = strict_strtoul(buf, 10, &time);
	/* Numbers only, please. */
	if (ret)
		return -EINVAL;

	pwm->fade_time = time;

	return strlen(buf);
}