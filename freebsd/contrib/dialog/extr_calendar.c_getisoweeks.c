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

/* Variables and functions */
 scalar_t__ MAX_DAYS ; 
 int days_per_month (int,int) ; 
 int iso_week (int,int,int) ; 

__attribute__((used)) static int *
getisoweeks(int year, int month)
{
    static int result[10];
    int windx = 0;
    int day;
    int dpm = days_per_month(year, month);

    for (day = 1; day <= dpm; day += MAX_DAYS)
	result[windx++] = iso_week(year, month, day);
    /*
     * Ensure that there is a week number associated with the last day of the
     * month, e.g., in case the last day of the month falls before Thursday,
     * so that we have to show the week-number for the beginning of the
     * following month.
     */
    result[windx] = iso_week(year, month, dpm);
    return result;
}