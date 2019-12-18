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
typedef  int u32 ;
struct stmp3xxx_rtc_data {int irq_count; int /*<<< orphan*/  rtc; scalar_t__ io; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int BM_RTC_CTRL_ALARM_IRQ ; 
 int BM_RTC_CTRL_ONEMSEC_IRQ ; 
 scalar_t__ HW_RTC_CTRL ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int RTC_AF ; 
 int RTC_IRQF ; 
 int RTC_UF ; 
 int __raw_readl (scalar_t__) ; 
 struct stmp3xxx_rtc_data* dev_get_drvdata (void*) ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stmp3xxx_clearl (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t stmp3xxx_rtc_interrupt(int irq, void *dev_id)
{
	struct stmp3xxx_rtc_data *rtc_data = dev_get_drvdata(dev_id);
	u32 status;
	u32 events = 0;

	status = __raw_readl(rtc_data->io + HW_RTC_CTRL) &
			(BM_RTC_CTRL_ALARM_IRQ | BM_RTC_CTRL_ONEMSEC_IRQ);

	if (status & BM_RTC_CTRL_ALARM_IRQ) {
		stmp3xxx_clearl(BM_RTC_CTRL_ALARM_IRQ,
				rtc_data->io + HW_RTC_CTRL);
		events |= RTC_AF | RTC_IRQF;
	}

	if (status & BM_RTC_CTRL_ONEMSEC_IRQ) {
		stmp3xxx_clearl(BM_RTC_CTRL_ONEMSEC_IRQ,
				rtc_data->io + HW_RTC_CTRL);
		if (++rtc_data->irq_count % 1000 == 0) {
			events |= RTC_UF | RTC_IRQF;
			rtc_data->irq_count = 0;
		}
	}

	if (events)
		rtc_update_irq(rtc_data->rtc, 1, events);

	return IRQ_HANDLED;
}