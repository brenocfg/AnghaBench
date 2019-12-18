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
typedef  int hrtime_t ;

/* Variables and functions */
 int NANOSEC ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 

void
print_time(hrtime_t t, char *timebuf)
{
	hrtime_t s = t / NANOSEC;
	hrtime_t m = s / 60;
	hrtime_t h = m / 60;
	hrtime_t d = h / 24;

	s -= m * 60;
	m -= h * 60;
	h -= d * 24;

	timebuf[0] = '\0';

	if (d)
		(void) sprintf(timebuf,
		    "%llud%02lluh%02llum%02llus", d, h, m, s);
	else if (h)
		(void) sprintf(timebuf, "%lluh%02llum%02llus", h, m, s);
	else if (m)
		(void) sprintf(timebuf, "%llum%02llus", m, s);
	else
		(void) sprintf(timebuf, "%llus", s);
}