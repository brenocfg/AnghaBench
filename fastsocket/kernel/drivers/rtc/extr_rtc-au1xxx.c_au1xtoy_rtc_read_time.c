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

/* Variables and functions */
 int /*<<< orphan*/  SYS_TOYREAD ; 
 unsigned long au_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_time_to_tm (unsigned long,struct rtc_time*) ; 
 int rtc_valid_tm (struct rtc_time*) ; 

__attribute__((used)) static int au1xtoy_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	unsigned long t;

	t = au_readl(SYS_TOYREAD);

	rtc_time_to_tm(t, tm);

	return rtc_valid_tm(tm);
}