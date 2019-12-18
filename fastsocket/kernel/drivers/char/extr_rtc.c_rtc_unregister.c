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
 unsigned char CMOS_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMOS_WRITE (unsigned char,int /*<<< orphan*/ ) ; 
 int EIO ; 
 int ENXIO ; 
 unsigned char RTC_AIE ; 
 int /*<<< orphan*/  RTC_CONTROL ; 
 int /*<<< orphan*/  RTC_INTR_FLAGS ; 
 int RTC_IS_OPEN ; 
 unsigned char RTC_PIE ; 
 int RTC_TIMER_ON ; 
 unsigned char RTC_UIE ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hpet_mask_rtc_irq_bit (unsigned char) ; 
 int /*<<< orphan*/ * rtc_callback ; 
 int /*<<< orphan*/  rtc_irq_timer ; 
 int /*<<< orphan*/  rtc_lock ; 
 int rtc_status ; 
 int /*<<< orphan*/  rtc_task_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int rtc_unregister(rtc_task_t *task)
{
#ifndef RTC_IRQ
	return -EIO;
#else
	unsigned char tmp;

	spin_lock_irq(&rtc_lock);
	spin_lock(&rtc_task_lock);
	if (rtc_callback != task) {
		spin_unlock(&rtc_task_lock);
		spin_unlock_irq(&rtc_lock);
		return -ENXIO;
	}
	rtc_callback = NULL;

	/* disable controls */
	if (!hpet_mask_rtc_irq_bit(RTC_PIE | RTC_AIE | RTC_UIE)) {
		tmp = CMOS_READ(RTC_CONTROL);
		tmp &= ~RTC_PIE;
		tmp &= ~RTC_AIE;
		tmp &= ~RTC_UIE;
		CMOS_WRITE(tmp, RTC_CONTROL);
		CMOS_READ(RTC_INTR_FLAGS);
	}
	if (rtc_status & RTC_TIMER_ON) {
		rtc_status &= ~RTC_TIMER_ON;
		del_timer(&rtc_irq_timer);
	}
	rtc_status &= ~RTC_IS_OPEN;
	spin_unlock(&rtc_task_lock);
	spin_unlock_irq(&rtc_lock);
	return 0;
#endif
}