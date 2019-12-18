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
typedef  int /*<<< orphan*/  u64 ;
struct rtc_time {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; scalar_t__ tm_mon; scalar_t__ tm_year; } ;

/* Variables and functions */
 scalar_t__ beat_rtc_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mktime (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int beat_set_rtc_time(struct rtc_time *rtc_time)
{
	u64 tim;
	tim = mktime(rtc_time->tm_year+1900,
		     rtc_time->tm_mon+1, rtc_time->tm_mday,
		     rtc_time->tm_hour, rtc_time->tm_min, rtc_time->tm_sec);
	if (beat_rtc_write(tim))
		return -1;
	return 0;
}