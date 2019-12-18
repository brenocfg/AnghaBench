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
 int /*<<< orphan*/  bfin_read_RTC_STAT () ; 
 int /*<<< orphan*/  bfin_rtc_sync_pending (struct device*) ; 
 int /*<<< orphan*/  dev_dbg_stamp (struct device*) ; 
 struct bfin_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rtc_bfin_to_tm (int /*<<< orphan*/ ,struct rtc_time*) ; 

__attribute__((used)) static int bfin_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct bfin_rtc *rtc = dev_get_drvdata(dev);

	dev_dbg_stamp(dev);

	if (rtc->rtc_wrote_regs & 0x1)
		bfin_rtc_sync_pending(dev);

	rtc_bfin_to_tm(bfin_read_RTC_STAT(), tm);

	return 0;
}