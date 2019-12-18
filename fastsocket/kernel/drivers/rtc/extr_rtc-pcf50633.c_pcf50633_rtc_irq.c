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
struct pcf50633_rtc {int /*<<< orphan*/  rtc_dev; } ;

/* Variables and functions */
#define  PCF50633_IRQ_ALARM 129 
#define  PCF50633_IRQ_SECOND 128 
 int RTC_AF ; 
 int RTC_IRQF ; 
 int RTC_UF ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void pcf50633_rtc_irq(int irq, void *data)
{
	struct pcf50633_rtc *rtc = data;

	switch (irq) {
	case PCF50633_IRQ_ALARM:
		rtc_update_irq(rtc->rtc_dev, 1, RTC_AF | RTC_IRQF);
		break;
	case PCF50633_IRQ_SECOND:
		rtc_update_irq(rtc->rtc_dev, 1, RTC_UF | RTC_IRQF);
		break;
	}
}