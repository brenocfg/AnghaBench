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
struct rtc_wkalrm {int /*<<< orphan*/  time; int /*<<< orphan*/  enabled; } ;
struct pcf50633_time {int /*<<< orphan*/ * time; } ;
struct pcf50633_rtc {int /*<<< orphan*/  pcf; int /*<<< orphan*/  alarm_enabled; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  PCF50633_REG_RTCSCA ; 
 int PCF50633_TI_EXTENT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct pcf50633_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  pcf2rtc_time (int /*<<< orphan*/ *,struct pcf50633_time*) ; 
 int pcf50633_read_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int rtc_valid_tm (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pcf50633_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct pcf50633_rtc *rtc;
	struct pcf50633_time pcf_tm;
	int ret = 0;

	rtc = dev_get_drvdata(dev);

	alrm->enabled = rtc->alarm_enabled;

	ret = pcf50633_read_block(rtc->pcf, PCF50633_REG_RTCSCA,
				PCF50633_TI_EXTENT, &pcf_tm.time[0]);
	if (ret != PCF50633_TI_EXTENT) {
		dev_err(dev, "Failed to read time\n");
		return -EIO;
	}

	pcf2rtc_time(&alrm->time, &pcf_tm);

	return rtc_valid_tm(&alrm->time);
}