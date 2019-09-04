#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* swapfile_pager_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_8__ {scalar_t__ mo_control; } ;
struct TYPE_9__ {int ref_count; TYPE_1__ swp_pgr_hdr; } ;

/* Variables and functions */
 scalar_t__ MEMORY_OBJECT_CONTROL_NULL ; 
 TYPE_2__* SWAPFILE_PAGER_NULL ; 
 int /*<<< orphan*/  kfree (TYPE_2__*,int) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memory_object_control_deallocate (scalar_t__) ; 
 int /*<<< orphan*/  swapfile_pager_dequeue (TYPE_2__*) ; 
 int /*<<< orphan*/  swapfile_pager_lock ; 
 int /*<<< orphan*/  swapfile_pager_terminate_internal (TYPE_2__*) ; 

void
swapfile_pager_deallocate_internal(
	swapfile_pager_t	pager,
	boolean_t		locked)
{
	if (! locked) {
		lck_mtx_lock(&swapfile_pager_lock);
	}

	/* drop a reference on this pager */
	pager->ref_count--;

	if (pager->ref_count == 1) {
		/*
		 * Only the "named" reference is left, which means that
		 * no one is really holding on to this pager anymore.
		 * Terminate it.
		 */
		swapfile_pager_dequeue(pager);
		/* the pager is all ours: no need for the lock now */
		lck_mtx_unlock(&swapfile_pager_lock);
		swapfile_pager_terminate_internal(pager);
	} else if (pager->ref_count == 0) {
		/*
		 * Dropped the existence reference;  the memory object has
		 * been terminated.  Do some final cleanup and release the
		 * pager structure.
		 */
		lck_mtx_unlock(&swapfile_pager_lock);
		if (pager->swp_pgr_hdr.mo_control != MEMORY_OBJECT_CONTROL_NULL) {
			memory_object_control_deallocate(pager->swp_pgr_hdr.mo_control);
			pager->swp_pgr_hdr.mo_control = MEMORY_OBJECT_CONTROL_NULL;
		}
		kfree(pager, sizeof (*pager));
		pager = SWAPFILE_PAGER_NULL;
	} else {
		/* there are still plenty of references:  keep going... */
		lck_mtx_unlock(&swapfile_pager_lock);
	}

	/* caution: lock is not held on return... */
}