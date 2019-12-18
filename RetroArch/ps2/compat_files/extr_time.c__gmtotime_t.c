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

/* Variables and functions */
 int DAYS_YEAR ; 
 long HOURS_DAY ; 
 int MAX_SUPPORTED_YEAR ; 
 int MINS_HOUR ; 
 int MIN_SUPPORTED_YEAR ; 
 int SECS_MIN ; 
 scalar_t__* _days ; 

__attribute__((used)) static time_t _gmtotime_t (
        int yr,     /* 0 based */
        int mo,     /* 1 based */
        int dy,     /* 1 based */
        int hr,
        int mn,
        int sc
        )
{
   int passed_years;
   long passed_days;
   long passed_seconds_current_day;
   time_t seconds_from_1970 = -1;

   if ((yr >= MIN_SUPPORTED_YEAR) || (yr <= MAX_SUPPORTED_YEAR))  {
      passed_years = (long)yr - MIN_SUPPORTED_YEAR; /* Years after 1970 */
      /* Calculate days for these years */
      passed_days = passed_years * DAYS_YEAR;
      passed_days += (passed_years >> 2) * (DAYS_YEAR + 1); /* passed leap years */
      passed_days += dy + _days[mo - 1]; /* passed days in the year */
      if ( !(yr & 3) && (mo > 2) ) {
         passed_days++; /* if current year, is a leap year */
      }
      passed_seconds_current_day = (((hr * MINS_HOUR) + mn) * SECS_MIN) + sc;
      seconds_from_1970 = (passed_days * HOURS_DAY * MINS_HOUR * SECS_MIN) + passed_seconds_current_day;
   }

   return seconds_from_1970;
}