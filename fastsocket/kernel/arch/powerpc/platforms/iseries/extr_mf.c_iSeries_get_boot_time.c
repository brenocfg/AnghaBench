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
struct rtc_time {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_mon; scalar_t__ tm_year; } ;

/* Variables and functions */
 int /*<<< orphan*/  mf_get_boot_rtc (struct rtc_time*) ; 
 unsigned long mktime (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned long iSeries_get_boot_time(void)
{
	struct rtc_time tm;

	mf_get_boot_rtc(&tm);
	return mktime(tm.tm_year + 1900, tm.tm_mon, tm.tm_mday,
		      tm.tm_hour, tm.tm_min, tm.tm_sec);
}