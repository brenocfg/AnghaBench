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
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;
struct bfin_rtc {int rtc_wrote_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfin_rtc_sync_pending (struct device*) ; 
 int /*<<< orphan*/  bfin_write_RTC_STAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg_stamp (struct device*) ; 
 struct bfin_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rtc_time_to_bfin (unsigned long) ; 
 int rtc_tm_to_time (struct rtc_time*,unsigned long*) ; 

__attribute__((used)) static int bfin_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct bfin_rtc *rtc = dev_get_drvdata(dev);
	int ret;
	unsigned long now;

	dev_dbg_stamp(dev);

	ret = rtc_tm_to_time(tm, &now);
	if (ret == 0) {
		if (rtc->rtc_wrote_regs & 0x1)
			bfin_rtc_sync_pending(dev);
		bfin_write_RTC_STAT(rtc_time_to_bfin(now));
		rtc->rtc_wrote_regs = 0x1;
	}

	return ret;
}