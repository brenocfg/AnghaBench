#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_63__   TYPE_5__ ;
typedef  struct TYPE_62__   TYPE_4__ ;
typedef  struct TYPE_61__   TYPE_3__ ;
typedef  struct TYPE_60__   TYPE_2__ ;
typedef  struct TYPE_59__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zone_t ;
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  TYPE_3__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_object_t ;
typedef  scalar_t__ vm_object_offset_t ;
typedef  TYPE_4__* vm_map_t ;
typedef  scalar_t__ vm_map_size_t ;
typedef  scalar_t__ vm_map_offset_t ;
typedef  TYPE_5__* vm_map_entry_t ;
typedef  TYPE_5__* vm_map_copy_t ;
typedef  scalar_t__ vm_map_address_t ;
typedef  int /*<<< orphan*/  vm_inherit_t ;
struct vm_object_fault_info {int /*<<< orphan*/  pmap_options; int /*<<< orphan*/  user_tag; } ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  event_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_60__ {scalar_t__ entries_pageable; } ;
struct TYPE_63__ {scalar_t__ size; scalar_t__ type; scalar_t__ offset; scalar_t__ vme_start; scalar_t__ vme_end; scalar_t__ wired_count; void* use_pmap; scalar_t__ is_sub_map; scalar_t__ iokit_acct; int /*<<< orphan*/  protection; int /*<<< orphan*/  behavior; int /*<<< orphan*/  max_protection; int /*<<< orphan*/  inheritance; void* map_aligned; struct TYPE_63__* vme_next; scalar_t__ from_reserved_zone; TYPE_2__ cpy_hdr; int /*<<< orphan*/  cpy_object; } ;
struct TYPE_59__ {scalar_t__ entries_pageable; } ;
struct TYPE_62__ {scalar_t__ disable_vmentry_reuse; scalar_t__ max_offset; scalar_t__ min_offset; int /*<<< orphan*/  size; int /*<<< orphan*/  pmap; TYPE_1__ hdr; scalar_t__ holelistenabled; int /*<<< orphan*/  holes_list; scalar_t__ wait_for_space; TYPE_5__* first_free; } ;
struct TYPE_61__ {scalar_t__ vmp_absent; } ;

