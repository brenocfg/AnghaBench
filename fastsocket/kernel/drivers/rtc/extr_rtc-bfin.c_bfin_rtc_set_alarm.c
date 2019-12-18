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
struct rtc_wkalrm {scalar_t__ enabled; int /*<<< orphan*/  time; } ;
struct device {int dummy; } ;
struct bfin_rtc {int /*<<< orphan*/  rtc_alarm; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  bfin_rtc_int_set_alarm (struct bfin_rtc*) ; 
 int /*<<< orphan*/  bfin_rtc_sync_pending (struct device*) ; 
 int /*<<< orphan*/  bfin_write_RTC_ALARM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg_stamp (struct device*) ; 
 struct bfin_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rtc_time_to_bfin (unsigned long) ; 
 scalar_t__ rtc_tm_to_time (int /*<<< orphan*/ *,unsigned long*) ; 

__attribute__((used)) static int bfin_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct bfin_rtc *rtc = dev_get_drvdata(dev);
	unsigned long rtc_alarm;

	dev_dbg_stamp(dev);

	if (rtc_tm_to_time(&alrm->time, &rtc_alarm))
		return -EINVAL;

	rtc->rtc_alarm = alrm->time;

	bfin_rtc_sync_pending(dev);
	bfin_write_RTC_ALARM(rtc_time_to_bfin(rtc_alarm));
	if (alrm->enabled)
		bfin_rtc_int_set_alarm(rtc);

	return 0;
}