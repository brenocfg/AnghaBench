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
struct rtc_device {int dummy; } ;
struct platform_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int RTC_AF ; 
 int RTC_IRQF ; 
 int RTC_PF ; 
 int RTC_UF ; 
 struct rtc_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  rtc_update_irq (struct rtc_device*,int,int) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static ssize_t test_irq_store(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t count)
{
	int retval;
	struct platform_device *plat_dev = to_platform_device(dev);
	struct rtc_device *rtc = platform_get_drvdata(plat_dev);

	retval = count;
	if (strncmp(buf, "tick", 4) == 0)
		rtc_update_irq(rtc, 1, RTC_PF | RTC_IRQF);
	else if (strncmp(buf, "alarm", 5) == 0)
		rtc_update_irq(rtc, 1, RTC_AF | RTC_IRQF);
	else if (strncmp(buf, "update", 6) == 0)
		rtc_update_irq(rtc, 1, RTC_UF | RTC_IRQF);
	else
		retval = -EINVAL;

	return retval;
}