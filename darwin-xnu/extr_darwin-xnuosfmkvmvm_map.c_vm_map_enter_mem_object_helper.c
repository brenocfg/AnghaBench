#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_65__   TYPE_8__ ;
typedef  struct TYPE_64__   TYPE_7__ ;
typedef  struct TYPE_63__   TYPE_6__ ;
typedef  struct TYPE_62__   TYPE_5__ ;
typedef  struct TYPE_61__   TYPE_4__ ;
typedef  struct TYPE_60__   TYPE_3__ ;
typedef  struct TYPE_59__   TYPE_2__ ;
typedef  struct TYPE_58__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_tag_t ;
typedef  int vm_prot_t ;
typedef  TYPE_2__* vm_object_t ;
typedef  scalar_t__ vm_object_size_t ;
typedef  scalar_t__ vm_object_offset_t ;
typedef  TYPE_3__* vm_named_entry_t ;
typedef  TYPE_4__* vm_map_t ;
typedef  scalar_t__ vm_map_size_t ;
typedef  int vm_map_offset_t ;
struct TYPE_62__ {scalar_t__ __vmkf_unused; int vmkf_keep_map_locked; void* vmkf_map_jit; void* vmkf_submap; } ;
typedef  TYPE_5__ vm_map_kernel_flags_t ;
typedef  TYPE_6__* vm_map_entry_t ;
typedef  TYPE_7__* vm_map_copy_t ;
typedef  int vm_map_address_t ;
typedef  scalar_t__ vm_inherit_t ;
typedef  int /*<<< orphan*/  upl_page_list_ptr_t ;
typedef  scalar_t__ memory_object_t ;
typedef  int mach_vm_address_t ;
typedef  scalar_t__ kern_return_t ;
typedef  TYPE_8__* ipc_port_t ;
typedef  int boolean_t ;
struct TYPE_65__ {scalar_t__ ip_kobject; } ;
struct TYPE_64__ {scalar_t__ type; } ;
struct TYPE_63__ {scalar_t__ vme_end; scalar_t__ vme_start; int needs_copy; int protection; scalar_t__ is_sub_map; scalar_t__ used_for_jit; void* is_shared; struct TYPE_63__* vme_next; } ;
struct TYPE_61__ {int mapped_in_other_pmaps; int /*<<< orphan*/  pmap; } ;
struct TYPE_58__ {TYPE_2__* object; TYPE_7__* copy; TYPE_4__* map; } ;
struct TYPE_60__ {scalar_t__ data_offset; scalar_t__ size; int protection; scalar_t__ offset; TYPE_1__ backing; scalar_t__ is_copy; scalar_t__ is_sub_map; } ;
struct TYPE_59__ {scalar_t__ vo_size; scalar_t__ copy_strategy; unsigned int wimg_bits; int pager_ready; scalar_t__ pager; scalar_t__ internal; scalar_t__ named; void* true_share; scalar_t__ shadowed; } ;

