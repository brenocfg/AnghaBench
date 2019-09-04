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
struct TYPE_3__ {int _b_limit; int _b_lock; int _b_waiters; int _b_count; int _b_waiters2; } ;
typedef  TYPE_1__ pthread_barrier_t ;

/* Variables and functions */
 int INT_MAX ; 
 int INT_MIN ; 
 int PTHREAD_BARRIER_SERIAL_THREAD ; 
 int /*<<< orphan*/  __vm_lock () ; 
 int /*<<< orphan*/  __vm_unlock () ; 
 int /*<<< orphan*/  __wait (int*,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __wake (int*,int,int /*<<< orphan*/ ) ; 
 int a_cas (int*,int,int) ; 
 int a_fetch_add (int*,int) ; 
 int /*<<< orphan*/  a_store (int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pshared_barrier_wait(pthread_barrier_t *b)
{
	int limit = (b->_b_limit & INT_MAX) + 1;
	int ret = 0;
	int v, w;

	if (limit==1) return PTHREAD_BARRIER_SERIAL_THREAD;

	while ((v=a_cas(&b->_b_lock, 0, limit)))
		__wait(&b->_b_lock, &b->_b_waiters, v, 0);

	/* Wait for <limit> threads to get to the barrier */
	if (++b->_b_count == limit) {
		a_store(&b->_b_count, 0);
		ret = PTHREAD_BARRIER_SERIAL_THREAD;
		if (b->_b_waiters2) __wake(&b->_b_count, -1, 0);
	} else {
		a_store(&b->_b_lock, 0);
		if (b->_b_waiters) __wake(&b->_b_lock, 1, 0);
		while ((v=b->_b_count)>0)
			__wait(&b->_b_count, &b->_b_waiters2, v, 0);
	}

	__vm_lock();

	/* Ensure all threads have a vm lock before proceeding */
	if (a_fetch_add(&b->_b_count, -1)==1-limit) {
		a_store(&b->_b_count, 0);
		if (b->_b_waiters2) __wake(&b->_b_count, -1, 0);
	} else {
		while ((v=b->_b_count))
			__wait(&b->_b_count, &b->_b_waiters2, v, 0);
	}
	
	/* Perform a recursive unlock suitable for self-sync'd destruction */
	do {
		v = b->_b_lock;
		w = b->_b_waiters;
	} while (a_cas(&b->_b_lock, v, v==INT_MIN+1 ? 0 : v-1) != v);

	/* Wake a thread waiting to reuse or destroy the barrier */
	if (v==INT_MIN+1 || (v==1 && w))
		__wake(&b->_b_lock, 1, 0);

	__vm_unlock();

	return ret;
}