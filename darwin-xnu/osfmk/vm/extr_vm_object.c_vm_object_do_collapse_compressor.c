#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_object_t ;
typedef  scalar_t__ vm_object_size_t ;
typedef  scalar_t__ vm_object_offset_t ;
typedef  scalar_t__ memory_object_offset_t ;
struct TYPE_8__ {int /*<<< orphan*/  do_collapse_compressor_pages; int /*<<< orphan*/  do_collapse_compressor; } ;
struct TYPE_7__ {scalar_t__ vo_size; scalar_t__ vo_shadow_offset; scalar_t__ paging_offset; int /*<<< orphan*/  pager; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ VM_EXTERNAL_STATE_EXISTS ; 
 scalar_t__ VM_PAGE_NULL ; 
 scalar_t__ vm_compressor_pager_next_compressed (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ vm_compressor_pager_state_get (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vm_compressor_pager_transfer (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_6__ vm_counters ; 
 int /*<<< orphan*/  vm_object_lock_assert_exclusive (TYPE_1__*) ; 
 scalar_t__ vm_page_lookup (TYPE_1__*,scalar_t__) ; 

void
vm_object_do_collapse_compressor(
	vm_object_t object,
	vm_object_t backing_object)
{
	vm_object_offset_t new_offset, backing_offset;
	vm_object_size_t size;

	vm_counters.do_collapse_compressor++;

	vm_object_lock_assert_exclusive(object);
	vm_object_lock_assert_exclusive(backing_object);

	size = object->vo_size;

	/*
	 *	Move all compressed pages from backing_object
	 *	to the parent.
	 */

	for (backing_offset = object->vo_shadow_offset;
	     backing_offset < object->vo_shadow_offset + object->vo_size;
	     backing_offset += PAGE_SIZE) {
		memory_object_offset_t backing_pager_offset;

		/* find the next compressed page at or after this offset */
		backing_pager_offset = (backing_offset +
					backing_object->paging_offset);
		backing_pager_offset = vm_compressor_pager_next_compressed(
			backing_object->pager,
			backing_pager_offset);
		if (backing_pager_offset == (memory_object_offset_t) -1) {
			/* no more compressed pages */
			break;
		}
		backing_offset = (backing_pager_offset -
				  backing_object->paging_offset);

		new_offset = backing_offset - object->vo_shadow_offset;

		if (new_offset >= object->vo_size) {
			/* we're out of the scope of "object": done */
			break;
		}

		if ((vm_page_lookup(object, new_offset) != VM_PAGE_NULL) ||
		    (vm_compressor_pager_state_get(object->pager,
						   (new_offset +
						    object->paging_offset)) ==
		     VM_EXTERNAL_STATE_EXISTS)) {
			/*
			 * This page already exists in object, resident or
			 * compressed.
			 * We don't need this compressed page in backing_object
			 * and it will be reclaimed when we release
			 * backing_object.
			 */
			continue;
		}

		/*
		 * backing_object has this page in the VM compressor and
		 * we need to transfer it to object.
		 */
		vm_counters.do_collapse_compressor_pages++;
		vm_compressor_pager_transfer(
			/* destination: */
			object->pager,
			(new_offset + object->paging_offset),
			/* source: */
			backing_object->pager,
			(backing_offset + backing_object->paging_offset));
	}
}