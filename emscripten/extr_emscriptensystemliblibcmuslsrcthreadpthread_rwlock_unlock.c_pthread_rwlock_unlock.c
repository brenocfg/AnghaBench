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
struct TYPE_3__ {int _rw_shared; int _rw_lock; int _rw_waiters; } ;
typedef  TYPE_1__ pthread_rwlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  __wake (int*,int,int) ; 
 int a_cas (int*,int,int) ; 

int pthread_rwlock_unlock(pthread_rwlock_t *rw)
{
	int val, cnt, waiters, new, priv = rw->_rw_shared^128;

#ifdef __EMSCRIPTEN__
	/// XXX Emscripten: The spec allows detecting when multiple write locks would deadlock, which we do here to avoid hangs.
	/// Mark this thread to not own the write lock anymore.
	if (rw->_rw_wr_owner == (int)pthread_self()) rw->_rw_wr_owner = 0;
#endif

	do {
		val = rw->_rw_lock;
		cnt = val & 0x7fffffff;
		waiters = rw->_rw_waiters;
		new = (cnt == 0x7fffffff || cnt == 1) ? 0 : val-1;
	} while (a_cas(&rw->_rw_lock, val, new) != val);

	if (!new && (waiters || val<0))
		__wake(&rw->_rw_lock, cnt, priv);

	return 0;
}