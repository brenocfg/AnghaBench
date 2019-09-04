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
struct instance {int finished; int count; int last; scalar_t__ waiters; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int _b_limit; int _b_lock; scalar_t__ _b_waiters; struct instance* _b_inst; } ;
typedef  TYPE_1__ pthread_barrier_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 int FUTEX_WAIT ; 
 int PTHREAD_BARRIER_SERIAL_THREAD ; 
 int /*<<< orphan*/  SYS_futex ; 
 int /*<<< orphan*/  __syscall (int /*<<< orphan*/ ,int*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __wait (int*,scalar_t__*,int,int) ; 
 int /*<<< orphan*/  __wake (int*,int,int) ; 
 int a_fetch_add (int*,int) ; 
 int /*<<< orphan*/  a_inc (int*) ; 
 int /*<<< orphan*/  a_spin () ; 
 int /*<<< orphan*/  a_store (int*,int) ; 
 scalar_t__ a_swap (int*,int) ; 
 int pshared_barrier_wait (TYPE_1__*) ; 

int pthread_barrier_wait(pthread_barrier_t *b)
{
	int limit = b->_b_limit;
	struct instance *inst;

	/* Trivial case: count was set at 1 */
	if (!limit) return PTHREAD_BARRIER_SERIAL_THREAD;

	/* Process-shared barriers require a separate, inefficient wait */
	if (limit < 0) return pshared_barrier_wait(b);

	/* Otherwise we need a lock on the barrier object */
	while (a_swap(&b->_b_lock, 1))
		__wait(&b->_b_lock, &b->_b_waiters, 1, 1);
	inst = b->_b_inst;

	/* First thread to enter the barrier becomes the "instance owner" */
	if (!inst) {
		struct instance new_inst = { 0 };
		int spins = 200;
		b->_b_inst = inst = &new_inst;
		a_store(&b->_b_lock, 0);
		if (b->_b_waiters) __wake(&b->_b_lock, 1, 1);
		while (spins-- && !inst->finished)
			a_spin();
		a_inc(&inst->finished);
		while (inst->finished == 1) {
#ifdef __EMSCRIPTEN__
			emscripten_futex_wait(&inst->finished, 1, INFINITY);
#else
			__syscall(SYS_futex,&inst->finished,FUTEX_WAIT|128,1,0) != -ENOSYS
			|| __syscall(SYS_futex,&inst->finished,FUTEX_WAIT,1,0);
#endif
		}
		return PTHREAD_BARRIER_SERIAL_THREAD;
	}

	/* Last thread to enter the barrier wakes all non-instance-owners */
	if (++inst->count == limit) {
		b->_b_inst = 0;
		a_store(&b->_b_lock, 0);
		if (b->_b_waiters) __wake(&b->_b_lock, 1, 1);
		a_store(&inst->last, 1);
		if (inst->waiters)
			__wake(&inst->last, -1, 1);
	} else {
		a_store(&b->_b_lock, 0);
		if (b->_b_waiters) __wake(&b->_b_lock, 1, 1);
		__wait(&inst->last, &inst->waiters, 0, 1);
	}

	/* Last thread to exit the barrier wakes the instance owner */
	if (a_fetch_add(&inst->count,-1)==1 && a_fetch_add(&inst->finished,1))
		__wake(&inst->finished, 1, 1);

	return 0;
}