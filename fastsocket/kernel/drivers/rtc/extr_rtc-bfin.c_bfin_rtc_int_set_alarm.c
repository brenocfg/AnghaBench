#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int tm_yday; } ;
struct bfin_rtc {TYPE_1__ rtc_alarm; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_ISTAT_ALARM ; 
 int /*<<< orphan*/  RTC_ISTAT_ALARM_DAY ; 
 int /*<<< orphan*/  bfin_rtc_int_set (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bfin_rtc_int_set_alarm(struct bfin_rtc *rtc)
{
	/* Blackfin has different bits for whether the alarm is
	 * more than 24 hours away.
	 */
	bfin_rtc_int_set(rtc->rtc_alarm.tm_yday == -1 ? RTC_ISTAT_ALARM : RTC_ISTAT_ALARM_DAY);
}