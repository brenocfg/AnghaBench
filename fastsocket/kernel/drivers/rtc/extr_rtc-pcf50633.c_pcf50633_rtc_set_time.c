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
struct rtc_time {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_year; int /*<<< orphan*/  tm_mon; int /*<<< orphan*/  tm_mday; } ;
struct pcf50633_time {int /*<<< orphan*/ * time; } ;
struct pcf50633_rtc {int /*<<< orphan*/  pcf; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCF50633_IRQ_ALARM ; 
 int /*<<< orphan*/  PCF50633_IRQ_SECOND ; 
 int /*<<< orphan*/  PCF50633_REG_RTCSC ; 
 size_t PCF50633_TI_DAY ; 
 int /*<<< orphan*/  PCF50633_TI_EXTENT ; 
 size_t PCF50633_TI_HOUR ; 
 size_t PCF50633_TI_MIN ; 
 size_t PCF50633_TI_MONTH ; 
 size_t PCF50633_TI_SEC ; 
 size_t PCF50633_TI_YEAR ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pcf50633_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  pcf50633_irq_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pcf50633_irq_mask_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcf50633_irq_unmask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pcf50633_write_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc2pcf_time (struct pcf50633_time*,struct rtc_time*) ; 

__attribute__((used)) static int pcf50633_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct pcf50633_rtc *rtc;
	struct pcf50633_time pcf_tm;
	int second_masked, alarm_masked, ret = 0;

	rtc = dev_get_drvdata(dev);

	dev_dbg(dev, "RTC_TIME: %u.%u.%u %u:%u:%u\n",
		tm->tm_mday, tm->tm_mon, tm->tm_year,
		tm->tm_hour, tm->tm_min, tm->tm_sec);

	rtc2pcf_time(&pcf_tm, tm);

	dev_dbg(dev, "PCF_TIME: %02x.%02x.%02x %02x:%02x:%02x\n",
		pcf_tm.time[PCF50633_TI_DAY],
		pcf_tm.time[PCF50633_TI_MONTH],
		pcf_tm.time[PCF50633_TI_YEAR],
		pcf_tm.time[PCF50633_TI_HOUR],
		pcf_tm.time[PCF50633_TI_MIN],
		pcf_tm.time[PCF50633_TI_SEC]);


	second_masked = pcf50633_irq_mask_get(rtc->pcf, PCF50633_IRQ_SECOND);
	alarm_masked = pcf50633_irq_mask_get(rtc->pcf, PCF50633_IRQ_ALARM);

	if (!second_masked)
		pcf50633_irq_mask(rtc->pcf, PCF50633_IRQ_SECOND);
	if (!alarm_masked)
		pcf50633_irq_mask(rtc->pcf, PCF50633_IRQ_ALARM);

	/* Returns 0 on success */
	ret = pcf50633_write_block(rtc->pcf, PCF50633_REG_RTCSC,
					     PCF50633_TI_EXTENT,
					     &pcf_tm.time[0]);

	if (!second_masked)
		pcf50633_irq_unmask(rtc->pcf, PCF50633_IRQ_SECOND);
	if (!alarm_masked)
		pcf50633_irq_unmask(rtc->pcf, PCF50633_IRQ_ALARM);

	return ret;
}