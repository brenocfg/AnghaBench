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
struct sh_rtc {int /*<<< orphan*/  lock; scalar_t__ regbase; } ;
struct rtc_time {scalar_t__ tm_mon; int tm_year; void* tm_mday; void* tm_wday; void* tm_hour; void* tm_min; void* tm_sec; } ;
struct rtc_wkalrm {int enabled; struct rtc_time time; } ;
struct platform_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ RCR1 ; 
 int RCR1_AIE ; 
 int /*<<< orphan*/  RDAYAR ; 
 int /*<<< orphan*/  RHRAR ; 
 int /*<<< orphan*/  RMINAR ; 
 int /*<<< orphan*/  RMONAR ; 
 int /*<<< orphan*/  RSECAR ; 
 int /*<<< orphan*/  RWKAR ; 
 struct sh_rtc* platform_get_drvdata (struct platform_device*) ; 
 int readb (scalar_t__) ; 
 void* sh_rtc_read_alarm_value (struct sh_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int sh_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *wkalrm)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct sh_rtc *rtc = platform_get_drvdata(pdev);
	struct rtc_time *tm = &wkalrm->time;

	spin_lock_irq(&rtc->lock);

	tm->tm_sec	= sh_rtc_read_alarm_value(rtc, RSECAR);
	tm->tm_min	= sh_rtc_read_alarm_value(rtc, RMINAR);
	tm->tm_hour	= sh_rtc_read_alarm_value(rtc, RHRAR);
	tm->tm_wday	= sh_rtc_read_alarm_value(rtc, RWKAR);
	tm->tm_mday	= sh_rtc_read_alarm_value(rtc, RDAYAR);
	tm->tm_mon	= sh_rtc_read_alarm_value(rtc, RMONAR);
	if (tm->tm_mon > 0)
		tm->tm_mon -= 1; /* RTC is 1-12, tm_mon is 0-11 */
	tm->tm_year     = 0xffff;

	wkalrm->enabled = (readb(rtc->regbase + RCR1) & RCR1_AIE) ? 1 : 0;

	spin_unlock_irq(&rtc->lock);

	return 0;
}