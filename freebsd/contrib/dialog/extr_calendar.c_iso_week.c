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
 int MAX_DAYS ; 
 int day_in_year (int,int,int) ; 
 int day_of_week (int,int,int) ; 
 int isleap (int) ; 

__attribute__((used)) static int
iso_week(int year, int month, int day)
{
    int week = 1;
    int dow;
    int new_year_dow;
    int diy;
    int new_years_eve_dow;
    static const int thursday = 3;

    /* add the number weeks *between* date and newyear */
    diy = day_in_year(year, month, day);
    week += (diy - 1) / MAX_DAYS;

    /* 0 = Monday */
    dow = day_of_week(year, month, day);
    new_year_dow = day_of_week(year, 1, 1);

    /*
     * If New Year falls on Friday, Saturday or Sunday, then New Years's week
     * is the last week of the preceding year.  In that case subtract one week.
     */
    if (new_year_dow > thursday)
	--week;

    /* Add one week if there is a Sunday to Monday transition. */
    if (dow - new_year_dow < 0)
	++week;

    /* Check if we are in the last week of the preceding year. */
    if (week < 1) {
	week = iso_week(--year, 12, 31);
    }

    /*
     * If we are in the same week as New Year's eve, check if New Year's eve is
     * in the first week of the next year.
     */
    new_years_eve_dow = (new_year_dow + 364 + isleap(year)) % MAX_DAYS;
    if (365 + isleap(year) - diy < MAX_DAYS
	&& new_years_eve_dow >= dow
	&& new_years_eve_dow < thursday) {
	++year;
	week = 1;
    }
    return week;
}