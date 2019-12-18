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
struct pxa_rtc {int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOIOCTLCMD ; 
#define  RTC_AIE_OFF 131 
#define  RTC_AIE_ON 130 
#define  RTC_UIE_OFF 129 
#define  RTC_UIE_ON 128 
 int /*<<< orphan*/  RTSR_HZE ; 
 int /*<<< orphan*/  RTSR_RDALE1 ; 
 struct pxa_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rtsr_clear_bits (struct pxa_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsr_set_bits (struct pxa_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pxa_rtc_ioctl(struct device *dev, unsigned int cmd,
		unsigned long arg)
{
	struct pxa_rtc *pxa_rtc = dev_get_drvdata(dev);
	int ret = 0;

	spin_lock_irq(&pxa_rtc->lock);
	switch (cmd) {
	case RTC_AIE_OFF:
		rtsr_clear_bits(pxa_rtc, RTSR_RDALE1);
		break;
	case RTC_AIE_ON:
		rtsr_set_bits(pxa_rtc, RTSR_RDALE1);
		break;
	case RTC_UIE_OFF:
		rtsr_clear_bits(pxa_rtc, RTSR_HZE);
		break;
	case RTC_UIE_ON:
		rtsr_set_bits(pxa_rtc, RTSR_HZE);
		break;
	default:
		ret = -ENOIOCTLCMD;
	}

	spin_unlock_irq(&pxa_rtc->lock);
	return ret;
}