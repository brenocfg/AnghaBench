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
struct rtc_wkalrm {int enabled; int pending; int /*<<< orphan*/  time; } ;
struct rtc_at32ap700x {int /*<<< orphan*/  lock; int /*<<< orphan*/  alarm_time; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMR ; 
 int /*<<< orphan*/  IMR_TOPI ; 
 int /*<<< orphan*/  ISR ; 
 int /*<<< orphan*/  ISR_TOPI ; 
 int RTC_BIT (int /*<<< orphan*/ ) ; 
 struct rtc_at32ap700x* dev_get_drvdata (struct device*) ; 
 int rtc_readl (struct rtc_at32ap700x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_time_to_tm (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int at32_rtc_readalarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct rtc_at32ap700x *rtc = dev_get_drvdata(dev);

	spin_lock_irq(&rtc->lock);
	rtc_time_to_tm(rtc->alarm_time, &alrm->time);
	alrm->enabled = rtc_readl(rtc, IMR) & RTC_BIT(IMR_TOPI) ? 1 : 0;
	alrm->pending = rtc_readl(rtc, ISR) & RTC_BIT(ISR_TOPI) ? 1 : 0;
	spin_unlock_irq(&rtc->lock);

	return 0;
}