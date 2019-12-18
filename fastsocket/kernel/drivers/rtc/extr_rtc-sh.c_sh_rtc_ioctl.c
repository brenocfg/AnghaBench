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
struct sh_rtc {int /*<<< orphan*/  periodic_freq; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int ENOIOCTLCMD ; 
 int /*<<< orphan*/  PF_OXS ; 
#define  RTC_AIE_OFF 131 
#define  RTC_AIE_ON 130 
#define  RTC_UIE_OFF 129 
#define  RTC_UIE_ON 128 
 struct sh_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sh_rtc_setaie (struct device*,int) ; 
 int /*<<< orphan*/  sh_rtc_setcie (struct device*,int) ; 

__attribute__((used)) static int sh_rtc_ioctl(struct device *dev, unsigned int cmd, unsigned long arg)
{
	struct sh_rtc *rtc = dev_get_drvdata(dev);
	unsigned int ret = 0;

	switch (cmd) {
	case RTC_AIE_OFF:
	case RTC_AIE_ON:
		sh_rtc_setaie(dev, cmd == RTC_AIE_ON);
		break;
	case RTC_UIE_OFF:
		rtc->periodic_freq &= ~PF_OXS;
		sh_rtc_setcie(dev, 0);
		break;
	case RTC_UIE_ON:
		rtc->periodic_freq |= PF_OXS;
		sh_rtc_setcie(dev, 1);
		break;
	default:
		ret = -ENOIOCTLCMD;
	}

	return ret;
}