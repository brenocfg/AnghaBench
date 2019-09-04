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
struct TYPE_3__ {int /*<<< orphan*/  _rw_lock; } ;
typedef  TYPE_1__ pthread_rwlock_t ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ a_cas (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int pthread_rwlock_trywrlock(pthread_rwlock_t *rw)
{
	if (a_cas(&rw->_rw_lock, 0, 0x7fffffff)) return EBUSY;
#ifdef __EMSCRIPTEN__
	/// XXX Emscripten: The spec allows detecting when multiple write locks would deadlock, which we do here to avoid hangs.
	/// Mark this thread to own the write lock, to ignore multiple attempts to lock.
	rw->_rw_wr_owner = (int)pthread_self();
#endif
	return 0;
}