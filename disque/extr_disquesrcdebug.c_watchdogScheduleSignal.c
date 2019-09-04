#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_3__ {int tv_sec; int tv_usec; } ;
struct itimerval {TYPE_2__ it_interval; TYPE_1__ it_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  ITIMER_REAL ; 
 int /*<<< orphan*/  setitimer (int /*<<< orphan*/ ,struct itimerval*,int /*<<< orphan*/ *) ; 

void watchdogScheduleSignal(int period) {
    struct itimerval it;

    /* Will stop the timer if period is 0. */
    it.it_value.tv_sec = period/1000;
    it.it_value.tv_usec = (period%1000)*1000;
    /* Don't automatically restart. */
    it.it_interval.tv_sec = 0;
    it.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &it, NULL);
}