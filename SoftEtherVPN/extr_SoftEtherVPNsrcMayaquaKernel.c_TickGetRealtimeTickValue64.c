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
typedef  int /*<<< orphan*/  tz ;
typedef  int /*<<< orphan*/  tv ;
struct timezone {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
typedef  unsigned long long UINT64 ;
typedef  scalar_t__ UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  gettimeofday (struct timezone*,struct timezone*) ; 
 int /*<<< orphan*/  memset (struct timezone*,int /*<<< orphan*/ ,int) ; 

UINT64 TickGetRealtimeTickValue64()
{
	struct timeval tv;
	struct timezone tz;
	UINT64 ret;

	memset(&tv, 0, sizeof(tv));
	memset(&tz, 0, sizeof(tz));

	gettimeofday(&tv, &tz);

	if (sizeof(tv.tv_sec) != 4)
	{
		ret = (UINT64)tv.tv_sec * 1000ULL + (UINT64)tv.tv_usec / 1000ULL;
	}
	else
	{
		ret = (UINT64)((UINT64)((UINT32)tv.tv_sec)) * 1000ULL + (UINT64)tv.tv_usec / 1000ULL;
	}

	return ret;
}