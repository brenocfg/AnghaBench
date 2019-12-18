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
struct TYPE_3__ {scalar_t__ initialized; void* rw_owner; int rw_count; int /*<<< orphan*/  rw_lock; } ;
typedef  TYPE_1__ krwlock_t ;
typedef  scalar_t__ krw_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ B_TRUE ; 
 scalar_t__ RW_READER ; 
 int /*<<< orphan*/  atomic_add_int (int*,int) ; 
 void* curthread ; 
 int rw_tryrdlock (int /*<<< orphan*/ *) ; 
 int rw_trywrlock (int /*<<< orphan*/ *) ; 

int
rw_tryenter(krwlock_t *rwlp, krw_t rw)
{
	int rv;

	ASSERT(rwlp->initialized == B_TRUE);
	ASSERT(rwlp->rw_owner != (void *)-1UL);
	ASSERT(rwlp->rw_owner != curthread);

	if (rw == RW_READER)
		rv = rw_tryrdlock(&rwlp->rw_lock);
	else
		rv = rw_trywrlock(&rwlp->rw_lock);

	if (rv == 0) {
		ASSERT(rwlp->rw_owner == NULL);
		if (rw == RW_READER) {
			ASSERT(rwlp->rw_count >= 0);
			atomic_add_int(&rwlp->rw_count, 1);
		} else {
			ASSERT(rwlp->rw_count == 0);
			rwlp->rw_count = -1;
			rwlp->rw_owner = curthread;
		}
		return (1);
	}

	return (0);
}