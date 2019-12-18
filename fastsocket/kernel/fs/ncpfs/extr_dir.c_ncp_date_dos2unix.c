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
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 unsigned short* day_n ; 
 unsigned short le16_to_cpu (int /*<<< orphan*/ ) ; 
 int local2utc (int) ; 

int
ncp_date_dos2unix(__le16 t, __le16 d)
{
	unsigned short time = le16_to_cpu(t), date = le16_to_cpu(d);
	int month, year, secs;

	/* first subtract and mask after that... Otherwise, if
	   date == 0, bad things happen */
	month = ((date >> 5) - 1) & 15;
	year = date >> 9;
	secs = (time & 31) * 2 + 60 * ((time >> 5) & 63) + (time >> 11) * 3600 +
		86400 * ((date & 31) - 1 + day_n[month] + (year / 4) + 
		year * 365 - ((year & 3) == 0 && month < 2 ? 1 : 0) + 3653);
	/* days since 1.1.70 plus 80's leap day */
	return local2utc(secs);
}