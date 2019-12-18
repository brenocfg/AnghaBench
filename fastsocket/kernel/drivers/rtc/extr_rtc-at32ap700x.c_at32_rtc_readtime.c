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
struct rtc_at32ap700x {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VAL ; 
 struct rtc_at32ap700x* dev_get_drvdata (struct device*) ; 
 unsigned long rtc_readl (struct rtc_at32ap700x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_time_to_tm (unsigned long,struct rtc_time*) ; 

__attribute__((used)) static int at32_rtc_readtime(struct device *dev, struct rtc_time *tm)
{
	struct rtc_at32ap700x *rtc = dev_get_drvdata(dev);
	unsigned long now;

	now = rtc_readl(rtc, VAL);
	rtc_time_to_tm(now, tm);

	return 0;
}