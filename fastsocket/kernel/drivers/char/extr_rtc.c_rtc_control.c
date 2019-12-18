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
typedef  int /*<<< orphan*/  rtc_task_t ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENXIO ; 
 unsigned int RTC_IRQP_SET ; 
 unsigned int RTC_PIE_OFF ; 
 unsigned int RTC_PIE_ON ; 
 int /*<<< orphan*/ * rtc_callback ; 
 int rtc_do_ioctl (unsigned int,unsigned long,int) ; 
 int /*<<< orphan*/  rtc_task_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int rtc_control(rtc_task_t *task, unsigned int cmd, unsigned long arg)
{
#ifndef RTC_IRQ
	return -EIO;
#else
	unsigned long flags;
	if (cmd != RTC_PIE_ON && cmd != RTC_PIE_OFF && cmd != RTC_IRQP_SET)
		return -EINVAL;
	spin_lock_irqsave(&rtc_task_lock, flags);
	if (rtc_callback != task) {
		spin_unlock_irqrestore(&rtc_task_lock, flags);
		return -ENXIO;
	}
	spin_unlock_irqrestore(&rtc_task_lock, flags);
	return rtc_do_ioctl(cmd, arg, 1);
#endif
}