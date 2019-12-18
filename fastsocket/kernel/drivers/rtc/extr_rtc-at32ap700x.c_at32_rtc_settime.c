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
 int rtc_tm_to_time (struct rtc_time*,unsigned long*) ; 
 int /*<<< orphan*/  rtc_writel (struct rtc_at32ap700x*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int at32_rtc_settime(struct device *dev, struct rtc_time *tm)
{
	struct rtc_at32ap700x *rtc = dev_get_drvdata(dev);
	unsigned long now;
	int ret;

	ret = rtc_tm_to_time(tm, &now);
	if (ret == 0)
		rtc_writel(rtc, VAL, now);

	return ret;
}