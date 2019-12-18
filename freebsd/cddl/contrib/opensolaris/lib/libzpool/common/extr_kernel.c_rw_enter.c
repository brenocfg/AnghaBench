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
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  atomic_add_int (int*,int) ; 
 void* curthread ; 
 scalar_t__ rw_rdlock (int /*<<< orphan*/ *) ; 
 scalar_t__ rw_wrlock (int /*<<< orphan*/ *) ; 

void
rw_enter(krwlock_t *rwlp, krw_t rw)
{
	//ASSERT(!RW_LOCK_HELD(rwlp));
	ASSERT(rwlp->initialized == B_TRUE);
	ASSERT(rwlp->rw_owner != (void *)-1UL);
	ASSERT(rwlp->rw_owner != curthread);

	if (rw == RW_READER) {
		VERIFY(rw_rdlock(&rwlp->rw_lock) == 0);
		ASSERT(rwlp->rw_count >= 0);
		atomic_add_int(&rwlp->rw_count, 1);
	} else {
		VERIFY(rw_wrlock(&rwlp->rw_lock) == 0);
		ASSERT(rwlp->rw_count == 0);
		rwlp->rw_count = -1;
		rwlp->rw_owner = curthread;
	}
}