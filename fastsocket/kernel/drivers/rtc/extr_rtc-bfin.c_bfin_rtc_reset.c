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
typedef  int /*<<< orphan*/  u16 ;
struct device {int dummy; } ;
struct bfin_rtc {scalar_t__ rtc_wrote_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfin_rtc_sync_pending (struct device*) ; 
 int /*<<< orphan*/  bfin_write_RTC_ALARM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_RTC_ICTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_RTC_ISTAT (int) ; 
 int /*<<< orphan*/  bfin_write_RTC_PREN (int) ; 
 int /*<<< orphan*/  dev_dbg_stamp (struct device*) ; 
 struct bfin_rtc* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static void bfin_rtc_reset(struct device *dev, u16 rtc_ictl)
{
	struct bfin_rtc *rtc = dev_get_drvdata(dev);
	dev_dbg_stamp(dev);
	bfin_rtc_sync_pending(dev);
	bfin_write_RTC_PREN(0x1);
	bfin_write_RTC_ICTL(rtc_ictl);
	bfin_write_RTC_ALARM(0);
	bfin_write_RTC_ISTAT(0xFFFF);
	rtc->rtc_wrote_regs = 0;
}