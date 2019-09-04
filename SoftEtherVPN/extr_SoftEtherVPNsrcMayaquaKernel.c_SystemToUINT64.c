#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  long long time_64t ;
typedef  unsigned long long UINT64 ;
struct TYPE_4__ {scalar_t__ wMilliseconds; } ;
typedef  TYPE_1__ SYSTEMTIME ;

/* Variables and functions */
 long long SystemToTime (TYPE_1__*) ; 

UINT64 SystemToUINT64(SYSTEMTIME *st)
{
	UINT64 sec64;
	time_64t time;
	// Validate arguments
	if (st == NULL)
	{
		return 0;
	}

	time = SystemToTime(st);

	//For times before 1970-01-01, clamp to the minimum
	//because we have to return an unsigned integer.
	//This is less wrong than casting it to UINT64
	//and returning a time far in the future.
	//For some reason we subtract 9 hours below, so
	//account for that here.
	if( time < 32400000LL ) return 0;

	sec64 = (UINT64)time * (UINT64)1000;
	sec64 += st->wMilliseconds;

	return sec64 - 32400000ULL;
}