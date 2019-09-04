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
struct tm {scalar_t__ __tm_gmtoff; int /*<<< orphan*/  __tm_zone; int /*<<< orphan*/  tm_isdst; } ;

/* Variables and functions */
 int /*<<< orphan*/  EOVERFLOW ; 
 long long INT_MAX ; 
 long long INT_MIN ; 
 scalar_t__ __secs_to_tm (scalar_t__,struct tm*) ; 
 int /*<<< orphan*/  __secs_to_zone (long long const,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 

struct tm *__localtime_r(const time_t *restrict t, struct tm *restrict tm)
{
	/* Reject time_t values whose year would overflow int because
	 * __secs_to_zone cannot safely handle them. */
	if (*t < INT_MIN * 31622400LL || *t > INT_MAX * 31622400LL) {
		errno = EOVERFLOW;
		return 0;
	}
	__secs_to_zone(*t, 0, &tm->tm_isdst, &tm->__tm_gmtoff, 0, &tm->__tm_zone);
	if (__secs_to_tm((long long)*t + tm->__tm_gmtoff, tm) < 0) {
		errno = EOVERFLOW;
		return 0;
	}
	return tm;
}