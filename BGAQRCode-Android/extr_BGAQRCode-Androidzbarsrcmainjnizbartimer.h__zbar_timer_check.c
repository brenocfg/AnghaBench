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
struct TYPE_3__ {int tv_sec; int tv_nsec; } ;
typedef  TYPE_1__ zbar_timer_t ;
struct timespec {int tv_sec; int tv_nsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 

__attribute__((used)) static inline int _zbar_timer_check (zbar_timer_t *timer)
{
    struct timespec now;
    int delay;
    if(!timer)
        return(-1);

    clock_gettime(CLOCK_REALTIME, &now);
    delay = ((timer->tv_sec - now.tv_sec) * 1000 +
             (timer->tv_nsec - now.tv_nsec) / 1000000);
    return((delay >= 0) ? delay : 0);
}