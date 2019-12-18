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
 int SYS_CNTRL_C0S ; 
 int /*<<< orphan*/  SYS_COUNTER_CNTRL ; 
 int /*<<< orphan*/  SYS_TOYWRITE ; 
 int au_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au_sync () ; 
 int /*<<< orphan*/  au_writel (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rtc_tm_to_time (struct rtc_time*,unsigned long*) ; 

__attribute__((used)) static int au1xtoy_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	unsigned long t;

	rtc_tm_to_time(tm, &t);

	au_writel(t, SYS_TOYWRITE);
	au_sync();

	/* wait for the pending register write to succeed.  This can
	 * take up to 6 seconds...
	 */
	while (au_readl(SYS_COUNTER_CNTRL) & SYS_CNTRL_C0S)
		msleep(1);

	return 0;
}