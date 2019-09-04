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
typedef  int /*<<< orphan*/  memory_object_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  TYPE_1__* fourk_pager_t ;
struct TYPE_4__ {scalar_t__ is_mapped; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  PAGER_ALL ; 
 int /*<<< orphan*/  PAGER_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int fourk_pager_count ; 
 int fourk_pager_count_mapped ; 
 int fourk_pager_count_unmapped_max ; 
 int /*<<< orphan*/  fourk_pager_deallocate_internal (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fourk_pager_lock ; 
 TYPE_1__* fourk_pager_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 

kern_return_t
fourk_pager_last_unmap(
	memory_object_t		mem_obj)
{
	fourk_pager_t	pager;
	int			count_unmapped;

	PAGER_DEBUG(PAGER_ALL,
		    ("fourk_pager_last_unmap: %p\n", mem_obj));

	pager = fourk_pager_lookup(mem_obj);

	lck_mtx_lock(&fourk_pager_lock);
	if (pager->is_mapped) {
		/*
		 * All the mappings are gone, so let go of the one extra
		 * reference that represents all the mappings of this pager.
		 */
		fourk_pager_count_mapped--;
		count_unmapped = (fourk_pager_count -
				  fourk_pager_count_mapped);
		if (count_unmapped > fourk_pager_count_unmapped_max) {
			fourk_pager_count_unmapped_max = count_unmapped;
		}
		pager->is_mapped = FALSE;
		fourk_pager_deallocate_internal(pager, TRUE);
		/* caution: deallocate_internal() released the lock ! */
	} else {
		lck_mtx_unlock(&fourk_pager_lock);
	}
	
	return KERN_SUCCESS;
}