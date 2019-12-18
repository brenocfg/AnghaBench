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
struct timestamp {long hour; long minute; long second; long month; long day; int centiseconds; int hundredsOfMicroseconds; int microseconds; void* year; void* typeAndTimezone; } ;
struct timespec {int tv_sec; int tv_nsec; } ;
typedef  int int16_t ;
struct TYPE_2__ {int tz_minuteswest; } ;

/* Variables and functions */
 scalar_t__ LEAPS_THRU_END_OF (long) ; 
 long SECS_PER_DAY ; 
 long SECS_PER_HOUR ; 
 size_t __isleap (long) ; 
 unsigned short** __mon_yday ; 
 void* cpu_to_le16 (long) ; 
 TYPE_1__ sys_tz ; 

struct timestamp *
udf_time_to_disk_stamp(struct timestamp *dest, struct timespec ts)
{
	long int days, rem, y;
	const unsigned short int *ip;
	int16_t offset;

	offset = -sys_tz.tz_minuteswest;

	if (!dest)
		return NULL;

	dest->typeAndTimezone = cpu_to_le16(0x1000 | (offset & 0x0FFF));

	ts.tv_sec += offset * 60;
	days = ts.tv_sec / SECS_PER_DAY;
	rem = ts.tv_sec % SECS_PER_DAY;
	dest->hour = rem / SECS_PER_HOUR;
	rem %= SECS_PER_HOUR;
	dest->minute = rem / 60;
	dest->second = rem % 60;
	y = 1970;

#define DIV(a, b) ((a) / (b) - ((a) % (b) < 0))
#define LEAPS_THRU_END_OF(y) (DIV (y, 4) - DIV (y, 100) + DIV (y, 400))

	while (days < 0 || days >= (__isleap(y) ? 366 : 365)) {
		long int yg = y + days / 365 - (days % 365 < 0);

		/* Adjust DAYS and Y to match the guessed year.  */
		days -= ((yg - y) * 365
			 + LEAPS_THRU_END_OF(yg - 1)
			 - LEAPS_THRU_END_OF(y - 1));
		y = yg;
	}
	dest->year = cpu_to_le16(y);
	ip = __mon_yday[__isleap(y)];
	for (y = 11; days < (long int)ip[y]; --y)
		continue;
	days -= ip[y];
	dest->month = y + 1;
	dest->day = days + 1;

	dest->centiseconds = ts.tv_nsec / 10000000;
	dest->hundredsOfMicroseconds = (ts.tv_nsec / 1000 -
					dest->centiseconds * 10000) / 100;
	dest->microseconds = (ts.tv_nsec / 1000 - dest->centiseconds * 10000 -
			      dest->hundredsOfMicroseconds * 100);
	return dest;
}