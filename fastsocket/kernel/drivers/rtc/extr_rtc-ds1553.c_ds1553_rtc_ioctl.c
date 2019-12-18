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
struct rtc_plat_data {scalar_t__ irq; int /*<<< orphan*/  irqen; } ;
struct platform_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOIOCTLCMD ; 
 int /*<<< orphan*/  RTC_AF ; 
#define  RTC_AIE_OFF 131 
#define  RTC_AIE_ON 130 
 int /*<<< orphan*/  RTC_UF ; 
#define  RTC_UIE_OFF 129 
#define  RTC_UIE_ON 128 
 int /*<<< orphan*/  ds1553_rtc_update_alarm (struct rtc_plat_data*) ; 
 struct rtc_plat_data* platform_get_drvdata (struct platform_device*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int ds1553_rtc_ioctl(struct device *dev, unsigned int cmd,
			    unsigned long arg)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct rtc_plat_data *pdata = platform_get_drvdata(pdev);

	if (pdata->irq <= 0)
		return -ENOIOCTLCMD; /* fall back into rtc-dev's emulation */
	switch (cmd) {
	case RTC_AIE_OFF:
		pdata->irqen &= ~RTC_AF;
		ds1553_rtc_update_alarm(pdata);
		break;
	case RTC_AIE_ON:
		pdata->irqen |= RTC_AF;
		ds1553_rtc_update_alarm(pdata);
		break;
	case RTC_UIE_OFF:
		pdata->irqen &= ~RTC_UF;
		ds1553_rtc_update_alarm(pdata);
		break;
	case RTC_UIE_ON:
		pdata->irqen |= RTC_UF;
		ds1553_rtc_update_alarm(pdata);
		break;
	default:
		return -ENOIOCTLCMD;
	}
	return 0;
}