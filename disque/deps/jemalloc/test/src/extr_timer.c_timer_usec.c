#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_14__ {int tv_sec; int tv_usec; } ;
struct TYPE_13__ {int tv_sec; int tv_usec; } ;
struct TYPE_12__ {int tv_sec; int tv_nsec; } ;
struct TYPE_11__ {int tv_sec; int tv_nsec; } ;
struct TYPE_10__ {int dwLowDateTime; scalar_t__ dwHighDateTime; } ;
struct TYPE_9__ {int dwLowDateTime; scalar_t__ dwHighDateTime; } ;
struct TYPE_15__ {TYPE_6__ tv0; TYPE_5__ tv1; TYPE_4__ ts0; TYPE_3__ ts1; TYPE_2__ ft1; TYPE_1__ ft0; } ;
typedef  TYPE_7__ timedelta_t ;

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