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
struct rtc_time {int tm_hour; int tm_min; int tm_mon; int tm_mday; int tm_year; int /*<<< orphan*/  tm_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_rtc_time (struct rtc_time*) ; 
 int /*<<< orphan*/  printk (char*,int,int,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static unsigned int read_magic_time(void)
{
	struct rtc_time time;
	unsigned int val;

	get_rtc_time(&time);
	printk("Time: %2d:%02d:%02d  Date: %02d/%02d/%02d\n",
		time.tm_hour, time.tm_min, time.tm_sec,
		time.tm_mon + 1, time.tm_mday, time.tm_year % 100);
	val = time.tm_year;				/* 100 years */
	if (val > 100)
		val -= 100;
	val += time.tm_mon * 100;			/* 12 months */
	val += (time.tm_mday-1) * 100 * 12;		/* 28 month-days */
	val += time.tm_hour * 100 * 12 * 28;		/* 24 hours */
	val += (time.tm_min / 3) * 100 * 12 * 28 * 24;	/* 20 3-minute intervals */
	return val;
}