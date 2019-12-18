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
typedef  unsigned long u32 ;
struct sam9_rtc {int dummy; } ;
struct rtc_time {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_mon; int /*<<< orphan*/  tm_year; } ;
struct rtc_wkalrm {scalar_t__ enabled; struct rtc_time time; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned long ALARM_DISABLED ; 
 int /*<<< orphan*/  AR ; 
 unsigned long AT91_RTT_ALMIEN ; 
 int EILSEQ ; 
 int /*<<< orphan*/  MR ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sam9_rtc* dev_get_drvdata (struct device*) ; 
 unsigned long gpbr_readl (struct sam9_rtc*) ; 
 int rtc_tm_to_time (struct rtc_time*,unsigned long*) ; 
 unsigned long rtt_readl (struct sam9_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtt_writel (struct sam9_rtc*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int at91_rtc_setalarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct sam9_rtc *rtc = dev_get_drvdata(dev);
	struct rtc_time *tm = &alrm->time;
	unsigned long secs;
	u32 offset;
	u32 mr;
	int err;

	err = rtc_tm_to_time(tm, &secs);
	if (err != 0)
		return err;

	offset = gpbr_readl(rtc);
	if (offset == 0) {
		/* time is not set */
		return -EILSEQ;
	}
	mr = rtt_readl(rtc, MR);
	rtt_writel(rtc, MR, mr & ~AT91_RTT_ALMIEN);

	/* alarm in the past? finish and leave disabled */
	if (secs <= offset) {
		rtt_writel(rtc, AR, ALARM_DISABLED);
		return 0;
	}

	/* else set alarm and maybe enable it */
	rtt_writel(rtc, AR, secs - offset);
	if (alrm->enabled)
		rtt_writel(rtc, MR, mr | AT91_RTT_ALMIEN);

	dev_dbg(dev, "%s: %4d-%02d-%02d %02d:%02d:%02d\n", "setalarm",
		tm->tm_year, tm->tm_mon, tm->tm_mday, tm->tm_hour,
		tm->tm_min, tm->tm_sec);

	return 0;
}