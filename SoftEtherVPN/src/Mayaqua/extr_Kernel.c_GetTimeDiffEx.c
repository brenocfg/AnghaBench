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
typedef  scalar_t__ time_t ;
struct tm {int wYear; } ;
typedef  struct tm SYSTEMTIME ;
typedef  scalar_t__ INT64 ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (struct tm*,struct tm*,int) ; 
 int /*<<< orphan*/  SystemToTm (struct tm*,struct tm*) ; 
 scalar_t__ SystemToUINT64 (struct tm*) ; 
 int /*<<< orphan*/  TmToSystem (struct tm*,struct tm*) ; 
 scalar_t__ c_mkgmtime (struct tm*) ; 
 struct tm* gmtime (scalar_t__*) ; 
 int /*<<< orphan*/  gmtime_r (scalar_t__*,struct tm*) ; 
 struct tm* localtime (scalar_t__*) ; 
 int /*<<< orphan*/  localtime_r (scalar_t__*,struct tm*) ; 
 scalar_t__ mktime (struct tm*) ; 

INT64 GetTimeDiffEx(SYSTEMTIME *basetime, bool local_time)
{
	time_t tmp;
	struct tm t1, t2;
	SYSTEMTIME snow;
	struct tm now;
	SYSTEMTIME s1, s2;
	INT64 ret;

	Copy(&snow, basetime, sizeof(SYSTEMTIME));

	if (sizeof(time_t) == 4)
	{
		if (snow.wYear >= 2038)
		{
			// For old systems: avoid the 2038-year problem
			snow.wYear = 2037;
		}
	}

	SystemToTm(&now, &snow);
	if (local_time == false)
	{
		tmp = (time_t)c_mkgmtime(&now);
	}
	else
	{
		tmp = mktime(&now);
	}

	if (tmp == (time_t)-1)
	{
		return 0;
	}

#ifndef	OS_UNIX
	Copy(&t1, localtime(&tmp), sizeof(struct tm));
	Copy(&t2, gmtime(&tmp), sizeof(struct tm));
#else	// OS_UNIX
	localtime_r(&tmp, &t1);
	gmtime_r(&tmp, &t2);
#endif	// OS_UNIX

	TmToSystem(&s1, &t1);
	TmToSystem(&s2, &t2);

	ret = (INT)SystemToUINT64(&s1) - (INT)SystemToUINT64(&s2);

	return ret;
}