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
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOIOCTLCMD ; 
 int /*<<< orphan*/  OIER ; 
 int /*<<< orphan*/  OIER_E1 ; 
 unsigned long OSCR ; 
 unsigned long OSMR1 ; 
#define  RTC_AIE_OFF 135 
#define  RTC_AIE_ON 134 
#define  RTC_IRQP_READ 133 
#define  RTC_IRQP_SET 132 
#define  RTC_PIE_OFF 131 
#define  RTC_PIE_ON 130 
#define  RTC_UIE_OFF 129 
#define  RTC_UIE_ON 128 
 int /*<<< orphan*/  RTSR ; 
 int /*<<< orphan*/  RTSR_ALE ; 
 int /*<<< orphan*/  RTSR_HZE ; 
 int put_user (unsigned long,unsigned long*) ; 
 unsigned long rtc_freq ; 
 int rtc_timer1_count ; 
 int /*<<< orphan*/  sa1100_rtc_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 unsigned long timer_freq ; 

__attribute__((used)) static int sa1100_rtc_ioctl(struct device *dev, unsigned int cmd,
		unsigned long arg)
{
	switch(cmd) {
	case RTC_AIE_OFF:
		spin_lock_irq(&sa1100_rtc_lock);
		RTSR &= ~RTSR_ALE;
		spin_unlock_irq(&sa1100_rtc_lock);
		return 0;
	case RTC_AIE_ON:
		spin_lock_irq(&sa1100_rtc_lock);
		RTSR |= RTSR_ALE;
		spin_unlock_irq(&sa1100_rtc_lock);
		return 0;
	case RTC_UIE_OFF:
		spin_lock_irq(&sa1100_rtc_lock);
		RTSR &= ~RTSR_HZE;
		spin_unlock_irq(&sa1100_rtc_lock);
		return 0;
	case RTC_UIE_ON:
		spin_lock_irq(&sa1100_rtc_lock);
		RTSR |= RTSR_HZE;
		spin_unlock_irq(&sa1100_rtc_lock);
		return 0;
	case RTC_PIE_OFF:
		spin_lock_irq(&sa1100_rtc_lock);
		OIER &= ~OIER_E1;
		spin_unlock_irq(&sa1100_rtc_lock);
		return 0;
	case RTC_PIE_ON:
		spin_lock_irq(&sa1100_rtc_lock);
		OSMR1 = timer_freq / rtc_freq + OSCR;
		OIER |= OIER_E1;
		rtc_timer1_count = 1;
		spin_unlock_irq(&sa1100_rtc_lock);
		return 0;
	case RTC_IRQP_READ:
		return put_user(rtc_freq, (unsigned long *)arg);
	case RTC_IRQP_SET:
		if (arg < 1 || arg > timer_freq)
			return -EINVAL;
		rtc_freq = arg;
		return 0;
	}
	return -ENOIOCTLCMD;
}