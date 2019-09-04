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
typedef  int time_t ;
struct my_tm {int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; int tm_sec; } ;

/* Variables and functions */

__attribute__((used)) static void my_timegm(struct my_tm *tm, time_t *t)
{
  static const int month_days_cumulative [12] =
    { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };
  int month, year, leap_days;

  year = tm->tm_year;
  month = tm->tm_mon;
  if(month < 0) {
    year += (11 - month) / 12;
    month = 11 - (11 - month) % 12;
  }
  else if(month >= 12) {
    year -= month / 12;
    month = month % 12;
  }

  leap_days = year - (tm->tm_mon <= 1);
  leap_days = ((leap_days / 4) - (leap_days / 100) + (leap_days / 400)
               - (1969 / 4) + (1969 / 100) - (1969 / 400));

  *t = ((((time_t) (year - 1970) * 365
          + leap_days + month_days_cumulative[month] + tm->tm_mday - 1) * 24
         + tm->tm_hour) * 60 + tm->tm_min) * 60 + tm->tm_sec;
}