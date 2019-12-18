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
struct device {int dummy; } ;
struct bfin_rtc {int dummy; } ;

/* Variables and functions */
 int ENOIOCTLCMD ; 
#define  RTC_AIE_OFF 131 
#define  RTC_AIE_ON 130 
 int RTC_ISTAT_ALARM ; 
 int RTC_ISTAT_ALARM_DAY ; 
 int RTC_ISTAT_SEC ; 
#define  RTC_UIE_OFF 129 
#define  RTC_UIE_ON 128 
 int /*<<< orphan*/  bfin_rtc_int_clear (int) ; 
 int /*<<< orphan*/  bfin_rtc_int_set (int) ; 
 int /*<<< orphan*/  bfin_rtc_int_set_alarm (struct bfin_rtc*) ; 
 int /*<<< orphan*/  bfin_rtc_sync_pending (struct device*) ; 
 int /*<<< orphan*/  dev_dbg_stamp (struct device*) ; 
 struct bfin_rtc* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int bfin_rtc_ioctl(struct device *dev, unsigned int cmd, unsigned long arg)
{
	struct bfin_rtc *rtc = dev_get_drvdata(dev);
	int ret = 0;

	dev_dbg_stamp(dev);

	bfin_rtc_sync_pending(dev);

	switch (cmd) {
	case RTC_UIE_ON:
		dev_dbg_stamp(dev);
		bfin_rtc_int_set(RTC_ISTAT_SEC);
		break;
	case RTC_UIE_OFF:
		dev_dbg_stamp(dev);
		bfin_rtc_int_clear(~RTC_ISTAT_SEC);
		break;

	case RTC_AIE_ON:
		dev_dbg_stamp(dev);
		bfin_rtc_int_set_alarm(rtc);
		break;
	case RTC_AIE_OFF:
		dev_dbg_stamp(dev);
		bfin_rtc_int_clear(~(RTC_ISTAT_ALARM | RTC_ISTAT_ALARM_DAY));
		break;

	default:
		dev_dbg_stamp(dev);
		ret = -ENOIOCTLCMD;
	}

	return ret;
}