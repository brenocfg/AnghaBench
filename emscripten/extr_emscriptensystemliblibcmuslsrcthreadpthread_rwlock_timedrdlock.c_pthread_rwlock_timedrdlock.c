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
struct TYPE_4__ {int _rw_lock; int _rw_shared; int /*<<< orphan*/  _rw_waiters; } ;
typedef  TYPE_1__ pthread_rwlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int EBUSY ; 
 int EINTR ; 
 int __timedwait (int*,int,int /*<<< orphan*/ ,struct timespec const*,int) ; 
 int /*<<< orphan*/  a_cas (int*,int,int) ; 
 int /*<<< orphan*/  a_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  a_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  a_spin () ; 
 int pthread_rwlock_tryrdlock (TYPE_1__*) ; 

int pthread_rwlock_timedrdlock(pthread_rwlock_t *restrict rw, const struct timespec *restrict at)
{
	int r, t;

	r = pthread_rwlock_tryrdlock(rw);
	if (r != EBUSY) return r;
	
	int spins = 100;
	while (spins-- && rw->_rw_lock && !rw->_rw_waiters) a_spin();

	while ((r=pthread_rwlock_tryrdlock(rw))==EBUSY) {
		if (!(r=rw->_rw_lock) || (r&0x7fffffff)!=0x7fffffff) continue;
		t = r | 0x80000000;
		a_inc(&rw->_rw_waiters);
		a_cas(&rw->_rw_lock, r, t);
		r = __timedwait(&rw->_rw_lock, t, CLOCK_REALTIME, at, rw->_rw_shared^128);
		a_dec(&rw->_rw_waiters);
		if (r && r != EINTR) return r;
	}
	return r;
}