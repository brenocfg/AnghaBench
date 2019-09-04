#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_48__   TYPE_3__ ;
typedef  struct TYPE_47__   TYPE_31__ ;
typedef  struct TYPE_46__   TYPE_2__ ;
typedef  struct TYPE_45__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_tag_t ;
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int vm_prot_t ;
typedef  TYPE_1__* vm_object_t ;
typedef  scalar_t__ vm_object_size_t ;
typedef  scalar_t__ vm_object_offset_t ;
typedef  int /*<<< orphan*/  vm_map_version_t ;
typedef  TYPE_2__* vm_map_t ;
typedef  scalar_t__ vm_map_offset_t ;
typedef  TYPE_3__* vm_map_entry_t ;
typedef  scalar_t__ vm_map_address_t ;
typedef  int /*<<< orphan*/  upl_t ;
typedef  scalar_t__ upl_size_t ;
typedef  int /*<<< orphan*/  upl_page_info_array_t ;
typedef  int upl_control_flags_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_48__ {scalar_t__ vme_end; scalar_t__ vme_start; int use_pmap; int protection; scalar_t__ wired_count; scalar_t__ is_sub_map; void* needs_copy; scalar_t__ is_shared; } ;
struct TYPE_47__ {int create_upl_extra_cow_pages; int /*<<< orphan*/  create_upl_lookup_failure_copy; int /*<<< orphan*/  create_upl_lookup_failure_write; int /*<<< orphan*/  create_upl_extra_cow; } ;
struct TYPE_46__ {scalar_t__ pmap; scalar_t__ mapped_in_other_pmaps; } ;
struct TYPE_45__ {scalar_t__ vo_size; scalar_t__ copy_strategy; int ref_count; void* true_share; scalar_t__ phys_contiguous; scalar_t__ private; scalar_t__ vo_shadow_offset; struct TYPE_45__* shadow; scalar_t__ copy; scalar_t__ internal; } ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ KERN_FAILURE ; 
 scalar_t__ KERN_INVALID_ARGUMENT ; 
 scalar_t__ KERN_INVALID_VALUE ; 
 scalar_t__ KERN_PROTECTION_FAILURE ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ MAX_UPL_SIZE_BYTES ; 
 scalar_t__ MEMORY_OBJECT_COPY_DELAY ; 
 scalar_t__ MEMORY_OBJECT_COPY_SYMMETRIC ; 
 int /*<<< orphan*/  MEMORY_OBJECT_DATA_SYNC ; 
 int /*<<< orphan*/  OBJECT_LOCK_EXCLUSIVE ; 
 int PAGE_SIZE ; 
 scalar_t__ PMAP_NULL ; 
 void* TRUE ; 
 int UPL_COPYOUT_FROM ; 
 int UPL_DEV_MEMORY ; 
 int UPL_FORCE_DATA_SYNC ; 
 int UPL_PHYS_CONTIG ; 
 int UPL_QUERY_OBJECT_TYPE ; 
 int UPL_VALID_FLAGS ; 
 int /*<<< orphan*/  VME_ALIAS (TYPE_3__*) ; 
 TYPE_1__* VME_OBJECT (TYPE_3__*) ; 
 int /*<<< orphan*/  VME_OBJECT_SET (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ VME_OFFSET (TYPE_3__*) ; 
 int /*<<< orphan*/  VME_OFFSET_SET (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* VME_SUBMAP (TYPE_3__*) ; 
 int /*<<< orphan*/  VM_MAP_PAGE_MASK (TYPE_2__*) ; 
 TYPE_1__* VM_OBJECT_NULL ; 
 int VM_PROT_COPY ; 
 int VM_PROT_EXECUTE ; 
 int /*<<< orphan*/  VM_PROT_NO_CHANGE ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* compressor_object ; 
 TYPE_1__* kernel_object ; 
 scalar_t__ kernel_pmap ; 
 scalar_t__ override_nx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int page_aligned (scalar_t__) ; 
 TYPE_31__ vm_counters ; 
 int /*<<< orphan*/  vm_map_clip_end (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_clip_start (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_deallocate (TYPE_2__*) ; 
 scalar_t__ vm_map_entry_should_cow_for_true_share (TYPE_3__*) ; 
 int /*<<< orphan*/  vm_map_lock_assert_exclusive (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_lock_read (TYPE_2__*) ; 
 scalar_t__ vm_map_lock_read_to_write (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_lock_write_to_read (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_lookup_entry (TYPE_2__*,scalar_t__,TYPE_3__**) ; 
 scalar_t__ vm_map_lookup_locked (TYPE_2__**,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__**,scalar_t__*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__**) ; 
 int /*<<< orphan*/  vm_map_reference (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_round_page (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_trunc_page (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_unlock_read (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_allocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_deallocate (TYPE_1__*) ; 
 scalar_t__ vm_object_iopl_request (TYPE_1__*,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_lock_request (TYPE_1__*,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_pmap_protect (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  vm_object_reference (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_reference_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_unlock (TYPE_1__*) ; 

kern_return_t
vm_map_create_upl(
	vm_map_t		map,
	vm_map_address_t	offset,
	upl_size_t		*upl_size,
	upl_t			*upl,
	upl_page_info_array_t	page_list,
	unsigned int		*count,
	upl_control_flags_t	*flags,
	vm_tag_t		tag)
{
	vm_map_entry_t		entry;
	upl_control_flags_t	caller_flags;
	int			force_data_sync;
	int			sync_cow_data;
	vm_object_t		local_object;
	vm_map_offset_t		local_offset;
	vm_map_offset_t		local_start;
	kern_return_t		ret;

	assert(page_aligned(offset));

	caller_flags = *flags;

	if (caller_flags & ~UPL_VALID_FLAGS) {
		/*
		 * For forward compatibility's sake,
		 * reject any unknown flag.
		 */
		return KERN_INVALID_VALUE;
	}
	force_data_sync = (caller_flags & UPL_FORCE_DATA_SYNC);
	sync_cow_data = !(caller_flags & UPL_COPYOUT_FROM);

	if (upl == NULL)
		return KERN_INVALID_ARGUMENT;

REDISCOVER_ENTRY:
	vm_map_lock_read(map);

	if (!vm_map_lookup_entry(map, offset, &entry)) {
		vm_map_unlock_read(map);
		return KERN_FAILURE;
	}

	if ((entry->vme_end - offset) < *upl_size) {
		*upl_size = (upl_size_t) (entry->vme_end - offset);
		assert(*upl_size == entry->vme_end - offset);
	}

	if (caller_flags & UPL_QUERY_OBJECT_TYPE) {
		*flags = 0;

		if (!entry->is_sub_map &&
		    VME_OBJECT(entry) != VM_OBJECT_NULL) {
			if (VME_OBJECT(entry)->private)
				*flags = UPL_DEV_MEMORY;

			if (VME_OBJECT(entry)->phys_contiguous)
				*flags |= UPL_PHYS_CONTIG;
		}
		vm_map_unlock_read(map);
		return KERN_SUCCESS;
	}

	if (VME_OBJECT(entry) == VM_OBJECT_NULL ||
	    !VME_OBJECT(entry)->phys_contiguous) {
		if (*upl_size > MAX_UPL_SIZE_BYTES)
			*upl_size = MAX_UPL_SIZE_BYTES;
	}

	/*
	 *      Create an object if necessary.
	 */
	if (VME_OBJECT(entry) == VM_OBJECT_NULL) {

		if (vm_map_lock_read_to_write(map))
			goto REDISCOVER_ENTRY;

		VME_OBJECT_SET(entry,
			       vm_object_allocate((vm_size_t)
						  (entry->vme_end -
						   entry->vme_start)));
		VME_OFFSET_SET(entry, 0);
		assert(entry->use_pmap);

		vm_map_lock_write_to_read(map);
	}

	if (!(caller_flags & UPL_COPYOUT_FROM) &&
	    !entry->is_sub_map &&
	    !(entry->protection & VM_PROT_WRITE)) {
		vm_map_unlock_read(map);
		return KERN_PROTECTION_FAILURE;
	}

#if CONFIG_EMBEDDED
	if (map->pmap != kernel_pmap &&
	    (caller_flags & UPL_COPYOUT_FROM) &&
	    (entry->protection & VM_PROT_EXECUTE) &&
	    !(entry->protection & VM_PROT_WRITE)) {
		vm_offset_t	kaddr;
		vm_size_t	ksize;

		/*
		 * We're about to create a read-only UPL backed by
		 * memory from an executable mapping.
		 * Wiring the pages would result in the pages being copied
		 * (due to the "MAP_PRIVATE" mapping) and no longer
		 * code-signed, so no longer eligible for execution.
		 * Instead, let's copy the data into a kernel buffer and
		 * create the UPL from this kernel buffer.
		 * The kernel buffer is then freed, leaving the UPL holding
		 * the last reference on the VM object, so the memory will
		 * be released when the UPL is committed.
		 */

		vm_map_unlock_read(map);
		/* allocate kernel buffer */
		ksize = round_page(*upl_size);
		kaddr = 0;
		ret = kmem_alloc_pageable(kernel_map,
					  &kaddr,
					  ksize,
					  tag);
		if (ret == KERN_SUCCESS) {
			/* copyin the user data */
			assert(page_aligned(offset));
			ret = copyinmap(map, offset, (void *)kaddr, *upl_size);
		}
		if (ret == KERN_SUCCESS) {
			if (ksize > *upl_size) {
				/* zero out the extra space in kernel buffer */
				memset((void *)(kaddr + *upl_size),
				       0,
				       ksize - *upl_size);
			}
			/* create the UPL from the kernel buffer */
			ret = vm_map_create_upl(kernel_map, kaddr, upl_size,
						upl, page_list, count, flags, tag);
		}
		if (kaddr != 0) {
			/* free the kernel buffer */
			kmem_free(kernel_map, kaddr, ksize);
			kaddr = 0;
			ksize = 0;
		}
#if DEVELOPMENT || DEBUG
		DTRACE_VM4(create_upl_from_executable,
			   vm_map_t, map,
			   vm_map_address_t, offset,
			   upl_size_t, *upl_size,
			   kern_return_t, ret);
#endif /* DEVELOPMENT || DEBUG */
		return ret;
	}
#endif /* CONFIG_EMBEDDED */

	local_object = VME_OBJECT(entry);
	assert(local_object != VM_OBJECT_NULL);

	if (!entry->is_sub_map &&
	    !entry->needs_copy &&
	    *upl_size != 0 &&
	    local_object->vo_size > *upl_size && /* partial UPL */
	    entry->wired_count == 0 && /* No COW for entries that are wired */
	    (map->pmap != kernel_pmap) && /* alias checks */
	    (vm_map_entry_should_cow_for_true_share(entry) /* case 1 */
	     ||
	     (/* case 2 */
	      local_object->internal &&
	      (local_object->copy_strategy == MEMORY_OBJECT_COPY_SYMMETRIC) &&
	      local_object->ref_count > 1))) {
		vm_prot_t	prot;

		/*
		 * Case 1:
		 * Set up the targeted range for copy-on-write to avoid
		 * applying true_share/copy_delay to the entire object.
		 *
		 * Case 2:
		 * This map entry covers only part of an internal
		 * object.  There could be other map entries covering
		 * other areas of this object and some of these map
		 * entries could be marked as "needs_copy", which
		 * assumes that the object is COPY_SYMMETRIC.
		 * To avoid marking this object as COPY_DELAY and
		 * "true_share", let's shadow it and mark the new
		 * (smaller) object as "true_share" and COPY_DELAY.
		 */

		if (vm_map_lock_read_to_write(map)) {
			goto REDISCOVER_ENTRY;
		}
		vm_map_lock_assert_exclusive(map);
		assert(VME_OBJECT(entry) == local_object);

		vm_map_clip_start(map,
				  entry,
				  vm_map_trunc_page(offset,
						    VM_MAP_PAGE_MASK(map)));
		vm_map_clip_end(map,
				entry,
				vm_map_round_page(offset + *upl_size,
						  VM_MAP_PAGE_MASK(map)));
		if ((entry->vme_end - offset) < *upl_size) {
			*upl_size = (upl_size_t) (entry->vme_end - offset);
			assert(*upl_size == entry->vme_end - offset);
		}

		prot = entry->protection & ~VM_PROT_WRITE;
		if (override_nx(map, VME_ALIAS(entry)) && prot)
			prot |= VM_PROT_EXECUTE;
		vm_object_pmap_protect(local_object,
				       VME_OFFSET(entry),
				       entry->vme_end - entry->vme_start,
				       ((entry->is_shared ||
					 map->mapped_in_other_pmaps)
					? PMAP_NULL
					: map->pmap),
				       entry->vme_start,
				       prot);

		assert(entry->wired_count == 0);

		/*
		 * Lock the VM object and re-check its status: if it's mapped
		 * in another address space, we could still be racing with
		 * another thread holding that other VM map exclusively.
		 */
		vm_object_lock(local_object);
		if (local_object->true_share) {
			/* object is already in proper state: no COW needed */
			assert(local_object->copy_strategy !=
			       MEMORY_OBJECT_COPY_SYMMETRIC);
		} else {
			/* not true_share: ask for copy-on-write below */
			assert(local_object->copy_strategy ==
			       MEMORY_OBJECT_COPY_SYMMETRIC);
			entry->needs_copy = TRUE;
		}
		vm_object_unlock(local_object);

		vm_map_lock_write_to_read(map);
	}

	if (entry->needs_copy)  {
		/*
		 * Honor copy-on-write for COPY_SYMMETRIC
		 * strategy.
		 */
		vm_map_t		local_map;
		vm_object_t		object;
		vm_object_offset_t	new_offset;
		vm_prot_t		prot;
		boolean_t		wired;
		vm_map_version_t	version;
		vm_map_t		real_map;
		vm_prot_t		fault_type;

		local_map = map;

		if (caller_flags & UPL_COPYOUT_FROM) {
			fault_type = VM_PROT_READ | VM_PROT_COPY;
			vm_counters.create_upl_extra_cow++;
			vm_counters.create_upl_extra_cow_pages +=
				(entry->vme_end - entry->vme_start) / PAGE_SIZE;
		} else {
			fault_type = VM_PROT_WRITE;
		}
		if (vm_map_lookup_locked(&local_map,
					 offset, fault_type,
					 OBJECT_LOCK_EXCLUSIVE,
					 &version, &object,
					 &new_offset, &prot, &wired,
					 NULL,
					 &real_map) != KERN_SUCCESS) {
			if (fault_type == VM_PROT_WRITE) {
				vm_counters.create_upl_lookup_failure_write++;
			} else {
				vm_counters.create_upl_lookup_failure_copy++;
			}
			vm_map_unlock_read(local_map);
			return KERN_FAILURE;
		}
		if (real_map != map)
			vm_map_unlock(real_map);
		vm_map_unlock_read(local_map);

		vm_object_unlock(object);

		goto REDISCOVER_ENTRY;
	}

	if (entry->is_sub_map) {
		vm_map_t	submap;

		submap = VME_SUBMAP(entry);
		local_start = entry->vme_start;
		local_offset = VME_OFFSET(entry);

		vm_map_reference(submap);
		vm_map_unlock_read(map);

		ret = vm_map_create_upl(submap,
					local_offset + (offset - local_start),
					upl_size, upl, page_list, count, flags, tag);
		vm_map_deallocate(submap);

		return ret;
	}

	if (sync_cow_data &&
	    (VME_OBJECT(entry)->shadow ||
	     VME_OBJECT(entry)->copy)) {
		local_object = VME_OBJECT(entry);
		local_start = entry->vme_start;
		local_offset = VME_OFFSET(entry);

		vm_object_reference(local_object);
		vm_map_unlock_read(map);

		if (local_object->shadow && local_object->copy) {
			vm_object_lock_request(local_object->shadow,
					       ((vm_object_offset_t)
						((offset - local_start) +
						 local_offset) +
						local_object->vo_shadow_offset),
					       *upl_size, FALSE,
					       MEMORY_OBJECT_DATA_SYNC,
					       VM_PROT_NO_CHANGE);
		}
		sync_cow_data = FALSE;
		vm_object_deallocate(local_object);

		goto REDISCOVER_ENTRY;
	}
	if (force_data_sync) {
		local_object = VME_OBJECT(entry);
		local_start = entry->vme_start;
		local_offset = VME_OFFSET(entry);

		vm_object_reference(local_object);
		vm_map_unlock_read(map);

		vm_object_lock_request(local_object,
				       ((vm_object_offset_t)
					((offset - local_start) +
					 local_offset)),
				       (vm_object_size_t)*upl_size,
				       FALSE,
				       MEMORY_OBJECT_DATA_SYNC,
				       VM_PROT_NO_CHANGE);

		force_data_sync = FALSE;
		vm_object_deallocate(local_object);

		goto REDISCOVER_ENTRY;
	}
	if (VME_OBJECT(entry)->private)
		*flags = UPL_DEV_MEMORY;
	else
		*flags = 0;

	if (VME_OBJECT(entry)->phys_contiguous)
		*flags |= UPL_PHYS_CONTIG;

	local_object = VME_OBJECT(entry);
	local_offset = VME_OFFSET(entry);
	local_start = entry->vme_start;

#if CONFIG_EMBEDDED
	/*
	 * Wiring will copy the pages to the shadow object.
	 * The shadow object will not be code-signed so
	 * attempting to execute code from these copied pages
	 * would trigger a code-signing violation.
	 */
	if (entry->protection & VM_PROT_EXECUTE) {
#if MACH_ASSERT
		printf("pid %d[%s] create_upl out of executable range from "
		       "0x%llx to 0x%llx: side effects may include "
		       "code-signing violations later on\n",
		       proc_selfpid(),
		       (current_task()->bsd_info
			? proc_name_address(current_task()->bsd_info)
			: "?"),
		       (uint64_t) entry->vme_start,
		       (uint64_t) entry->vme_end);
#endif /* MACH_ASSERT */
		DTRACE_VM2(cs_executable_create_upl,
			   uint64_t, (uint64_t)entry->vme_start,
			   uint64_t, (uint64_t)entry->vme_end);
		cs_executable_create_upl++;
	}
#endif /* CONFIG_EMBEDDED */

	vm_object_lock(local_object);

	/*
	 * Ensure that this object is "true_share" and "copy_delay" now,
	 * while we're still holding the VM map lock.  After we unlock the map,
	 * anything could happen to that mapping, including some copy-on-write
	 * activity.  We need to make sure that the IOPL will point at the
	 * same memory as the mapping.
	 */
	if (local_object->true_share) {
		assert(local_object->copy_strategy !=
		       MEMORY_OBJECT_COPY_SYMMETRIC);
	} else if (local_object != kernel_object &&
		   local_object != compressor_object &&
		   !local_object->phys_contiguous) {
#if VM_OBJECT_TRACKING_OP_TRUESHARE
		if (!local_object->true_share &&
		    vm_object_tracking_inited) {
			void *bt[VM_OBJECT_TRACKING_BTDEPTH];
			int num = 0;
			num = OSBacktrace(bt,
					  VM_OBJECT_TRACKING_BTDEPTH);
			btlog_add_entry(vm_object_tracking_btlog,
					local_object,
					VM_OBJECT_TRACKING_OP_TRUESHARE,
					bt,
					num);
		}
#endif /* VM_OBJECT_TRACKING_OP_TRUESHARE */
		local_object->true_share = TRUE;
		if (local_object->copy_strategy ==
		    MEMORY_OBJECT_COPY_SYMMETRIC) {
			local_object->copy_strategy = MEMORY_OBJECT_COPY_DELAY;
		}
	}

	vm_object_reference_locked(local_object);
	vm_object_unlock(local_object);

	vm_map_unlock_read(map);

	ret = vm_object_iopl_request(local_object,
				     ((vm_object_offset_t)
				      ((offset - local_start) + local_offset)),
				     *upl_size,
				     upl,
				     page_list,
				     count,
				     caller_flags,
				     tag);
	vm_object_deallocate(local_object);

	return ret;
}