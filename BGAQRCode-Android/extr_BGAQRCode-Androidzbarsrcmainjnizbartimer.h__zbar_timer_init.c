#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int tv_nsec; int tv_sec; } ;
typedef  TYPE_1__ zbar_timer_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static inline zbar_timer_t *_zbar_timer_init (zbar_timer_t *timer,
                                              int delay)
{
    if(delay < 0)
        return(NULL);

    clock_gettime(CLOCK_REALTIME, timer);
    timer->tv_nsec += (delay % 1000) * 1000000;
    timer->tv_sec += (delay / 1000) + (timer->tv_nsec / 1000000000);
    timer->tv_nsec %= 1000000000;
    return(timer);
}