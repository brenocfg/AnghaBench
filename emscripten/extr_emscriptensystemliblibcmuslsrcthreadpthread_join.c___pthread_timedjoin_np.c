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
struct timespec {int dummy; } ;
typedef  TYPE_1__* pthread_t ;
struct TYPE_3__ {int tid; int /*<<< orphan*/  map_size; scalar_t__ map_base; void* result; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int PTHREAD_CANCEL_DISABLE ; 
 int PTHREAD_CANCEL_ENABLE ; 
 int /*<<< orphan*/  __munmap (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __pthread_setcancelstate (int,int*) ; 
 int /*<<< orphan*/  __pthread_testcancel () ; 
 int __timedwait_cp (int*,int,int /*<<< orphan*/ ,struct timespec const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a_barrier () ; 

int __pthread_timedjoin_np(pthread_t t, void **res, const struct timespec *at)
{
	int tmp, cs, r = 0;
	__pthread_testcancel();
	__pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &cs);
	if (cs == PTHREAD_CANCEL_ENABLE) __pthread_setcancelstate(cs, 0);
	while ((tmp = t->tid) && r != ETIMEDOUT && r != EINVAL)
		r = __timedwait_cp(&t->tid, tmp, CLOCK_REALTIME, at, 0);
	__pthread_setcancelstate(cs, 0);
	if (r == ETIMEDOUT || r == EINVAL) return r;
	a_barrier();
	if (res) *res = t->result;
	if (t->map_base) __munmap(t->map_base, t->map_size);
	return 0;
}