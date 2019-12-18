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
struct rtc_time {unsigned int tm_min; unsigned int tm_hour; int tm_mday; int tm_mon; int tm_year; int tm_wday; int tm_yday; int tm_isdst; int /*<<< orphan*/  tm_sec; } ;

/* Variables and functions */
 unsigned int FILEHASH ; 
 unsigned int USERHASH ; 
 int /*<<< orphan*/  set_rtc_time (struct rtc_time*) ; 

__attribute__((used)) static int set_magic_time(unsigned int user, unsigned int file, unsigned int device)
{
	unsigned int n = user + USERHASH*(file + FILEHASH*device);

	// June 7th, 2006
	static struct rtc_time time = {
		.tm_sec = 0,
		.tm_min = 0,
		.tm_hour = 0,
		.tm_mday = 7,
		.tm_mon = 5,	// June - counting from zero
		.tm_year = 106,
		.tm_wday = 3,
		.tm_yday = 160,
		.tm_isdst = 1
	};

	time.tm_year = (n % 100);
	n /= 100;
	time.tm_mon = (n % 12);
	n /= 12;
	time.tm_mday = (n % 28) + 1;
	n /= 28;
	time.tm_hour = (n % 24);
	n /= 24;
	time.tm_min = (n % 20) * 3;
	n /= 20;
	set_rtc_time(&time);
	return n ? -1 : 0;
}