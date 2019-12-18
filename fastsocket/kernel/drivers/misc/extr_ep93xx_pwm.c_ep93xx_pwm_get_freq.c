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
typedef  int u16 ;
struct platform_device {int dummy; } ;
struct ep93xx_pwm {int /*<<< orphan*/  clk; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 scalar_t__ ep93xx_pwm_is_enabled (struct ep93xx_pwm*) ; 
 int ep93xx_pwm_read_tc (struct ep93xx_pwm*) ; 
 struct ep93xx_pwm* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static ssize_t ep93xx_pwm_get_freq(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct ep93xx_pwm *pwm = platform_get_drvdata(pdev);

	if (ep93xx_pwm_is_enabled(pwm)) {
		unsigned long rate = clk_get_rate(pwm->clk);
		u16 term = ep93xx_pwm_read_tc(pwm);

		return sprintf(buf, "%ld\n", rate / (term + 1));
	} else {
		return sprintf(buf, "disabled\n");
	}
}