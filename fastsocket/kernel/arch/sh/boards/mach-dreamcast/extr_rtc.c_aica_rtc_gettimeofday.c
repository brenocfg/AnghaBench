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
struct timespec {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  AICA_RTC_SECS_H ; 
 int /*<<< orphan*/  AICA_RTC_SECS_L ; 
 scalar_t__ TWENTY_YEARS ; 
 int ctrl_inl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aica_rtc_gettimeofday(struct timespec *ts)
{
	unsigned long val1, val2;

	do {
		val1 = ((ctrl_inl(AICA_RTC_SECS_H) & 0xffff) << 16) |
			(ctrl_inl(AICA_RTC_SECS_L) & 0xffff);

		val2 = ((ctrl_inl(AICA_RTC_SECS_H) & 0xffff) << 16) |
			(ctrl_inl(AICA_RTC_SECS_L) & 0xffff);
	} while (val1 != val2);

	ts->tv_sec = val1 - TWENTY_YEARS;

	/* Can't get nanoseconds with just a seconds counter. */
	ts->tv_nsec = 0;
}