/* Variables and functions */
 TYPE_5__* CAST_TO_VM_MAP_ENTRY (int /*<<< orphan*/ ) ; 
 int DBG_CACHE_HIT_FAULT ; 
 void* FALSE ; 
 scalar_t__ KERN_FAILURE ; 
 scalar_t__ KERN_NO_SPACE ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ PAGE_SIZE_64 ; 
 int /*<<< orphan*/  PMAP_OPTIONS_ALT_ACCT ; 
 int /*<<< orphan*/  SAVE_HINT_MAP_WRITE (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  THREAD_CONTINUE_NULL ; 
 int /*<<< orphan*/  THREAD_INTERRUPTIBLE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VME_ALIAS (TYPE_5__*) ; 
 int /*<<< orphan*/  VME_OBJECT (TYPE_5__*) ; 
 scalar_t__ VME_OFFSET (TYPE_5__*) ; 
 int /*<<< orphan*/  VM_BEHAVIOR_DEFAULT ; 
 int /*<<< orphan*/  VM_FLAGS_ANYWHERE ; 
 int /*<<< orphan*/  VM_INHERIT_DEFAULT ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_NONE ; 
 scalar_t__ VM_MAP_COPY_KERNEL_BUFFER ; 
 TYPE_5__* VM_MAP_COPY_NULL ; 
 scalar_t__ VM_MAP_COPY_OBJECT ; 
 int /*<<< orphan*/  VM_MAP_COPY_PAGE_MASK (TYPE_5__*) ; 
 int /*<<< orphan*/  VM_MAP_HIGHEST_ENTRY (TYPE_4__*,TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  VM_MAP_KERNEL_FLAGS_NONE ; 
 int VM_MAP_PAGE_ALIGNED (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_MAP_PAGE_MASK (TYPE_4__*) ; 
 scalar_t__ VM_MAP_PAGE_SHIFT (TYPE_4__*) ; 
 TYPE_3__* VM_PAGE_NULL ; 
 int /*<<< orphan*/  VM_PAGE_WIRED (TYPE_3__*) ; 
 int /*<<< orphan*/  VM_PROT_ALL ; 
 int /*<<< orphan*/  VM_PROT_DEFAULT ; 
 int /*<<< orphan*/  VM_PROT_EXECUTE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assert_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int first_free_is_valid (TYPE_4__*) ; 
 int /*<<< orphan*/  kasan_notify_address (scalar_t__,scalar_t__) ; 
 scalar_t__ override_nx (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 int /*<<< orphan*/  pmap_pageable (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  thread_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_fault_enter (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,struct vm_object_fault_info*,int /*<<< orphan*/ *,int*) ; 
 TYPE_5__* vm_map_copy_entry_create (TYPE_5__*,int) ; 
 int /*<<< orphan*/  vm_map_copy_entry_link (TYPE_5__*,TYPE_5__*,TYPE_5__*) ; 
 TYPE_5__* vm_map_copy_first_entry (TYPE_5__*) ; 
 int /*<<< orphan*/  vm_map_copy_insert (TYPE_4__*,TYPE_5__*,TYPE_5__*) ; 
 TYPE_5__* vm_map_copy_last_entry (TYPE_5__*) ; 
 int /*<<< orphan*/  vm_map_copy_remap (TYPE_4__*,TYPE_5__*,TYPE_5__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* vm_map_copy_to_entry (TYPE_5__*) ; 
 int /*<<< orphan*/  vm_map_copy_zone ; 
 scalar_t__ vm_map_copyout_kernel_buffer (TYPE_4__*,scalar_t__*,TYPE_5__*,scalar_t__,void*,scalar_t__) ; 
 scalar_t__ vm_map_enter (TYPE_4__*,scalar_t__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_entry_copy_full (TYPE_5__*,TYPE_5__*) ; 
 int /*<<< orphan*/  vm_map_entry_reserved_zone ; 
 int /*<<< orphan*/  vm_map_entry_zone ; 
 int /*<<< orphan*/  vm_map_lock (TYPE_4__*) ; 
 scalar_t__ vm_map_lookup_entry (TYPE_4__*,scalar_t__,TYPE_5__**) ; 
 scalar_t__ vm_map_min (TYPE_4__*) ; 
 scalar_t__ vm_map_round_page (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_store_copy_reset (TYPE_5__*,TYPE_5__*) ; 
 TYPE_5__* vm_map_to_entry (TYPE_4__*) ; 
 scalar_t__ vm_map_trunc_page (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_unlock (TYPE_4__*) ; 
 int /*<<< orphan*/  vm_object_lock (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_object_trunc_page (scalar_t__) ; 
 int /*<<< orphan*/  vm_object_unlock (int /*<<< orphan*/ ) ; 
 TYPE_3__* vm_page_lookup (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,TYPE_5__*) ; 

kern_return_t
vm_map_copyout_internal(
	vm_map_t		dst_map,
	vm_map_address_t	*dst_addr,	/* OUT */
	vm_map_copy_t		copy,
	vm_map_size_t		copy_size,
	boolean_t		consume_on_success,
	vm_prot_t		cur_protection,
	vm_prot_t		max_protection,
	vm_inherit_t		inheritance)
{
	vm_map_size_t		size;
	vm_map_size_t		adjustment;
	vm_map_offset_t		start;
	vm_object_offset_t	vm_copy_start;
	vm_map_entry_t		last;
	vm_map_entry_t		entry;
	vm_map_entry_t		hole_entry;

	/*
	 *	Check for null copy object.
	 */

	if (copy == VM_MAP_COPY_NULL) {
		*dst_addr = 0;
		return(KERN_SUCCESS);
	}

	if (copy->size != copy_size) {
		*dst_addr = 0;
		return KERN_FAILURE;
	}

	/*
	 *	Check for special copy object, created
	 *	by vm_map_copyin_object.
	 */

	if (copy->type == VM_MAP_COPY_OBJECT) {
		vm_object_t 		object = copy->cpy_object;
		kern_return_t 		kr;
		vm_object_offset_t	offset;

		offset = vm_object_trunc_page(copy->offset);
		size = vm_map_round_page((copy_size +
					  (vm_map_size_t)(copy->offset -
							  offset)),
					 VM_MAP_PAGE_MASK(dst_map));
		*dst_addr = 0;
		kr = vm_map_enter(dst_map, dst_addr, size,
				  (vm_map_offset_t) 0, VM_FLAGS_ANYWHERE,
				  VM_MAP_KERNEL_FLAGS_NONE,
				  VM_KERN_MEMORY_NONE,
				  object, offset, FALSE,
				  VM_PROT_DEFAULT, VM_PROT_ALL,
				  VM_INHERIT_DEFAULT);
		if (kr != KERN_SUCCESS)
			return(kr);
		/* Account for non-pagealigned copy object */
		*dst_addr += (vm_map_offset_t)(copy->offset - offset);
		if (consume_on_success)
			zfree(vm_map_copy_zone, copy);
		return(KERN_SUCCESS);
	}

	/*
	 *	Check for special kernel buffer allocated
	 *	by new_ipc_kmsg_copyin.
	 */

	if (copy->type == VM_MAP_COPY_KERNEL_BUFFER) {
		return vm_map_copyout_kernel_buffer(dst_map, dst_addr,
						    copy, copy_size, FALSE,
						    consume_on_success);
	}


	/*
	 *	Find space for the data
	 */

	vm_copy_start = vm_map_trunc_page((vm_map_size_t)copy->offset,
					  VM_MAP_COPY_PAGE_MASK(copy));
	size = vm_map_round_page((vm_map_size_t)copy->offset + copy_size,
				 VM_MAP_COPY_PAGE_MASK(copy))
		- vm_copy_start;


StartAgain: ;

	vm_map_lock(dst_map);
	if( dst_map->disable_vmentry_reuse == TRUE) {
		VM_MAP_HIGHEST_ENTRY(dst_map, entry, start);
		last = entry;
	} else {
		if (dst_map->holelistenabled) {
			hole_entry = CAST_TO_VM_MAP_ENTRY(dst_map->holes_list);

			if (hole_entry == NULL) {
				/*
				 * No more space in the map?
				 */
				vm_map_unlock(dst_map);
				return(KERN_NO_SPACE);
			}

			last = hole_entry;
			start = last->vme_start;
		} else {
			assert(first_free_is_valid(dst_map));
			start = ((last = dst_map->first_free) == vm_map_to_entry(dst_map)) ?
			vm_map_min(dst_map) : last->vme_end;
		}
		start = vm_map_round_page(start,
					  VM_MAP_PAGE_MASK(dst_map));
	}

	while (TRUE) {
		vm_map_entry_t	next = last->vme_next;
		vm_map_offset_t	end = start + size;

		if ((end > dst_map->max_offset) || (end < start)) {
			if (dst_map->wait_for_space) {
				if (size <= (dst_map->max_offset - dst_map->min_offset)) {
					assert_wait((event_t) dst_map,
						    THREAD_INTERRUPTIBLE);
					vm_map_unlock(dst_map);
					thread_block(THREAD_CONTINUE_NULL);
					goto StartAgain;
				}
			}
			vm_map_unlock(dst_map);
			return(KERN_NO_SPACE);
		}

		if (dst_map->holelistenabled) {
			if (last->vme_end >= end)
				break;
		} else {
			/*
			 *	If there are no more entries, we must win.
			 *
			 *	OR
			 *
			 *	If there is another entry, it must be
			 *	after the end of the potential new region.
			 */

			if (next == vm_map_to_entry(dst_map))
				break;

			if (next->vme_start >= end)
				break;
		}

		last = next;

		if (dst_map->holelistenabled) {
			if (last == CAST_TO_VM_MAP_ENTRY(dst_map->holes_list)) {
				/*
				 * Wrapped around
				 */
				vm_map_unlock(dst_map);
				return(KERN_NO_SPACE);
			}
			start = last->vme_start;
		} else {
			start = last->vme_end;
		}
		start = vm_map_round_page(start,
					  VM_MAP_PAGE_MASK(dst_map));
	}

	if (dst_map->holelistenabled) {
		if (vm_map_lookup_entry(dst_map, last->vme_start, &last)) {
			panic("Found an existing entry (%p) instead of potential hole at address: 0x%llx.\n", last, (unsigned long long)last->vme_start);
		}
	}


	adjustment = start - vm_copy_start;
	if (! consume_on_success) {
		/*
		 * We're not allowed to consume "copy", so we'll have to
		 * copy its map entries into the destination map below.
		 * No need to re-allocate map entries from the correct
		 * (pageable or not) zone, since we'll get new map entries
		 * during the transfer.
		 * We'll also adjust the map entries's "start" and "end"
		 * during the transfer, to keep "copy"'s entries consistent
		 * with its "offset".
		 */
		goto after_adjustments;
	}

	/*
	 *	Since we're going to just drop the map
	 *	entries from the copy into the destination
	 *	map, they must come from the same pool.
	 */

	if (copy->cpy_hdr.entries_pageable != dst_map->hdr.entries_pageable) {
		/*
		 * Mismatches occur when dealing with the default
		 * pager.
		 */
		zone_t		old_zone;
		vm_map_entry_t	next, new;

		/*
		 * Find the zone that the copies were allocated from
		 */

		entry = vm_map_copy_first_entry(copy);

		/*
		 * Reinitialize the copy so that vm_map_copy_entry_link
		 * will work.
		 */
		vm_map_store_copy_reset(copy, entry);
		copy->cpy_hdr.entries_pageable = dst_map->hdr.entries_pageable;

		/*
		 * Copy each entry.
		 */
		while (entry != vm_map_copy_to_entry(copy)) {
			new = vm_map_copy_entry_create(copy, !copy->cpy_hdr.entries_pageable);
			vm_map_entry_copy_full(new, entry);
			assert(!new->iokit_acct);
			if (new->is_sub_map) {
				/* clr address space specifics */
				new->use_pmap = FALSE;
			}
			vm_map_copy_entry_link(copy,
					       vm_map_copy_last_entry(copy),
					       new);
			next = entry->vme_next;
			old_zone = entry->from_reserved_zone ? vm_map_entry_reserved_zone : vm_map_entry_zone;
			zfree(old_zone, entry);
			entry = next;
		}
	}

	/*
	 *	Adjust the addresses in the copy chain, and
	 *	reset the region attributes.
	 */

	for (entry = vm_map_copy_first_entry(copy);
	     entry != vm_map_copy_to_entry(copy);
	     entry = entry->vme_next) {
		if (VM_MAP_PAGE_SHIFT(dst_map) == PAGE_SHIFT) {
			/*
			 * We're injecting this copy entry into a map that
			 * has the standard page alignment, so clear
			 * "map_aligned" (which might have been inherited
			 * from the original map entry).
			 */
			entry->map_aligned = FALSE;
		}

		entry->vme_start += adjustment;
		entry->vme_end += adjustment;

		if (entry->map_aligned) {
			assert(VM_MAP_PAGE_ALIGNED(entry->vme_start,
						   VM_MAP_PAGE_MASK(dst_map)));
			assert(VM_MAP_PAGE_ALIGNED(entry->vme_end,
						   VM_MAP_PAGE_MASK(dst_map)));
		}

		entry->inheritance = VM_INHERIT_DEFAULT;
		entry->protection = VM_PROT_DEFAULT;
		entry->max_protection = VM_PROT_ALL;
		entry->behavior = VM_BEHAVIOR_DEFAULT;

		/*
		 * If the entry is now wired,
		 * map the pages into the destination map.
		 */
		if (entry->wired_count != 0) {
			vm_map_offset_t va;
			vm_object_offset_t	 offset;
			vm_object_t object;
			vm_prot_t prot;
			int	type_of_fault;

			object = VME_OBJECT(entry);
			offset = VME_OFFSET(entry);
			va = entry->vme_start;

			pmap_pageable(dst_map->pmap,
				      entry->vme_start,
				      entry->vme_end,
				      TRUE);

			while (va < entry->vme_end) {
				vm_page_t	m;
				struct vm_object_fault_info fault_info = {};

				/*
				 * Look up the page in the object.
				 * Assert that the page will be found in the
				 * top object:
				 * either
				 *	the object was newly created by
				 *	vm_object_copy_slowly, and has
				 *	copies of all of the pages from
				 *	the source object
				 * or
				 *	the object was moved from the old
				 *	map entry; because the old map
				 *	entry was wired, all of the pages
				 *	were in the top-level object.
				 *	(XXX not true if we wire pages for
				 *	 reading)
				 */
				vm_object_lock(object);

				m = vm_page_lookup(object, offset);
				if (m == VM_PAGE_NULL || !VM_PAGE_WIRED(m) ||
				    m->vmp_absent)
					panic("vm_map_copyout: wiring %p", m);

				prot = entry->protection;

				if (override_nx(dst_map, VME_ALIAS(entry)) &&
				    prot)
				        prot |= VM_PROT_EXECUTE;

				type_of_fault = DBG_CACHE_HIT_FAULT;

				fault_info.user_tag = VME_ALIAS(entry);
				fault_info.pmap_options = 0;
				if (entry->iokit_acct ||
				    (!entry->is_sub_map && !entry->use_pmap)) {
					fault_info.pmap_options |= PMAP_OPTIONS_ALT_ACCT;
				}

				vm_fault_enter(m,
					       dst_map->pmap,
					       va,
					       prot,
					       prot,
					       VM_PAGE_WIRED(m),
					       FALSE, /* change_wiring */
					       VM_KERN_MEMORY_NONE, /* tag - not wiring */
					       &fault_info,
					       NULL,  /* need_retry */
					       &type_of_fault);

				vm_object_unlock(object);

				offset += PAGE_SIZE_64;
				va += PAGE_SIZE;
			}
		}
	}

after_adjustments:

	/*
	 *	Correct the page alignment for the result
	 */

	*dst_addr = start + (copy->offset - vm_copy_start);

#if KASAN
	kasan_notify_address(*dst_addr, size);
#endif

	/*
	 *	Update the hints and the map size
	 */

	if (consume_on_success) {
		SAVE_HINT_MAP_WRITE(dst_map, vm_map_copy_last_entry(copy));
	} else {
		SAVE_HINT_MAP_WRITE(dst_map, last);
	}

	dst_map->size += size;

	/*
	 *	Link in the copy
	 */

	if (consume_on_success) {
		vm_map_copy_insert(dst_map, last, copy);
	} else {
		vm_map_copy_remap(dst_map, last, copy, adjustment,
				  cur_protection, max_protection,
				  inheritance);
	}

	vm_map_unlock(dst_map);

	/*
	 * XXX	If wiring_required, call vm_map_pageable
	 */

	return(KERN_SUCCESS);
}