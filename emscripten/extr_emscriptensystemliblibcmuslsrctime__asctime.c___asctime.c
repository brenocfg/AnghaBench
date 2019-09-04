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
struct tm {int tm_mday; int tm_hour; int tm_min; int tm_sec; scalar_t__ tm_mon; scalar_t__ tm_wday; scalar_t__ tm_year; } ;

/* Variables and functions */
 scalar_t__ ABDAY_1 ; 
 scalar_t__ ABMON_1 ; 
 char* __nl_langinfo (scalar_t__) ; 
 int /*<<< orphan*/  a_crash () ; 
 int snprintf (char*,int,char*,char*,char*,int,int,int,int,scalar_t__) ; 

char *__asctime(const struct tm *restrict tm, char *restrict buf)
{
	/* FIXME: change __nl_langinfo to __nl_langinfo_l with explicit C
	 * locale once we have locales */
	if (snprintf(buf, 26, "%.3s %.3s%3d %.2d:%.2d:%.2d %d\n",
		__nl_langinfo(ABDAY_1+tm->tm_wday),
		__nl_langinfo(ABMON_1+tm->tm_mon),
		tm->tm_mday, tm->tm_hour,
		tm->tm_min, tm->tm_sec,
		1900 + tm->tm_year) >= 26)
	{
		/* ISO C requires us to use the above format string,
		 * even if it will not fit in the buffer. Thus asctime_r
		 * is _supposed_ to crash if the fields in tm are too large.
		 * We follow this behavior and crash "gracefully" to warn
		 * application developers that they may not be so lucky
		 * on other implementations (e.g. stack smashing..).
		 */
		a_crash();
	}
	return buf;
}