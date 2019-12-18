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
typedef  int u8 ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int OMAP_RTC_STATUS_1S_EVENT ; 
 int OMAP_RTC_STATUS_ALARM ; 
 int /*<<< orphan*/  OMAP_RTC_STATUS_REG ; 
 unsigned long RTC_AF ; 
 unsigned long RTC_IRQF ; 
 unsigned long RTC_UF ; 
 int rtc_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_update_irq (void*,int,unsigned long) ; 
 int /*<<< orphan*/  rtc_write (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t rtc_irq(int irq, void *rtc)
{
	unsigned long		events = 0;
	u8			irq_data;

	irq_data = rtc_read(OMAP_RTC_STATUS_REG);

	/* alarm irq? */
	if (irq_data & OMAP_RTC_STATUS_ALARM) {
		rtc_write(OMAP_RTC_STATUS_ALARM, OMAP_RTC_STATUS_REG);
		events |= RTC_IRQF | RTC_AF;
	}

	/* 1/sec periodic/update irq? */
	if (irq_data & OMAP_RTC_STATUS_1S_EVENT)
		events |= RTC_IRQF | RTC_UF;

	rtc_update_irq(rtc, 1, events);

	return IRQ_HANDLED;
}