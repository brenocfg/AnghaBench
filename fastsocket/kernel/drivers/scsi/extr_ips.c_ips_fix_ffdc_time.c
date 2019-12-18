#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  long time_t ;
struct TYPE_5__ {long hour; long minute; long second; int yearH; int yearL; int month; long day; } ;
struct TYPE_6__ {TYPE_1__ ffdc; } ;
struct TYPE_7__ {TYPE_2__ cmd; } ;
typedef  TYPE_3__ ips_scb_t ;
typedef  int /*<<< orphan*/  ips_ha_t ;

/* Variables and functions */
 int IPS_DAYS_LEAP_YEAR ; 
 int IPS_DAYS_NORMAL_YEAR ; 
 int IPS_EPOCH_YEAR ; 
 int IPS_IS_LEAP_YEAR (int) ; 
 scalar_t__ IPS_NUM_LEAP_YEARS_THROUGH (int) ; 
 long IPS_SECS_DAY ; 
 long IPS_SECS_HOUR ; 
 long IPS_SECS_MIN ; 
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 

__attribute__((used)) static void
ips_fix_ffdc_time(ips_ha_t * ha, ips_scb_t * scb, time_t current_time)
{
	long days;
	long rem;
	int i;
	int year;
	int yleap;
	int year_lengths[2] = { IPS_DAYS_NORMAL_YEAR, IPS_DAYS_LEAP_YEAR };
	int month_lengths[12][2] = { {31, 31},
	{28, 29},
	{31, 31},
	{30, 30},
	{31, 31},
	{30, 30},
	{31, 31},
	{31, 31},
	{30, 30},
	{31, 31},
	{30, 30},
	{31, 31}
	};

	METHOD_TRACE("ips_fix_ffdc_time", 1);

	days = current_time / IPS_SECS_DAY;
	rem = current_time % IPS_SECS_DAY;

	scb->cmd.ffdc.hour = (rem / IPS_SECS_HOUR);
	rem = rem % IPS_SECS_HOUR;
	scb->cmd.ffdc.minute = (rem / IPS_SECS_MIN);
	scb->cmd.ffdc.second = (rem % IPS_SECS_MIN);

	year = IPS_EPOCH_YEAR;
	while (days < 0 || days >= year_lengths[yleap = IPS_IS_LEAP_YEAR(year)]) {
		int newy;

		newy = year + (days / IPS_DAYS_NORMAL_YEAR);
		if (days < 0)
			--newy;
		days -= (newy - year) * IPS_DAYS_NORMAL_YEAR +
		    IPS_NUM_LEAP_YEARS_THROUGH(newy - 1) -
		    IPS_NUM_LEAP_YEARS_THROUGH(year - 1);
		year = newy;
	}

	scb->cmd.ffdc.yearH = year / 100;
	scb->cmd.ffdc.yearL = year % 100;

	for (i = 0; days >= month_lengths[i][yleap]; ++i)
		days -= month_lengths[i][yleap];

	scb->cmd.ffdc.month = i + 1;
	scb->cmd.ffdc.day = days + 1;
}