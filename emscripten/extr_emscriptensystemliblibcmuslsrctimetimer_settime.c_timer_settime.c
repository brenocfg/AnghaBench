#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* timer_t ;
struct itimerspec {int dummy; } ;
typedef  TYPE_1__* pthread_t ;
struct TYPE_2__ {int timer_id; } ;

/* Variables and functions */
 int INT_MAX ; 
 int /*<<< orphan*/  SYS_timer_settime ; 
 int syscall (int /*<<< orphan*/ ,void*,int,struct itimerspec const*,struct itimerspec*) ; 

int timer_settime(timer_t t, int flags, const struct itimerspec *restrict val, struct itimerspec *restrict old)
{
	if ((intptr_t)t < 0) {
		pthread_t td = (void *)((uintptr_t)t << 1);
		t = (void *)(uintptr_t)(td->timer_id & INT_MAX);
	}
	return syscall(SYS_timer_settime, t, flags, val, old);
}