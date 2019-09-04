#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_object_t ;
typedef  scalar_t__ uint32_t ;
typedef  TYPE_2__* purgeable_q_t ;
typedef  enum purgeable_q_type { ____Placeholder_purgeable_q_type } purgeable_q_type ;
struct TYPE_11__ {scalar_t__ debug_count_objects; int /*<<< orphan*/ * objq; } ;
struct TYPE_10__ {scalar_t__ purgable; scalar_t__ purgeable_when_ripe; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_MACH_VM ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACHDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NUM_VOLATILE_GROUPS ; 
 int /*<<< orphan*/  OBJECT_PURGE_ALL ; 
 int PURGEABLE_Q_TYPE_MAX ; 
 int PURGEABLE_Q_TYPE_OBSOLETE ; 
 TYPE_1__* VM_OBJECT_NULL ; 
 scalar_t__ VM_PURGABLE_EMPTY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  available_for_purge ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_pause (int /*<<< orphan*/ ) ; 
 TYPE_2__* purgeable_queues ; 
 int /*<<< orphan*/  queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_object_purge (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_lock_queues () ; 
 int /*<<< orphan*/  vm_page_unlock_queues () ; 
 TYPE_1__* vm_purgeable_object_find_and_lock (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_purgeable_queue_lock ; 
 int /*<<< orphan*/  vm_purgeable_token_remove_first (TYPE_2__*) ; 

void
vm_purgeable_object_purge_all(void)
{
	enum purgeable_q_type i;
	int             group;
	vm_object_t     object;
	unsigned int	purged_count;
	uint32_t	collisions;

	purged_count = 0;
	collisions = 0;

restart:
	lck_mtx_lock(&vm_purgeable_queue_lock);
	/* Cycle through all queues */
	for (i = PURGEABLE_Q_TYPE_OBSOLETE; i < PURGEABLE_Q_TYPE_MAX; i++) {
		purgeable_q_t   queue;

		queue = &purgeable_queues[i];

		/*
		 * Look through all groups, starting from the lowest. If
		 * we find an object in that group, try to lock it (this can
		 * fail). If locking is successful, we can drop the queue
		 * lock, remove a token and then purge the object.
		 */
		for (group = 0; group < NUM_VOLATILE_GROUPS; group++) {
			while (!queue_empty(&queue->objq[group])) {
				object = vm_purgeable_object_find_and_lock(queue, group, FALSE);
				if (object == VM_OBJECT_NULL) {
					lck_mtx_unlock(&vm_purgeable_queue_lock);
					mutex_pause(collisions++);
					goto restart;
				}

				lck_mtx_unlock(&vm_purgeable_queue_lock);
				
				/* Lock the page queue here so we don't hold it
				 * over the whole, legthy operation */
				if (object->purgeable_when_ripe) {
					vm_page_lock_queues();
					vm_purgeable_token_remove_first(queue);
					vm_page_unlock_queues();
				}
				
				(void) vm_object_purge(object, 0);
				assert(object->purgable == VM_PURGABLE_EMPTY);
				/* no change in purgeable accounting */

				vm_object_unlock(object);
				purged_count++;
				goto restart;
			}
			assert(queue->debug_count_objects >= 0);
		}
	}
	KERNEL_DEBUG_CONSTANT((MACHDBG_CODE(DBG_MACH_VM, OBJECT_PURGE_ALL)),
			      purged_count, /* # of purged objects */
			      0,
			      available_for_purge,
			      0,
			      0);
	lck_mtx_unlock(&vm_purgeable_queue_lock);
	return;
}