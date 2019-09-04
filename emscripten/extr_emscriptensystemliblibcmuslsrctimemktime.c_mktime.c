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
typedef  long long time_t ;
struct tm {scalar_t__ tm_isdst; long __tm_gmtoff; int /*<<< orphan*/  __tm_zone; } ;

/* Variables and functions */
 int /*<<< orphan*/  EOVERFLOW ; 
 scalar_t__ __secs_to_tm (long long,struct tm*) ; 
 int /*<<< orphan*/  __secs_to_zone (long long,int,scalar_t__*,long*,long*,int /*<<< orphan*/ *) ; 
 long long __tm_to_secs (struct tm*) ; 
 int /*<<< orphan*/  errno ; 

time_t mktime(struct tm *tm)
{
	struct tm new;
	long opp;
	long long t = __tm_to_secs(tm);

	__secs_to_zone(t, 1, &new.tm_isdst, &new.__tm_gmtoff, &opp, &new.__tm_zone);

	if (tm->tm_isdst>=0 && new.tm_isdst!=tm->tm_isdst)
		t -= opp - new.__tm_gmtoff;

	t -= new.__tm_gmtoff;
	if ((time_t)t != t) goto error;

	__secs_to_zone(t, 0, &new.tm_isdst, &new.__tm_gmtoff, &opp, &new.__tm_zone);

	if (__secs_to_tm(t + new.__tm_gmtoff, &new) < 0) goto error;

	*tm = new;
	return t;

error:
	errno = EOVERFLOW;
	return -1;
}