#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  int vm_map_size_t ;
typedef  int vm_map_offset_t ;
typedef  TYPE_1__* vm_map_entry_t ;
typedef  TYPE_2__* vm_map_copy_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_28__ {int /*<<< orphan*/  entries_pageable; } ;
struct TYPE_27__ {scalar_t__ type; int size; int offset; TYPE_3__ cpy_hdr; } ;
struct TYPE_26__ {int vme_start; int vme_end; scalar_t__ is_sub_map; struct TYPE_26__* vme_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ KERN_SUCCESS ; 
 int MAX (int /*<<< orphan*/ ,int) ; 
 int MIN (int,int) ; 
 int PAGE_MASK ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ VM_MAP_COPY_ENTRY_LIST ; 
 TYPE_2__* VM_MAP_COPY_NULL ; 
 int /*<<< orphan*/  VM_MAP_COPY_PAGE_MASK (TYPE_2__*) ; 
 int /*<<< orphan*/  VM_MAP_PAGE_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* vm_map_copy_allocate () ; 
 int /*<<< orphan*/  vm_map_copy_clip_end (TYPE_2__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  vm_map_copy_clip_start (TYPE_2__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  vm_map_copy_discard (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_copy_entry_link (TYPE_2__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_copy_entry_unlink (TYPE_2__*,TYPE_1__*) ; 
 TYPE_1__* vm_map_copy_first_entry (TYPE_2__*) ; 
 TYPE_1__* vm_map_copy_last_entry (TYPE_2__*) ; 
 scalar_t__ vm_map_copy_overwrite_nested (int /*<<< orphan*/ ,int,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* vm_map_copy_to_entry (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_lock_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_lookup_entry (int /*<<< orphan*/ ,int,TYPE_1__**) ; 
 int /*<<< orphan*/  vm_map_page_aligned (int,int) ; 
 int /*<<< orphan*/  vm_map_store_init (TYPE_3__*) ; 
 int /*<<< orphan*/  vm_map_unlock_read (int /*<<< orphan*/ ) ; 

kern_return_t
vm_map_copy_overwrite(
	vm_map_t	dst_map,
	vm_map_offset_t	dst_addr,
	vm_map_copy_t	copy,
	boolean_t	interruptible)
{
	vm_map_size_t	head_size, tail_size;
	vm_map_copy_t	head_copy, tail_copy;
	vm_map_offset_t	head_addr, tail_addr;
	vm_map_entry_t	entry;
	kern_return_t	kr;
	vm_map_offset_t	effective_page_mask, effective_page_size;

	head_size = 0;
	tail_size = 0;
	head_copy = NULL;
	tail_copy = NULL;
	head_addr = 0;
	tail_addr = 0;

	if (interruptible ||
	    copy == VM_MAP_COPY_NULL ||
	    copy->type != VM_MAP_COPY_ENTRY_LIST) {
		/*
		 * We can't split the "copy" map if we're interruptible
		 * or if we don't have a "copy" map...
		 */
	blunt_copy:
		return vm_map_copy_overwrite_nested(dst_map,
						    dst_addr,
						    copy,
						    interruptible,
						    (pmap_t) NULL,
						    TRUE);
	}

	effective_page_mask = MAX(VM_MAP_PAGE_MASK(dst_map), PAGE_MASK);
	effective_page_mask = MAX(VM_MAP_COPY_PAGE_MASK(copy),
				  effective_page_mask);
	effective_page_size = effective_page_mask + 1;

	if (copy->size < 3 * effective_page_size) {
		/*
		 * Too small to bother with optimizing...
		 */
		goto blunt_copy;
	}

	if ((dst_addr & effective_page_mask) !=
	    (copy->offset & effective_page_mask)) {
		/*
		 * Incompatible mis-alignment of source and destination...
		 */
		goto blunt_copy;
	}

	/*
	 * Proper alignment or identical mis-alignment at the beginning.
	 * Let's try and do a small unaligned copy first (if needed)
	 * and then an aligned copy for the rest.
	 */
	if (!vm_map_page_aligned(dst_addr, effective_page_mask)) {
		head_addr = dst_addr;
		head_size = (effective_page_size -
			     (copy->offset & effective_page_mask));
		head_size = MIN(head_size, copy->size);
	}
	if (!vm_map_page_aligned(copy->offset + copy->size,
				  effective_page_mask)) {
		/*
		 * Mis-alignment at the end.
		 * Do an aligned copy up to the last page and
		 * then an unaligned copy for the remaining bytes.
		 */
		tail_size = ((copy->offset + copy->size) &
			     effective_page_mask);
		tail_size = MIN(tail_size, copy->size);
		tail_addr = dst_addr + copy->size - tail_size;
		assert(tail_addr >= head_addr + head_size);
	}
	assert(head_size + tail_size <= copy->size);

	if (head_size + tail_size == copy->size) {
		/*
		 * It's all unaligned, no optimization possible...
		 */
		goto blunt_copy;
	}

	/*
	 * Can't optimize if there are any submaps in the
	 * destination due to the way we free the "copy" map
	 * progressively in vm_map_copy_overwrite_nested()
	 * in that case.
	 */
	vm_map_lock_read(dst_map);
	if (! vm_map_lookup_entry(dst_map, dst_addr, &entry)) {
		vm_map_unlock_read(dst_map);
		goto blunt_copy;
	}
	for (;
	     (entry != vm_map_copy_to_entry(copy) &&
	      entry->vme_start < dst_addr + copy->size);
	     entry = entry->vme_next) {
		if (entry->is_sub_map) {
			vm_map_unlock_read(dst_map);
			goto blunt_copy;
		}
	}
	vm_map_unlock_read(dst_map);

	if (head_size) {
		/*
		 * Unaligned copy of the first "head_size" bytes, to reach
		 * a page boundary.
		 */

		/*
		 * Extract "head_copy" out of "copy".
		 */
		head_copy = vm_map_copy_allocate();
		head_copy->type = VM_MAP_COPY_ENTRY_LIST;
		head_copy->cpy_hdr.entries_pageable =
			copy->cpy_hdr.entries_pageable;
		vm_map_store_init(&head_copy->cpy_hdr);

		entry = vm_map_copy_first_entry(copy);
		if (entry->vme_end < copy->offset + head_size) {
			head_size = entry->vme_end - copy->offset;
		}

		head_copy->offset = copy->offset;
		head_copy->size = head_size;
		copy->offset += head_size;
		copy->size -= head_size;

		vm_map_copy_clip_end(copy, entry, copy->offset);
		vm_map_copy_entry_unlink(copy, entry);
		vm_map_copy_entry_link(head_copy,
				       vm_map_copy_to_entry(head_copy),
				       entry);

		/*
		 * Do the unaligned copy.
		 */
		kr = vm_map_copy_overwrite_nested(dst_map,
						  head_addr,
						  head_copy,
						  interruptible,
						  (pmap_t) NULL,
						  FALSE);
		if (kr != KERN_SUCCESS)
			goto done;
	}

	if (tail_size) {
		/*
		 * Extract "tail_copy" out of "copy".
		 */
		tail_copy = vm_map_copy_allocate();
		tail_copy->type = VM_MAP_COPY_ENTRY_LIST;
		tail_copy->cpy_hdr.entries_pageable =
			copy->cpy_hdr.entries_pageable;
		vm_map_store_init(&tail_copy->cpy_hdr);

		tail_copy->offset = copy->offset + copy->size - tail_size;
		tail_copy->size = tail_size;

		copy->size -= tail_size;

		entry = vm_map_copy_last_entry(copy);
		vm_map_copy_clip_start(copy, entry, tail_copy->offset);
		entry = vm_map_copy_last_entry(copy);
		vm_map_copy_entry_unlink(copy, entry);
		vm_map_copy_entry_link(tail_copy,
				       vm_map_copy_last_entry(tail_copy),
				       entry);
	}

	/*
	 * Copy most (or possibly all) of the data.
	 */
	kr = vm_map_copy_overwrite_nested(dst_map,
					  dst_addr + head_size,
					  copy,
					  interruptible,
					  (pmap_t) NULL,
					  FALSE);
	if (kr != KERN_SUCCESS) {
		goto done;
	}

	if (tail_size) {
		kr = vm_map_copy_overwrite_nested(dst_map,
						  tail_addr,
						  tail_copy,
						  interruptible,
						  (pmap_t) NULL,
						  FALSE);
	}

done:
	assert(copy->type == VM_MAP_COPY_ENTRY_LIST);
	if (kr == KERN_SUCCESS) {
		/*
		 * Discard all the copy maps.
		 */
		if (head_copy) {
			vm_map_copy_discard(head_copy);
			head_copy = NULL;
		}
		vm_map_copy_discard(copy);
		if (tail_copy) {
			vm_map_copy_discard(tail_copy);
			tail_copy = NULL;
		}
	} else {
		/*
		 * Re-assemble the original copy map.
		 */
		if (head_copy) {
			entry = vm_map_copy_first_entry(head_copy);
			vm_map_copy_entry_unlink(head_copy, entry);
			vm_map_copy_entry_link(copy,
					       vm_map_copy_to_entry(copy),
					       entry);
			copy->offset -= head_size;
			copy->size += head_size;
			vm_map_copy_discard(head_copy);
			head_copy = NULL;
		}
		if (tail_copy) {
			entry = vm_map_copy_last_entry(tail_copy);
			vm_map_copy_entry_unlink(tail_copy, entry);
			vm_map_copy_entry_link(copy,
					       vm_map_copy_last_entry(copy),
					       entry);
			copy->size += tail_size;
			vm_map_copy_discard(tail_copy);
			tail_copy = NULL;
		}
	}
	return kr;
}