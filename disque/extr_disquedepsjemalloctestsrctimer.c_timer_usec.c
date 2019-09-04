#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_6__ {int tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_5__ {int tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_7__ {TYPE_2__ tv0; TYPE_1__ tv1; } ;
typedef  TYPE_3__ timedelta_t ;

/* Variables and functions */

uint64_t
timer_usec(const timedelta_t *timer)
{

#ifdef _WIN32
	uint64_t t0, t1;
	t0 = (((uint64_t)timer->ft0.dwHighDateTime) << 32) |
	    timer->ft0.dwLowDateTime;
	t1 = (((uint64_t)timer->ft1.dwHighDateTime) << 32) |
	    timer->ft1.dwLowDateTime;
	return ((t1 - t0) / 10);
#elif JEMALLOC_CLOCK_GETTIME
	return (((timer->ts1.tv_sec - timer->ts0.tv_sec) * 1000000) +
	    (timer->ts1.tv_nsec - timer->ts0.tv_nsec) / 1000);
#else
	return (((timer->tv1.tv_sec - timer->tv0.tv_sec) * 1000000) +
	    timer->tv1.tv_usec - timer->tv0.tv_usec);
#endif
}