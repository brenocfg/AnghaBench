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
struct tm {unsigned int tm_yday; unsigned int tm_wday; int tm_year; } ;

/* Variables and functions */
 scalar_t__ is_leap (int) ; 

__attribute__((used)) static int week_num(const struct tm *tm)
{
	int val = (tm->tm_yday + 7U - (tm->tm_wday+6U)%7) / 7;
	/* If 1 Jan is just 1-3 days past Monday,
	 * the previous week is also in this year. */
	if ((tm->tm_wday + 371U - tm->tm_yday - 2) % 7 <= 2)
		val++;
	if (!val) {
		val = 52;
		/* If 31 December of prev year a Thursday,
		 * or Friday of a leap year, then the
		 * prev year has 53 weeks. */
		int dec31 = (tm->tm_wday + 7U - tm->tm_yday - 1) % 7;
		if (dec31 == 4 || (dec31 == 5 && is_leap(tm->tm_year%400-1)))
			val++;
	} else if (val == 53) {
		/* If 1 January is not a Thursday, and not
		 * a Wednesday of a leap year, then this
		 * year has only 52 weeks. */
		int jan1 = (tm->tm_wday + 371U - tm->tm_yday) % 7;
		if (jan1 != 4 && (jan1 != 3 || !is_leap(tm->tm_year)))
			val = 1;
	}
	return val;
}