/* Variables and functions */
 int FALSE ; 
 unsigned int GET_MAP_MEM (int) ; 
 scalar_t__ IKOT_MEMORY_OBJECT ; 
 scalar_t__ IKOT_NAMED_ENTRY ; 
 int /*<<< orphan*/  IP_VALID (TYPE_8__*) ; 
 scalar_t__ KERN_INVALID_ARGUMENT ; 
 scalar_t__ KERN_INVALID_OBJECT ; 
 scalar_t__ KERN_INVALID_RIGHT ; 
 scalar_t__ KERN_MEMORY_ERROR ; 
 scalar_t__ KERN_MEMORY_RESTART_COPY ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ MEMORY_OBJECT_COPY_DELAY ; 
 scalar_t__ MEMORY_OBJECT_COPY_NONE ; 
 scalar_t__ MEMORY_OBJECT_COPY_SYMMETRIC ; 
 scalar_t__ MEMORY_OBJECT_NULL ; 
 int /*<<< orphan*/  OSIncrementAtomic64 (int /*<<< orphan*/ *) ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ PMAP_NULL ; 
 int PMAP_OPTIONS_INTERNAL ; 
 int PMAP_OPTIONS_NOWAIT ; 
 int /*<<< orphan*/  THREAD_UNINT ; 
 void* TRUE ; 
 int /*<<< orphan*/  UPL_PHYS_PAGE (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  UPL_VALID_PAGE (int /*<<< orphan*/ ,unsigned int) ; 
 int VME_ALIAS (TYPE_6__*) ; 
 TYPE_2__* VME_OBJECT (TYPE_6__*) ; 
 int /*<<< orphan*/  VME_OBJECT_SHADOW (TYPE_6__*,scalar_t__) ; 
 scalar_t__ VME_OFFSET (TYPE_6__*) ; 
 TYPE_4__* VME_SUBMAP (TYPE_6__*) ; 
 int VM_FLAGS_ALIAS_MASK ; 
 int VM_FLAGS_ANYWHERE ; 
 int VM_FLAGS_FIXED ; 
 int VM_FLAGS_OVERWRITE ; 
 int VM_FLAGS_RETURN_4K_DATA_ADDR ; 
 int VM_FLAGS_RETURN_DATA_ADDR ; 
 int /*<<< orphan*/  VM_GET_FLAGS_ALIAS (int,int) ; 
 scalar_t__ VM_INHERIT_LAST_VALID ; 
 scalar_t__ VM_MAP_COPY_ENTRY_LIST ; 
 TYPE_5__ VM_MAP_KERNEL_FLAGS_NONE ; 
 TYPE_4__* VM_MAP_NULL ; 
 int /*<<< orphan*/  VM_MAP_PAGE_ALIGNED (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_MAP_PAGE_MASK (TYPE_4__*) ; 
 int /*<<< orphan*/  VM_MAP_REMOVE_NO_FLAGS ; 
 int /*<<< orphan*/  VM_OBJECT_EVENT_PAGER_READY ; 
 TYPE_2__* VM_OBJECT_NULL ; 
 int VM_PROT_ALL ; 
 int VM_PROT_IS_MASK ; 
 int /*<<< orphan*/  VM_PROT_NONE ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assertf (int,char*,...) ; 
 scalar_t__ ip_kotype (TYPE_8__*) ; 
 TYPE_2__* kernel_object ; 
 scalar_t__ memory_object_map (scalar_t__,int) ; 
 TYPE_2__* memory_object_to_vm_object (scalar_t__) ; 
 int /*<<< orphan*/  named_entry_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  named_entry_unlock (TYPE_3__*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ pmap_enter_options (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  vm_deallocate (TYPE_4__*,int,scalar_t__) ; 
 scalar_t__ vm_kernel_map_is_kernel (TYPE_4__*) ; 
 TYPE_6__* vm_map_copy_first_entry (TYPE_7__*) ; 
 TYPE_6__* vm_map_copy_to_entry (TYPE_7__*) ; 
 int /*<<< orphan*/  vm_map_deallocate (TYPE_4__*) ; 
 scalar_t__ vm_map_enter (TYPE_4__*,int*,scalar_t__,int,int,TYPE_5__,int,TYPE_2__*,scalar_t__,int,int,int,scalar_t__) ; 
 int /*<<< orphan*/  vm_map_lock (TYPE_4__*) ; 
 scalar_t__ vm_map_pmap (TYPE_4__*) ; 
 int /*<<< orphan*/  vm_map_reference (TYPE_4__*) ; 
 int /*<<< orphan*/  vm_map_remove (TYPE_4__*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_round_page (scalar_t__,int /*<<< orphan*/ ) ; 
 int vm_map_trunc_page (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_unlock (TYPE_4__*) ; 
 int /*<<< orphan*/  vm_object_change_wimg_mode (TYPE_2__*,unsigned int) ; 
 int vm_object_copy_quickly (TYPE_2__**,scalar_t__,scalar_t__,int*,int*) ; 
 scalar_t__ vm_object_copy_strategically (TYPE_2__*,scalar_t__,scalar_t__,TYPE_2__**,scalar_t__*,int*) ; 
 int /*<<< orphan*/  vm_object_deallocate (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_mapping_begin (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_mapping_end (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_mapping_wait (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_pmap_protect (TYPE_2__*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_object_reference (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_reference_locked (TYPE_2__*) ; 
 scalar_t__ vm_object_round_page (scalar_t__) ; 
 scalar_t__ vm_object_trunc_page (scalar_t__) ; 
 int /*<<< orphan*/  vm_object_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_wait (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_prefault_nb_bailout ; 
 int /*<<< orphan*/  vm_prefault_nb_pages ; 
 int /*<<< orphan*/  vm_prot_to_wimg (unsigned int,unsigned int*) ; 

__attribute__((used)) static kern_return_t
vm_map_enter_mem_object_helper(
	vm_map_t		target_map,
	vm_map_offset_t		*address,
	vm_map_size_t		initial_size,
	vm_map_offset_t		mask,
	int			flags,
	vm_map_kernel_flags_t	vmk_flags,
	vm_tag_t		tag,
	ipc_port_t		port,
	vm_object_offset_t	offset,
	boolean_t		copy,
	vm_prot_t		cur_protection,
	vm_prot_t		max_protection,
	vm_inherit_t		inheritance,
	upl_page_list_ptr_t	page_list,
	unsigned int		page_list_count)
{
	vm_map_address_t	map_addr;
	vm_map_size_t		map_size;
	vm_object_t		object;
	vm_object_size_t	size;
	kern_return_t		result;
	boolean_t		mask_cur_protection, mask_max_protection;
	boolean_t		kernel_prefault, try_prefault = (page_list_count != 0);
	vm_map_offset_t		offset_in_mapping = 0;
#if __arm64__
	boolean_t		fourk = vmk_flags.vmkf_fourk;
#endif /* __arm64__ */

	assertf(vmk_flags.__vmkf_unused == 0, "vmk_flags unused=0x%x\n", vmk_flags.__vmkf_unused);

	mask_cur_protection = cur_protection & VM_PROT_IS_MASK;
	mask_max_protection = max_protection & VM_PROT_IS_MASK;
	cur_protection &= ~VM_PROT_IS_MASK;
	max_protection &= ~VM_PROT_IS_MASK;

	/*
	 * Check arguments for validity
	 */
	if ((target_map == VM_MAP_NULL) ||
	    (cur_protection & ~VM_PROT_ALL) ||
	    (max_protection & ~VM_PROT_ALL) ||
	    (inheritance > VM_INHERIT_LAST_VALID) ||
	    (try_prefault && (copy || !page_list)) ||
	    initial_size == 0) {
		return KERN_INVALID_ARGUMENT;
	}

#if __arm64__
	if (fourk) {
		map_addr = vm_map_trunc_page(*address, FOURK_PAGE_MASK);
		map_size = vm_map_round_page(initial_size, FOURK_PAGE_MASK);
	} else
#endif /* __arm64__ */
	{
		map_addr = vm_map_trunc_page(*address,
					     VM_MAP_PAGE_MASK(target_map));
		map_size = vm_map_round_page(initial_size,
					     VM_MAP_PAGE_MASK(target_map));
	}
	size = vm_object_round_page(initial_size);

	/*
	 * Find the vm object (if any) corresponding to this port.
	 */
	if (!IP_VALID(port)) {
		object = VM_OBJECT_NULL;
		offset = 0;
		copy = FALSE;
	} else if (ip_kotype(port) == IKOT_NAMED_ENTRY) {
		vm_named_entry_t	named_entry;

		named_entry = (vm_named_entry_t) port->ip_kobject;

		if (flags & (VM_FLAGS_RETURN_DATA_ADDR |
			     VM_FLAGS_RETURN_4K_DATA_ADDR)) {
			offset += named_entry->data_offset;
		}

		/* a few checks to make sure user is obeying rules */
		if (size == 0) {
			if (offset >= named_entry->size)
				return KERN_INVALID_RIGHT;
			size = named_entry->size - offset;
		}
		if (mask_max_protection) {
			max_protection &= named_entry->protection;
		}
		if (mask_cur_protection) {
			cur_protection &= named_entry->protection;
		}
		if ((named_entry->protection & max_protection) !=
		    max_protection)
			return KERN_INVALID_RIGHT;
		if ((named_entry->protection & cur_protection) !=
		    cur_protection)
			return KERN_INVALID_RIGHT;
		if (offset + size < offset) {
			/* overflow */
			return KERN_INVALID_ARGUMENT;
		}
		if (named_entry->size < (offset + initial_size)) {
			return KERN_INVALID_ARGUMENT;
		}

		if (named_entry->is_copy) {
			/* for a vm_map_copy, we can only map it whole */
			if ((size != named_entry->size) &&
			    (vm_map_round_page(size,
					       VM_MAP_PAGE_MASK(target_map)) ==
			     named_entry->size)) {
				/* XXX FBDP use the rounded size... */
				size = vm_map_round_page(
					size,
					VM_MAP_PAGE_MASK(target_map));
			}

			if (!(flags & VM_FLAGS_ANYWHERE) &&
			    (offset != 0 ||
			     size != named_entry->size)) {
				/*
				 * XXX for a mapping at a "fixed" address,
				 * we can't trim after mapping the whole
				 * memory entry, so reject a request for a
				 * partial mapping.
				 */
				return KERN_INVALID_ARGUMENT;
			}
		}

		/* the callers parameter offset is defined to be the */
		/* offset from beginning of named entry offset in object */
		offset = offset + named_entry->offset;

		if (! VM_MAP_PAGE_ALIGNED(size,
					  VM_MAP_PAGE_MASK(target_map))) {
			/*
			 * Let's not map more than requested;
			 * vm_map_enter() will handle this "not map-aligned"
			 * case.
			 */
			map_size = size;
		}

		named_entry_lock(named_entry);
		if (named_entry->is_sub_map) {
			vm_map_t		submap;

			if (flags & (VM_FLAGS_RETURN_DATA_ADDR |
				     VM_FLAGS_RETURN_4K_DATA_ADDR)) {
				panic("VM_FLAGS_RETURN_DATA_ADDR not expected for submap.");
			}

			submap = named_entry->backing.map;
			vm_map_lock(submap);
			vm_map_reference(submap);
			vm_map_unlock(submap);
			named_entry_unlock(named_entry);

			vmk_flags.vmkf_submap = TRUE;

			result = vm_map_enter(target_map,
					      &map_addr,
					      map_size,
					      mask,
					      flags,
					      vmk_flags,
					      tag,
					      (vm_object_t)(uintptr_t) submap,
					      offset,
					      copy,
					      cur_protection,
					      max_protection,
					      inheritance);
			if (result != KERN_SUCCESS) {
				vm_map_deallocate(submap);
			} else {
				/*
				 * No need to lock "submap" just to check its
				 * "mapped" flag: that flag is never reset
				 * once it's been set and if we race, we'll
				 * just end up setting it twice, which is OK.
				 */
				if (submap->mapped_in_other_pmaps == FALSE &&
				    vm_map_pmap(submap) != PMAP_NULL &&
				    vm_map_pmap(submap) !=
				    vm_map_pmap(target_map)) {
					/*
					 * This submap is being mapped in a map
					 * that uses a different pmap.
					 * Set its "mapped_in_other_pmaps" flag
					 * to indicate that we now need to
					 * remove mappings from all pmaps rather
					 * than just the submap's pmap.
					 */
					vm_map_lock(submap);
					submap->mapped_in_other_pmaps = TRUE;
					vm_map_unlock(submap);
				}
				*address = map_addr;
			}
			return result;

		} else if (named_entry->is_copy) {
			kern_return_t	kr;
			vm_map_copy_t	copy_map;
			vm_map_entry_t	copy_entry;
			vm_map_offset_t	copy_addr;

			if (flags & ~(VM_FLAGS_FIXED |
				      VM_FLAGS_ANYWHERE |
				      VM_FLAGS_OVERWRITE |
				      VM_FLAGS_RETURN_4K_DATA_ADDR |
				      VM_FLAGS_RETURN_DATA_ADDR |
				      VM_FLAGS_ALIAS_MASK)) {
				named_entry_unlock(named_entry);
				return KERN_INVALID_ARGUMENT;
			}

			if (flags & (VM_FLAGS_RETURN_DATA_ADDR |
				     VM_FLAGS_RETURN_4K_DATA_ADDR)) {
				offset_in_mapping = offset - vm_object_trunc_page(offset);
				if (flags & VM_FLAGS_RETURN_4K_DATA_ADDR)
					offset_in_mapping &= ~((signed)(0xFFF));
				offset = vm_object_trunc_page(offset);
				map_size = vm_object_round_page(offset + offset_in_mapping + initial_size) - offset;
			}

			copy_map = named_entry->backing.copy;
			assert(copy_map->type == VM_MAP_COPY_ENTRY_LIST);
			if (copy_map->type != VM_MAP_COPY_ENTRY_LIST) {
				/* unsupported type; should not happen */
				printf("vm_map_enter_mem_object: "
				       "memory_entry->backing.copy "
				       "unsupported type 0x%x\n",
				       copy_map->type);
				named_entry_unlock(named_entry);
				return KERN_INVALID_ARGUMENT;
			}

			/* reserve a contiguous range */
			kr = vm_map_enter(target_map,
					  &map_addr,
					  /* map whole mem entry, trim later: */
					  named_entry->size,
					  mask,
					  flags & (VM_FLAGS_ANYWHERE |
						   VM_FLAGS_OVERWRITE |
						   VM_FLAGS_RETURN_4K_DATA_ADDR |
						   VM_FLAGS_RETURN_DATA_ADDR),
					  vmk_flags,
					  tag,
					  VM_OBJECT_NULL,
					  0,
					  FALSE, /* copy */
					  cur_protection,
					  max_protection,
					  inheritance);
			if (kr != KERN_SUCCESS) {
				named_entry_unlock(named_entry);
				return kr;
			}

			copy_addr = map_addr;

			for (copy_entry = vm_map_copy_first_entry(copy_map);
			     copy_entry != vm_map_copy_to_entry(copy_map);
			     copy_entry = copy_entry->vme_next) {
				int			remap_flags;
				vm_map_kernel_flags_t	vmk_remap_flags;
				vm_map_t		copy_submap;
				vm_object_t		copy_object;
				vm_map_size_t		copy_size;
				vm_object_offset_t	copy_offset;
				int			copy_vm_alias;

				remap_flags = 0;
				vmk_remap_flags = VM_MAP_KERNEL_FLAGS_NONE;

				copy_object = VME_OBJECT(copy_entry);
				copy_offset = VME_OFFSET(copy_entry);
				copy_size = (copy_entry->vme_end -
					     copy_entry->vme_start);
				VM_GET_FLAGS_ALIAS(flags, copy_vm_alias);
				if (copy_vm_alias == 0) {
					/*
					 * Caller does not want a specific
					 * alias for this new mapping:  use
					 * the alias of the original mapping.
					 */
					copy_vm_alias = VME_ALIAS(copy_entry);
				}

				/* sanity check */
				if ((copy_addr + copy_size) >
				    (map_addr +
				     named_entry->size /* XXX full size */ )) {
					/* over-mapping too much !? */
					kr = KERN_INVALID_ARGUMENT;
					/* abort */
					break;
				}

				/* take a reference on the object */
				if (copy_entry->is_sub_map) {
					vmk_remap_flags.vmkf_submap = TRUE;
					copy_submap = VME_SUBMAP(copy_entry);
					vm_map_lock(copy_submap);
					vm_map_reference(copy_submap);
					vm_map_unlock(copy_submap);
					copy_object = (vm_object_t)(uintptr_t) copy_submap;
				} else if (!copy &&
					   copy_object != VM_OBJECT_NULL &&
					   (copy_entry->needs_copy ||
					    copy_object->shadowed ||
					    (!copy_object->true_share &&
					     !copy_entry->is_shared &&
					     copy_object->vo_size > copy_size))) {
					/*
					 * We need to resolve our side of this
					 * "symmetric" copy-on-write now; we
					 * need a new object to map and share,
					 * instead of the current one which
					 * might still be shared with the
					 * original mapping.
					 *
					 * Note: A "vm_map_copy_t" does not
					 * have a lock but we're protected by
					 * the named entry's lock here.
					 */
					// assert(copy_object->copy_strategy == MEMORY_OBJECT_COPY_SYMMETRIC);
					VME_OBJECT_SHADOW(copy_entry, copy_size);
					if (!copy_entry->needs_copy &&
					    copy_entry->protection & VM_PROT_WRITE) {
						vm_prot_t prot;

						prot = copy_entry->protection & ~VM_PROT_WRITE;
						vm_object_pmap_protect(copy_object,
								       copy_offset,
								       copy_size,
								       PMAP_NULL,
								       0,
								       prot);
					}

					copy_entry->needs_copy = FALSE;
					copy_entry->is_shared = TRUE;
					copy_object = VME_OBJECT(copy_entry);
					copy_offset = VME_OFFSET(copy_entry);
					vm_object_lock(copy_object);
					vm_object_reference_locked(copy_object);
					if (copy_object->copy_strategy == MEMORY_OBJECT_COPY_SYMMETRIC) {
						/* we're about to make a shared mapping of this object */
						copy_object->copy_strategy = MEMORY_OBJECT_COPY_DELAY;
						copy_object->true_share = TRUE;
					}
					vm_object_unlock(copy_object);
				} else {
					/*
					 * We already have the right object
					 * to map.
					 */
					copy_object = VME_OBJECT(copy_entry);
					vm_object_reference(copy_object);
				}

				/* over-map the object into destination */
				remap_flags |= flags;
				remap_flags |= VM_FLAGS_FIXED;
				remap_flags |= VM_FLAGS_OVERWRITE;
				remap_flags &= ~VM_FLAGS_ANYWHERE;
				if (!copy && !copy_entry->is_sub_map) {
					/*
					 * copy-on-write should have been
					 * resolved at this point, or we would
					 * end up sharing instead of copying.
					 */
					assert(!copy_entry->needs_copy);
				}
#if !CONFIG_EMBEDDED
				if (copy_entry->used_for_jit) {
					vmk_remap_flags.vmkf_map_jit = TRUE;
				}
#endif /* !CONFIG_EMBEDDED */
				kr = vm_map_enter(target_map,
						  &copy_addr,
						  copy_size,
						  (vm_map_offset_t) 0,
						  remap_flags,
						  vmk_remap_flags,
						  copy_vm_alias,
						  copy_object,
						  copy_offset,
						  copy,
						  cur_protection,
						  max_protection,
						  inheritance);
				if (kr != KERN_SUCCESS) {
					if (copy_entry->is_sub_map) {
						vm_map_deallocate(copy_submap);
					} else {
						vm_object_deallocate(copy_object);
					}
					/* abort */
					break;
				}

				/* next mapping */
				copy_addr += copy_size;
			}

			if (kr == KERN_SUCCESS) {
				if (flags & (VM_FLAGS_RETURN_DATA_ADDR |
					     VM_FLAGS_RETURN_4K_DATA_ADDR)) {
					*address = map_addr + offset_in_mapping;
				} else {
					*address = map_addr;
				}

				if (offset) {
					/*
					 * Trim in front, from 0 to "offset".
					 */
					vm_map_remove(target_map,
						      map_addr,
						      map_addr + offset,
						      VM_MAP_REMOVE_NO_FLAGS);
					*address += offset;
				}
				if (offset + map_size < named_entry->size) {
					/*
					 * Trim in back, from
					 * "offset + map_size" to
					 * "named_entry->size".
					 */
					vm_map_remove(target_map,
						      (map_addr +
						       offset + map_size),
						      (map_addr +
						       named_entry->size),
						      VM_MAP_REMOVE_NO_FLAGS);
				}
			}
			named_entry_unlock(named_entry);

			if (kr != KERN_SUCCESS) {
				if (! (flags & VM_FLAGS_OVERWRITE)) {
					/* deallocate the contiguous range */
					(void) vm_deallocate(target_map,
							     map_addr,
							     map_size);
				}
			}

			return kr;

		} else {
			unsigned int	access;
			vm_prot_t	protections;
			unsigned int	wimg_mode;

			/* we are mapping a VM object */

			protections = named_entry->protection & VM_PROT_ALL;
			access = GET_MAP_MEM(named_entry->protection);

			if (flags & (VM_FLAGS_RETURN_DATA_ADDR |
				     VM_FLAGS_RETURN_4K_DATA_ADDR)) {
				offset_in_mapping = offset - vm_object_trunc_page(offset);
				if (flags & VM_FLAGS_RETURN_4K_DATA_ADDR)
					offset_in_mapping &= ~((signed)(0xFFF));
				offset = vm_object_trunc_page(offset);
				map_size = vm_object_round_page(offset + offset_in_mapping + initial_size) - offset;
			}

			object = named_entry->backing.object;
			assert(object != VM_OBJECT_NULL);
			vm_object_lock(object);
			named_entry_unlock(named_entry);

			vm_object_reference_locked(object);

			wimg_mode = object->wimg_bits;
                        vm_prot_to_wimg(access, &wimg_mode);
			if (object->wimg_bits != wimg_mode)
				vm_object_change_wimg_mode(object, wimg_mode);

			vm_object_unlock(object);
		}
	} else if (ip_kotype(port) == IKOT_MEMORY_OBJECT) {
		/*
		 * JMM - This is temporary until we unify named entries
		 * and raw memory objects.
		 *
		 * Detected fake ip_kotype for a memory object.  In
		 * this case, the port isn't really a port at all, but
		 * instead is just a raw memory object.
		 */
		if (flags & (VM_FLAGS_RETURN_DATA_ADDR |
			     VM_FLAGS_RETURN_4K_DATA_ADDR)) {
			panic("VM_FLAGS_RETURN_DATA_ADDR not expected for raw memory object.");
		}

		object = memory_object_to_vm_object((memory_object_t)port);
		if (object == VM_OBJECT_NULL)
			return KERN_INVALID_OBJECT;
		vm_object_reference(object);

		/* wait for object (if any) to be ready */
		if (object != VM_OBJECT_NULL) {
			if (object == kernel_object) {
				printf("Warning: Attempt to map kernel object"
					" by a non-private kernel entity\n");
				return KERN_INVALID_OBJECT;
			}
			if (!object->pager_ready) {
				vm_object_lock(object);

				while (!object->pager_ready) {
					vm_object_wait(object,
						       VM_OBJECT_EVENT_PAGER_READY,
						       THREAD_UNINT);
					vm_object_lock(object);
				}
				vm_object_unlock(object);
			}
		}
	} else {
		return KERN_INVALID_OBJECT;
	}

	if (object != VM_OBJECT_NULL &&
	    object->named &&
	    object->pager != MEMORY_OBJECT_NULL &&
	    object->copy_strategy != MEMORY_OBJECT_COPY_NONE) {
		memory_object_t pager;
		vm_prot_t	pager_prot;
		kern_return_t	kr;

		/*
		 * For "named" VM objects, let the pager know that the
		 * memory object is being mapped.  Some pagers need to keep
		 * track of this, to know when they can reclaim the memory
		 * object, for example.
		 * VM calls memory_object_map() for each mapping (specifying
		 * the protection of each mapping) and calls
		 * memory_object_last_unmap() when all the mappings are gone.
		 */
		pager_prot = max_protection;
		if (copy) {
			/*
			 * Copy-On-Write mapping: won't modify the
			 * memory object.
			 */
			pager_prot &= ~VM_PROT_WRITE;
		}
		vm_object_lock(object);
		pager = object->pager;
		if (object->named &&
		    pager != MEMORY_OBJECT_NULL &&
		    object->copy_strategy != MEMORY_OBJECT_COPY_NONE) {
			assert(object->pager_ready);
			vm_object_mapping_wait(object, THREAD_UNINT);
			vm_object_mapping_begin(object);
			vm_object_unlock(object);

			kr = memory_object_map(pager, pager_prot);
			assert(kr == KERN_SUCCESS);

			vm_object_lock(object);
			vm_object_mapping_end(object);
		}
		vm_object_unlock(object);
	}

	/*
	 *	Perform the copy if requested
	 */

	if (copy) {
		vm_object_t		new_object;
		vm_object_offset_t	new_offset;

		result = vm_object_copy_strategically(object, offset,
						      map_size,
						      &new_object, &new_offset,
						      &copy);


		if (result == KERN_MEMORY_RESTART_COPY) {
			boolean_t success;
			boolean_t src_needs_copy;

			/*
			 * XXX
			 * We currently ignore src_needs_copy.
			 * This really is the issue of how to make
			 * MEMORY_OBJECT_COPY_SYMMETRIC safe for
			 * non-kernel users to use. Solution forthcoming.
			 * In the meantime, since we don't allow non-kernel
			 * memory managers to specify symmetric copy,
			 * we won't run into problems here.
			 */
			new_object = object;
			new_offset = offset;
			success = vm_object_copy_quickly(&new_object,
							 new_offset,
							 map_size,
							 &src_needs_copy,
							 &copy);
			assert(success);
			result = KERN_SUCCESS;
		}
		/*
		 *	Throw away the reference to the
		 *	original object, as it won't be mapped.
		 */

		vm_object_deallocate(object);

		if (result != KERN_SUCCESS) {
			return result;
		}

		object = new_object;
		offset = new_offset;
	}

	/*
	 * If non-kernel users want to try to prefault pages, the mapping and prefault
	 * needs to be atomic.
	 */
	kernel_prefault = (try_prefault && vm_kernel_map_is_kernel(target_map));
	vmk_flags.vmkf_keep_map_locked = (try_prefault && !kernel_prefault);

#if __arm64__
	if (fourk) {
		/* map this object in a "4K" pager */
		result = vm_map_enter_fourk(target_map,
					    &map_addr,
					    map_size,
					    (vm_map_offset_t) mask,
					    flags,
					    vmk_flags,
					    tag,
					    object,
					    offset,
					    copy,
					    cur_protection,
					    max_protection,
					    inheritance);
	} else
#endif /* __arm64__ */
	{
		result = vm_map_enter(target_map,
				      &map_addr, map_size,
				      (vm_map_offset_t)mask,
				      flags,
				      vmk_flags,
				      tag,
				      object, offset,
				      copy,
				      cur_protection, max_protection,
				      inheritance);
	}
	if (result != KERN_SUCCESS)
		vm_object_deallocate(object);

	/*
	 * Try to prefault, and do not forget to release the vm map lock.
	 */
	if (result == KERN_SUCCESS && try_prefault) {
		mach_vm_address_t va = map_addr;
		kern_return_t kr = KERN_SUCCESS;
		unsigned int i = 0;
		int pmap_options;

		pmap_options = kernel_prefault ? 0 : PMAP_OPTIONS_NOWAIT;
		if (object->internal) {
			pmap_options |= PMAP_OPTIONS_INTERNAL;
		}

		for (i = 0; i < page_list_count; ++i) {
			if (!UPL_VALID_PAGE(page_list, i)) {
				if (kernel_prefault) {
					assertf(FALSE, "kernel_prefault && !UPL_VALID_PAGE");
					result = KERN_MEMORY_ERROR;
					break;
				}
			} else {
				/*
				 * If this function call failed, we should stop
				 * trying to optimize, other calls are likely
				 * going to fail too.
				 *
				 * We are not gonna report an error for such
				 * failure though. That's an optimization, not
				 * something critical.
				 */
				kr = pmap_enter_options(target_map->pmap,
				                        va, UPL_PHYS_PAGE(page_list, i),
				                        cur_protection, VM_PROT_NONE,
				                        0, TRUE, pmap_options, NULL);
				if (kr != KERN_SUCCESS) {
					OSIncrementAtomic64(&vm_prefault_nb_bailout);
					if (kernel_prefault) {
						result = kr;
					}
					break;
				}
				OSIncrementAtomic64(&vm_prefault_nb_pages);
			}

			/* Next virtual address */
			va += PAGE_SIZE;
		}
		if (vmk_flags.vmkf_keep_map_locked) {
			vm_map_unlock(target_map);
		}
	}

	if (flags & (VM_FLAGS_RETURN_DATA_ADDR |
		     VM_FLAGS_RETURN_4K_DATA_ADDR)) {
		*address = map_addr + offset_in_mapping;
	} else {
		*address = map_addr;
	}
	return result;
}