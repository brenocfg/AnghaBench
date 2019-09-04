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
typedef  int time_t ;
struct tm {int /*<<< orphan*/  __tm_zone; scalar_t__ __tm_gmtoff; scalar_t__ tm_isdst; } ;

/* Variables and functions */
 int /*<<< orphan*/  EOVERFLOW ; 
 int /*<<< orphan*/  __gmt ; 
 scalar_t__ __secs_to_tm (long long,struct tm*) ; 
 long long __tm_to_secs (struct tm*) ; 
 int /*<<< orphan*/  errno ; 

time_t timegm(struct tm *tm)
{
	struct tm new;
	long long t = __tm_to_secs(tm);
	if (__secs_to_tm(t, &new) < 0) {
		errno = EOVERFLOW;
		return -1;
	}
	*tm = new;
	tm->tm_isdst = 0;
	tm->__tm_gmtoff = 0;
	tm->__tm_zone = __gmt;
	return t;
}