#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct timespec {int dummy; } ;
struct TYPE_5__ {int _m_type; int _m_lock; int /*<<< orphan*/  _m_waiters; } ;
typedef  TYPE_1__ pthread_mutex_t ;
struct TYPE_6__ {int tid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int EBUSY ; 
 int EDEADLK ; 
 int EINTR ; 
 int PTHREAD_MUTEX_ERRORCHECK ; 
 int PTHREAD_MUTEX_NORMAL ; 
 TYPE_3__* __pthread_self () ; 
 int __timedwait (int*,int,int /*<<< orphan*/ ,struct timespec const*,int) ; 
 int /*<<< orphan*/  a_cas (int*,int,int) ; 
 int /*<<< orphan*/  a_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  a_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  a_spin () ; 
 int pthread_mutex_trylock (TYPE_1__*) ; 

int __pthread_mutex_timedlock(pthread_mutex_t *restrict m, const struct timespec *restrict at)
{
	if ((m->_m_type&15) == PTHREAD_MUTEX_NORMAL
	    && !a_cas(&m->_m_lock, 0, EBUSY))
		return 0;

	int r, t, priv = (m->_m_type & 128) ^ 128;

	r = pthread_mutex_trylock(m);
	if (r != EBUSY) return r;
	
	int spins = 100;
	while (spins-- && m->_m_lock && !m->_m_waiters) a_spin();

	while ((r=pthread_mutex_trylock(m)) == EBUSY) {
		if (!(r=m->_m_lock) || ((r&0x40000000) && (m->_m_type&4)))
			continue;
		if ((m->_m_type&3) == PTHREAD_MUTEX_ERRORCHECK
		 && (r&0x7fffffff) == __pthread_self()->tid)
			return EDEADLK;

		a_inc(&m->_m_waiters);
		t = r | 0x80000000;
		a_cas(&m->_m_lock, r, t);
		r = __timedwait(&m->_m_lock, t, CLOCK_REALTIME, at, priv);
		a_dec(&m->_m_waiters);
		if (r && r != EINTR) break;
	}
	return r;
}