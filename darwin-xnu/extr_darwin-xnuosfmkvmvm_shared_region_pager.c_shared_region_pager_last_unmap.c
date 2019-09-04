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
typedef  TYPE_1__* shared_region_pager_t ;
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
 int shared_region_pager_count ; 
 int shared_region_pager_count_mapped ; 
 int shared_region_pager_count_unmapped_max ; 
 int /*<<< orphan*/  shared_region_pager_deallocate_internal (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shared_region_pager_lock ; 
 TYPE_1__* shared_region_pager_lookup (int /*<<< orphan*/ ) ; 

kern_return_t
shared_region_pager_last_unmap(
	memory_object_t		mem_obj)
{
	shared_region_pager_t	pager;
	int			count_unmapped;

	PAGER_DEBUG(PAGER_ALL,
		    ("shared_region_pager_last_unmap: %p\n", mem_obj));

	pager = shared_region_pager_lookup(mem_obj);

	lck_mtx_lock(&shared_region_pager_lock);
	if (pager->is_mapped) {
		/*
		 * All the mappings are gone, so let go of the one extra
		 * reference that represents all the mappings of this pager.
		 */
		shared_region_pager_count_mapped--;
		count_unmapped = (shared_region_pager_count -
				  shared_region_pager_count_mapped);
		if (count_unmapped > shared_region_pager_count_unmapped_max) {
			shared_region_pager_count_unmapped_max = count_unmapped;
		}
		pager->is_mapped = FALSE;
		shared_region_pager_deallocate_internal(pager, TRUE);
		/* caution: deallocate_internal() released the lock ! */
	} else {
		lck_mtx_unlock(&shared_region_pager_lock);
	}

	return KERN_SUCCESS;
}