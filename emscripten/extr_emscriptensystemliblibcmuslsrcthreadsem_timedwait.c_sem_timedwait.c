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
struct timespec {int dummy; } ;
struct TYPE_4__ {scalar_t__* __val; } ;
typedef  TYPE_1__ sem_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int EINTR ; 
 int __timedwait_cp (scalar_t__*,int,int /*<<< orphan*/ ,struct timespec const*,scalar_t__) ; 
 int /*<<< orphan*/  a_cas (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  a_inc (scalar_t__*) ; 
 int /*<<< orphan*/  a_spin () ; 
 int /*<<< orphan*/  cleanup ; 
 int errno ; 
 int /*<<< orphan*/  pthread_cleanup_pop (int) ; 
 int /*<<< orphan*/  pthread_cleanup_push (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pthread_testcancel () ; 
 scalar_t__ sem_trywait (TYPE_1__*) ; 

int sem_timedwait(sem_t *restrict sem, const struct timespec *restrict at)
{
	pthread_testcancel();

	if (!sem_trywait(sem)) return 0;

	int spins = 100;
	while (spins-- && sem->__val[0] <= 0 && !sem->__val[1]) a_spin();

	while (sem_trywait(sem)) {
		int r;
		a_inc(sem->__val+1);
		a_cas(sem->__val, 0, -1);
		pthread_cleanup_push(cleanup, (void *)(sem->__val+1));
		r = __timedwait_cp(sem->__val, -1, CLOCK_REALTIME, at, sem->__val[2]);
		pthread_cleanup_pop(1);
		if (r && r != EINTR) {
#ifdef __EMSCRIPTEN__
			if (r == ECANCELED) r = EINTR;
#endif
			errno = r;
			return -1;
		}
	}
	return 0;
}