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
typedef  TYPE_1__* swapfile_pager_t ;
typedef  int /*<<< orphan*/  memory_object_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_4__ {scalar_t__ is_mapped; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  PAGER_ALL ; 
 int /*<<< orphan*/  PAGER_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swapfile_pager_deallocate_internal (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swapfile_pager_lock ; 
 TYPE_1__* swapfile_pager_lookup (int /*<<< orphan*/ ) ; 

kern_return_t
swapfile_pager_last_unmap(
	memory_object_t		mem_obj)
{
	swapfile_pager_t	pager;

	PAGER_DEBUG(PAGER_ALL,
		    ("swapfile_pager_last_unmap: %p\n", mem_obj));

	pager = swapfile_pager_lookup(mem_obj);

	lck_mtx_lock(&swapfile_pager_lock);
	if (pager->is_mapped) {
		/*
		 * All the mappings are gone, so let go of the one extra
		 * reference that represents all the mappings of this pager.
		 */
		pager->is_mapped = FALSE;
		swapfile_pager_deallocate_internal(pager, TRUE);
		/* caution: deallocate_internal() released the lock ! */
	} else {
		lck_mtx_unlock(&swapfile_pager_lock);
	}
	
	return KERN_SUCCESS;
}