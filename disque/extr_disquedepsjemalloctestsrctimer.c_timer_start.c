#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  tv0; } ;
typedef  TYPE_1__ timedelta_t ;

/* Variables and functions */
 int /*<<< orphan*/  gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
timer_start(timedelta_t *timer)
{

#ifdef _WIN32
	GetSystemTimeAsFileTime(&timer->ft0);
#elif JEMALLOC_CLOCK_GETTIME
	if (sysconf(_SC_MONOTONIC_CLOCK) <= 0)
		timer->clock_id = CLOCK_REALTIME;
	else
		timer->clock_id = CLOCK_MONOTONIC;
	clock_gettime(timer->clock_id, &timer->ts0);
#else
	gettimeofday(&timer->tv0, NULL);
#endif
}