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
typedef  TYPE_2__* shared_region_pager_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_8__ {scalar_t__ mo_control; } ;
struct TYPE_9__ {int ref_count; TYPE_1__ sc_pgr_hdr; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ MEMORY_OBJECT_CONTROL_NULL ; 
 TYPE_2__* SHARED_REGION_PAGER_NULL ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  kfree (TYPE_2__*,int) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memory_object_control_deallocate (scalar_t__) ; 
 int shared_region_pager_cache_limit ; 
 int shared_region_pager_count ; 
 int shared_region_pager_count_mapped ; 
 int /*<<< orphan*/  shared_region_pager_dequeue (TYPE_2__*) ; 
 int /*<<< orphan*/  shared_region_pager_lock ; 
 int /*<<< orphan*/  shared_region_pager_terminate_internal (TYPE_2__*) ; 
 int /*<<< orphan*/  shared_region_pager_trim () ; 

void
shared_region_pager_deallocate_internal(
	shared_region_pager_t	pager,
	boolean_t		locked)
{
	boolean_t	needs_trimming;
	int		count_unmapped;

	if (! locked) {
		lck_mtx_lock(&shared_region_pager_lock);
	}

	count_unmapped = (shared_region_pager_count -
			  shared_region_pager_count_mapped);
	if (count_unmapped > shared_region_pager_cache_limit) {
		/* we have too many unmapped pagers:  trim some */
		needs_trimming = TRUE;
	} else {
		needs_trimming = FALSE;
	}

	/* drop a reference on this pager */
	pager->ref_count--;

	if (pager->ref_count == 1) {
		/*
		 * Only the "named" reference is left, which means that
		 * no one is really holding on to this pager anymore.
		 * Terminate it.
		 */
		shared_region_pager_dequeue(pager);
		/* the pager is all ours: no need for the lock now */
		lck_mtx_unlock(&shared_region_pager_lock);
		shared_region_pager_terminate_internal(pager);
	} else if (pager->ref_count == 0) {
		/*
		 * Dropped the existence reference;  the memory object has
		 * been terminated.  Do some final cleanup and release the
		 * pager structure.
		 */
		lck_mtx_unlock(&shared_region_pager_lock);
		if (pager->sc_pgr_hdr.mo_control != MEMORY_OBJECT_CONTROL_NULL) {
			memory_object_control_deallocate(pager->sc_pgr_hdr.mo_control);
			pager->sc_pgr_hdr.mo_control = MEMORY_OBJECT_CONTROL_NULL;
		}
		kfree(pager, sizeof (*pager));
		pager = SHARED_REGION_PAGER_NULL;
	} else {
		/* there are still plenty of references:  keep going... */
		lck_mtx_unlock(&shared_region_pager_lock);
	}

	if (needs_trimming) {
		shared_region_pager_trim();
	}
	/* caution: lock is not held on return... */
}