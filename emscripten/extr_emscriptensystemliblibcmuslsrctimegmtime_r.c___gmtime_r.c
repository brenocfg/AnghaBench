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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int /*<<< orphan*/  __tm_zone; scalar_t__ __tm_gmtoff; scalar_t__ tm_isdst; } ;

/* Variables and functions */
 int /*<<< orphan*/  EOVERFLOW ; 
 int /*<<< orphan*/  __gmt ; 
 scalar_t__ __secs_to_tm (int /*<<< orphan*/  const,struct tm*) ; 
 int /*<<< orphan*/  errno ; 

struct tm *__gmtime_r(const time_t *restrict t, struct tm *restrict tm)
{
	if (__secs_to_tm(*t, tm) < 0) {
		errno = EOVERFLOW;
		return 0;
	}
	tm->tm_isdst = 0;
	tm->__tm_gmtoff = 0;
	tm->__tm_zone = __gmt;
	return tm;
}