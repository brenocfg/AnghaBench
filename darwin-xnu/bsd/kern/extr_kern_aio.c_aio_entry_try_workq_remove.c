#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  aio_workq_t ;
struct TYPE_6__ {int /*<<< orphan*/ * tqe_prev; } ;
struct TYPE_7__ {TYPE_1__ aio_workq_link; } ;
typedef  TYPE_2__ aio_workq_entry ;

/* Variables and functions */
 int /*<<< orphan*/  aio_entry_workq (TYPE_2__*) ; 
 int /*<<< orphan*/  aio_workq_lock_spin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aio_workq_remove_entry_locked (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  aio_workq_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aio_entry_try_workq_remove(aio_workq_entry *entryp)
{	
	/* Can only be cancelled if it's still on a work queue */
	if (entryp->aio_workq_link.tqe_prev != NULL) {
		aio_workq_t queue;

		/* Will have to check again under the lock */
		queue = aio_entry_workq(entryp);
		aio_workq_lock_spin(queue);
		if (entryp->aio_workq_link.tqe_prev != NULL) {
			aio_workq_remove_entry_locked(queue, entryp);
			aio_workq_unlock(queue);
			return 1;
		}  else {
			aio_workq_unlock(queue);
		}
	}

	return 0;
}