#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct waiter {int barrier; int state; struct waiter* prev; struct waiter* next; int /*<<< orphan*/ * notify; int /*<<< orphan*/  member_0; } ;
struct timespec {unsigned long tv_nsec; } ;
struct TYPE_8__ {int _m_type; int _m_lock; int /*<<< orphan*/  _m_waiters; } ;
typedef  TYPE_1__ pthread_mutex_t ;
struct TYPE_9__ {int _c_clock; int _c_seq; int _c_lock; struct waiter* _c_tail; struct waiter* _c_head; int /*<<< orphan*/  _c_waiters; scalar_t__ _c_shared; } ;
typedef  TYPE_2__ pthread_cond_t ;
struct TYPE_10__ {int tid; } ;

/* Variables and functions */
 int ECANCELED ; 
 int EINTR ; 
 int EINVAL ; 
 int EPERM ; 
 int INT_MAX ; 
 int /*<<< orphan*/  LEAVING ; 
 int PTHREAD_CANCEL_DISABLE ; 
 int PTHREAD_CANCEL_MASKED ; 
 int WAITING ; 
 int /*<<< orphan*/  __pthread_mutex_unlock (TYPE_1__*) ; 
 TYPE_4__* __pthread_self () ; 
 int /*<<< orphan*/  __pthread_setcancelstate (int,int*) ; 
 int /*<<< orphan*/  __pthread_testcancel () ; 
 int __timedwait_cp (int volatile*,int,int,struct timespec const*,int) ; 
 int /*<<< orphan*/  __wake (int /*<<< orphan*/ *,int,int) ; 
 int a_cas (int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a_dec (int /*<<< orphan*/ *) ; 
 int a_fetch_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  a_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock (int*) ; 
 int pthread_mutex_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  unlock (int*) ; 
 int /*<<< orphan*/  unlock_requeue (int*,int*,int) ; 

int __pthread_cond_timedwait(pthread_cond_t *restrict c, pthread_mutex_t *restrict m, const struct timespec *restrict ts)
{
	struct waiter node = { 0 };
	int e, seq, clock = c->_c_clock, cs, shared=0, oldstate, tmp;
	volatile int *fut;

	if ((m->_m_type&15) && (m->_m_lock&INT_MAX) != __pthread_self()->tid)
		return EPERM;

	if (ts && ts->tv_nsec >= 1000000000UL)
		return EINVAL;

	__pthread_testcancel();

	if (c->_c_shared) {
		shared = 1;
		fut = &c->_c_seq;
		seq = c->_c_seq;
		a_inc(&c->_c_waiters);
	} else {
		lock(&c->_c_lock);

		seq = node.barrier = 2;
		fut = &node.barrier;
		node.state = WAITING;
		node.next = c->_c_head;
		c->_c_head = &node;
		if (!c->_c_tail) c->_c_tail = &node;
		else node.next->prev = &node;

		unlock(&c->_c_lock);
	}

	__pthread_mutex_unlock(m);

	__pthread_setcancelstate(PTHREAD_CANCEL_MASKED, &cs);
	if (cs == PTHREAD_CANCEL_DISABLE) __pthread_setcancelstate(cs, 0);

	do e = __timedwait_cp(fut, seq, clock, ts, !shared);
	while (*fut==seq && (!e || e==EINTR));
	if (e == EINTR) e = 0;

	if (shared) {
		/* Suppress cancellation if a signal was potentially
		 * consumed; this is a legitimate form of spurious
		 * wake even if not. */
		if (e == ECANCELED && c->_c_seq != seq) e = 0;
		if (a_fetch_add(&c->_c_waiters, -1) == -0x7fffffff)
			__wake(&c->_c_waiters, 1, 0);
		oldstate = WAITING;
		goto relock;
	}

	oldstate = a_cas(&node.state, WAITING, LEAVING);

	if (oldstate == WAITING) {
		/* Access to cv object is valid because this waiter was not
		 * yet signaled and a new signal/broadcast cannot return
		 * after seeing a LEAVING waiter without getting notified
		 * via the futex notify below. */

		lock(&c->_c_lock);
		
		if (c->_c_head == &node) c->_c_head = node.next;
		else if (node.prev) node.prev->next = node.next;
		if (c->_c_tail == &node) c->_c_tail = node.prev;
		else if (node.next) node.next->prev = node.prev;
		
		unlock(&c->_c_lock);

		if (node.notify) {
			if (a_fetch_add(node.notify, -1)==1)
				__wake(node.notify, 1, 1);
		}
	} else {
		/* Lock barrier first to control wake order. */
		lock(&node.barrier);
	}

relock:
	/* Errors locking the mutex override any existing error or
	 * cancellation, since the caller must see them to know the
	 * state of the mutex. */
	if ((tmp = pthread_mutex_lock(m))) e = tmp;

	if (oldstate == WAITING) goto done;

	if (!node.next) a_inc(&m->_m_waiters);

	/* Unlock the barrier that's holding back the next waiter, and
	 * either wake it or requeue it to the mutex. */
	if (node.prev)
		unlock_requeue(&node.prev->barrier, &m->_m_lock, m->_m_type & 128);
	else
		a_dec(&m->_m_waiters);

	/* Since a signal was consumed, cancellation is not permitted. */
	if (e == ECANCELED) e = 0;

done:
	__pthread_setcancelstate(cs, 0);

	if (e == ECANCELED) {
		__pthread_testcancel();
		__pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, 0);
	}

#ifdef __EMSCRIPTEN__
	pthread_testcancel();
#endif

	return e;
}