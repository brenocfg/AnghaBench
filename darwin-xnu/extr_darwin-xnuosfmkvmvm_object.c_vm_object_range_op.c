#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  TYPE_2__* vm_object_t ;
typedef  scalar_t__ vm_object_offset_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_15__ {scalar_t__ resident_page_count; scalar_t__ phys_contiguous; } ;
struct TYPE_14__ {scalar_t__ vmp_pmapped; scalar_t__ vmp_busy; int /*<<< orphan*/  vmp_absent; scalar_t__ vmp_laundry; scalar_t__ vmp_cleaning; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_INVALID_OBJECT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ PAGE_MASK_64 ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PAGE_SLEEP (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THREAD_UNINT ; 
 scalar_t__ TRUE ; 
 int UPL_ROP_ABSENT ; 
 int UPL_ROP_DUMP ; 
 int UPL_ROP_PRESENT ; 
 int /*<<< orphan*/  VM_PAGE_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  VM_PAGE_GET_PHYS_PAGE (TYPE_1__*) ; 
 TYPE_1__* VM_PAGE_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pmap_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_unlock (TYPE_2__*) ; 
 TYPE_1__* vm_page_lookup (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  vm_pageout_steal_laundry (TYPE_1__*,int /*<<< orphan*/ ) ; 

kern_return_t
vm_object_range_op(
	vm_object_t		object,
	vm_object_offset_t	offset_beg,
	vm_object_offset_t	offset_end,
	int                     ops,
	uint32_t		*range)
{
        vm_object_offset_t	offset;
	vm_page_t		dst_page;

	if (offset_end - offset_beg > (uint32_t) -1) {
		/* range is too big and would overflow "*range" */
		return KERN_INVALID_ARGUMENT;
	} 
	if (object->resident_page_count == 0) {
	        if (range) {
		        if (ops & UPL_ROP_PRESENT) {
			        *range = 0;
			} else {
			        *range = (uint32_t) (offset_end - offset_beg);
				assert(*range == (offset_end - offset_beg));
			}
		}
		return KERN_SUCCESS;
	}
	vm_object_lock(object);

	if (object->phys_contiguous) {
		vm_object_unlock(object);
	        return KERN_INVALID_OBJECT;
	}
	
	offset = offset_beg & ~PAGE_MASK_64;

	while (offset < offset_end) {
		dst_page = vm_page_lookup(object, offset);
		if (dst_page != VM_PAGE_NULL) {
			if (ops & UPL_ROP_DUMP) {
				if (dst_page->vmp_busy || dst_page->vmp_cleaning) {
					/*
					 * someone else is playing with the 
					 * page, we will have to wait
					 */
				        PAGE_SLEEP(object, dst_page, THREAD_UNINT);
					/*
					 * need to relook the page up since it's
					 * state may have changed while we slept
					 * it might even belong to a different object
					 * at this point
					 */
					continue;
				}
				if (dst_page->vmp_laundry)
					vm_pageout_steal_laundry(dst_page, FALSE);

				if (dst_page->vmp_pmapped == TRUE)
				        pmap_disconnect(VM_PAGE_GET_PHYS_PAGE(dst_page));

				VM_PAGE_FREE(dst_page);

			} else if ((ops & UPL_ROP_ABSENT)
					   && (!dst_page->vmp_absent || dst_page->vmp_busy)) {
				break;
			}
		} else if (ops & UPL_ROP_PRESENT)
		        break;

		offset += PAGE_SIZE;
	}
	vm_object_unlock(object);

	if (range) {
	        if (offset > offset_end)
		        offset = offset_end;
		if(offset > offset_beg) {
			*range = (uint32_t) (offset - offset_beg);
			assert(*range == (offset - offset_beg));
		} else {
			*range = 0;
		}
	}
	return KERN_SUCCESS;
}