#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_53__   TYPE_5__ ;
typedef  struct TYPE_52__   TYPE_4__ ;
typedef  struct TYPE_51__   TYPE_3__ ;
typedef  struct TYPE_50__   TYPE_37__ ;
typedef  struct TYPE_49__   TYPE_2__ ;
typedef  struct TYPE_48__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* vm_map_t ;
typedef  scalar_t__ vm_map_size_t ;
typedef  scalar_t__ vm_map_offset_t ;
typedef  TYPE_4__* vm_map_entry_t ;
typedef  TYPE_5__* vm_map_copy_t ;
typedef  scalar_t__ vm_map_address_t ;
typedef  int /*<<< orphan*/ * pmap_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  void* boolean_t ;
struct TYPE_48__ {TYPE_4__* prev; TYPE_4__* next; } ;
struct TYPE_49__ {int nentries; TYPE_1__ links; } ;
struct TYPE_53__ {scalar_t__ type; scalar_t__ size; scalar_t__ offset; TYPE_2__ cpy_hdr; } ;
struct TYPE_52__ {scalar_t__ vme_end; scalar_t__ vme_start; int protection; scalar_t__ inheritance; void* needs_wakeup; scalar_t__ in_transition; struct TYPE_52__* vme_prev; struct TYPE_52__* vme_next; void* use_pmap; scalar_t__ user_wired_count; scalar_t__ wired_count; int /*<<< orphan*/  max_protection; void* needs_copy; void* is_shared; void* is_sub_map; int /*<<< orphan*/  iokit_acct; } ;
struct TYPE_51__ {scalar_t__ max_offset; int /*<<< orphan*/ * pmap; } ;
struct TYPE_50__ {scalar_t__ true_share; int /*<<< orphan*/  internal; } ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_INVALID_ADDRESS ; 
 int /*<<< orphan*/  KERN_PROTECTION_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  THREAD_UNINT ; 
 void* TRUE ; 
 TYPE_37__* VME_OBJECT (TYPE_4__*) ; 
 int /*<<< orphan*/  VME_OBJECT_SET (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ VME_OFFSET (TYPE_4__*) ; 
 int /*<<< orphan*/  VME_OFFSET_SET (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* VME_SUBMAP (TYPE_4__*) ; 
 scalar_t__ VM_INHERIT_COPY ; 
 scalar_t__ VM_INHERIT_SHARE ; 
 scalar_t__ VM_MAP_COPY_ENTRY_LIST ; 
 scalar_t__ VM_MAP_COPY_KERNEL_BUFFER ; 
 TYPE_5__* VM_MAP_COPY_NULL ; 
 TYPE_4__* VM_MAP_ENTRY_NULL ; 
 int /*<<< orphan*/  VM_MAP_PAGE_ALIGNED (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_MAP_PAGE_MASK (TYPE_3__*) ; 
 TYPE_37__* VM_OBJECT_NULL ; 
 int /*<<< orphan*/  VM_PROT_ALL ; 
 int VM_PROT_DEFAULT ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vm_map_clip_end (TYPE_3__*,TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  vm_map_clip_start (TYPE_3__*,TYPE_4__*,scalar_t__) ; 
 TYPE_5__* vm_map_copy_allocate () ; 
 int /*<<< orphan*/  vm_map_copy_clip_end (TYPE_5__*,TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  vm_map_copy_discard (TYPE_5__*) ; 
 TYPE_4__* vm_map_copy_first_entry (TYPE_5__*) ; 
 int /*<<< orphan*/  vm_map_copy_overwrite_aligned (TYPE_3__*,TYPE_4__*,TYPE_5__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_map_copy_overwrite_unaligned (TYPE_3__*,TYPE_4__*,TYPE_5__*,scalar_t__,void*) ; 
 TYPE_4__* vm_map_copy_to_entry (TYPE_5__*) ; 
 int /*<<< orphan*/  vm_map_copyout_kernel_buffer (TYPE_3__*,scalar_t__*,TYPE_5__*,scalar_t__,void*,void*) ; 
 int /*<<< orphan*/  vm_map_deallocate (TYPE_3__*) ; 
 int /*<<< orphan*/  vm_map_entry_wait (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  vm_map_lookup_entry (TYPE_3__*,scalar_t__,TYPE_4__**) ; 
 int /*<<< orphan*/  vm_map_overwrite_submap_recurse (TYPE_3__*,scalar_t__,scalar_t__) ; 
 scalar_t__ vm_map_round_page (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_4__* vm_map_to_entry (TYPE_3__*) ; 
 scalar_t__ vm_map_trunc_page (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_unlock (TYPE_3__*) ; 

__attribute__((used)) static kern_return_t
vm_map_copy_overwrite_nested(
	vm_map_t		dst_map,
	vm_map_address_t	dst_addr,
	vm_map_copy_t		copy,
	boolean_t		interruptible,
	pmap_t			pmap,
	boolean_t		discard_on_success)
{
	vm_map_offset_t		dst_end;
	vm_map_entry_t		tmp_entry;
	vm_map_entry_t		entry;
	kern_return_t		kr;
	boolean_t		aligned = TRUE;
	boolean_t		contains_permanent_objects = FALSE;
	boolean_t		encountered_sub_map = FALSE;
	vm_map_offset_t		base_addr;
	vm_map_size_t		copy_size;
	vm_map_size_t		total_size;


	/*
	 *	Check for null copy object.
	 */

	if (copy == VM_MAP_COPY_NULL)
		return(KERN_SUCCESS);

	/*
	 *	Check for special kernel buffer allocated
	 *	by new_ipc_kmsg_copyin.
	 */

	if (copy->type == VM_MAP_COPY_KERNEL_BUFFER) {
		return(vm_map_copyout_kernel_buffer(
			       dst_map, &dst_addr,
			       copy, copy->size, TRUE, discard_on_success));
	}

	/*
	 *      Only works for entry lists at the moment.  Will
	 *	support page lists later.
	 */

	assert(copy->type == VM_MAP_COPY_ENTRY_LIST);

	if (copy->size == 0) {
		if (discard_on_success)
			vm_map_copy_discard(copy);
		return(KERN_SUCCESS);
	}

	/*
	 *	Verify that the destination is all writeable
	 *	initially.  We have to trunc the destination
	 *	address and round the copy size or we'll end up
	 *	splitting entries in strange ways.
	 */

	if (!VM_MAP_PAGE_ALIGNED(copy->size,
				 VM_MAP_PAGE_MASK(dst_map)) ||
	    !VM_MAP_PAGE_ALIGNED(copy->offset,
				 VM_MAP_PAGE_MASK(dst_map)) ||
	    !VM_MAP_PAGE_ALIGNED(dst_addr,
				 VM_MAP_PAGE_MASK(dst_map)))
	{
		aligned = FALSE;
		dst_end = vm_map_round_page(dst_addr + copy->size,
					    VM_MAP_PAGE_MASK(dst_map));
	} else {
		dst_end = dst_addr + copy->size;
	}

	vm_map_lock(dst_map);

	/* LP64todo - remove this check when vm_map_commpage64()
	 * no longer has to stuff in a map_entry for the commpage
	 * above the map's max_offset.
	 */
	if (dst_addr >= dst_map->max_offset) {
		vm_map_unlock(dst_map);
		return(KERN_INVALID_ADDRESS);
	}

start_pass_1:
	if (!vm_map_lookup_entry(dst_map, dst_addr, &tmp_entry)) {
		vm_map_unlock(dst_map);
		return(KERN_INVALID_ADDRESS);
	}
	vm_map_clip_start(dst_map,
			  tmp_entry,
			  vm_map_trunc_page(dst_addr,
					    VM_MAP_PAGE_MASK(dst_map)));
	for (entry = tmp_entry;;) {
		vm_map_entry_t	next = entry->vme_next;

		while(entry->is_sub_map) {
			vm_map_offset_t	sub_start;
			vm_map_offset_t	sub_end;
			vm_map_offset_t	local_end;

                	if (entry->in_transition) {

				/*
				 * Say that we are waiting, and wait for entry.
				 */
                        	entry->needs_wakeup = TRUE;
                        	vm_map_entry_wait(dst_map, THREAD_UNINT);

				goto start_pass_1;
			}

			local_end = entry->vme_end;
		        if (!(entry->needs_copy)) {
				/* if needs_copy we are a COW submap */
				/* in such a case we just replace so */
				/* there is no need for the follow-  */
				/* ing check.                        */
				encountered_sub_map = TRUE;
				sub_start = VME_OFFSET(entry);

				if(entry->vme_end < dst_end)
					sub_end = entry->vme_end;
				else
					sub_end = dst_end;
				sub_end -= entry->vme_start;
				sub_end += VME_OFFSET(entry);
				vm_map_unlock(dst_map);

				kr = vm_map_overwrite_submap_recurse(
					VME_SUBMAP(entry),
					sub_start,
					sub_end - sub_start);
				if(kr != KERN_SUCCESS)
					return kr;
				vm_map_lock(dst_map);
			}

			if (dst_end <= entry->vme_end)
				goto start_overwrite;
			if(!vm_map_lookup_entry(dst_map, local_end,
						&entry)) {
				vm_map_unlock(dst_map);
				return(KERN_INVALID_ADDRESS);
			}
			next = entry->vme_next;
		}

		if ( ! (entry->protection & VM_PROT_WRITE)) {
			vm_map_unlock(dst_map);
			return(KERN_PROTECTION_FAILURE);
		}

		/*
		 *	If the entry is in transition, we must wait
		 *	for it to exit that state.  Anything could happen
		 *	when we unlock the map, so start over.
		 */
                if (entry->in_transition) {

                        /*
                         * Say that we are waiting, and wait for entry.
                         */
                        entry->needs_wakeup = TRUE;
                        vm_map_entry_wait(dst_map, THREAD_UNINT);

			goto start_pass_1;
		}

/*
 *		our range is contained completely within this map entry
 */
		if (dst_end <= entry->vme_end)
			break;
/*
 *		check that range specified is contiguous region
 */
		if ((next == vm_map_to_entry(dst_map)) ||
		    (next->vme_start != entry->vme_end)) {
			vm_map_unlock(dst_map);
			return(KERN_INVALID_ADDRESS);
		}


		/*
		 *	Check for permanent objects in the destination.
		 */
		if ((VME_OBJECT(entry) != VM_OBJECT_NULL) &&
		    ((!VME_OBJECT(entry)->internal) ||
		     (VME_OBJECT(entry)->true_share))) {
			contains_permanent_objects = TRUE;
		}

		entry = next;
	}/* for */

start_overwrite:
	/*
	 *	If there are permanent objects in the destination, then
	 *	the copy cannot be interrupted.
	 */

	if (interruptible && contains_permanent_objects) {
		vm_map_unlock(dst_map);
		return(KERN_FAILURE);	/* XXX */
	}

	/*
 	 *
	 *	Make a second pass, overwriting the data
	 *	At the beginning of each loop iteration,
	 *	the next entry to be overwritten is "tmp_entry"
	 *	(initially, the value returned from the lookup above),
	 *	and the starting address expected in that entry
	 *	is "start".
	 */

	total_size = copy->size;
	if(encountered_sub_map) {
		copy_size = 0;
		/* re-calculate tmp_entry since we've had the map */
		/* unlocked */
		if (!vm_map_lookup_entry( dst_map, dst_addr, &tmp_entry)) {
			vm_map_unlock(dst_map);
			return(KERN_INVALID_ADDRESS);
		}
	} else {
		copy_size = copy->size;
	}

	base_addr = dst_addr;
	while(TRUE) {
		/* deconstruct the copy object and do in parts */
		/* only in sub_map, interruptable case */
		vm_map_entry_t	copy_entry;
		vm_map_entry_t	previous_prev = VM_MAP_ENTRY_NULL;
		vm_map_entry_t	next_copy = VM_MAP_ENTRY_NULL;
		int		nentries;
		int		remaining_entries = 0;
		vm_map_offset_t	new_offset = 0;

		for (entry = tmp_entry; copy_size == 0;) {
			vm_map_entry_t	next;

			next = entry->vme_next;

			/* tmp_entry and base address are moved along */
			/* each time we encounter a sub-map.  Otherwise */
			/* entry can outpase tmp_entry, and the copy_size */
			/* may reflect the distance between them */
			/* if the current entry is found to be in transition */
			/* we will start over at the beginning or the last */
			/* encounter of a submap as dictated by base_addr */
			/* we will zero copy_size accordingly. */
			if (entry->in_transition) {
                       		/*
                       		 * Say that we are waiting, and wait for entry.
                       		 */
                       		entry->needs_wakeup = TRUE;
                       		vm_map_entry_wait(dst_map, THREAD_UNINT);

				if(!vm_map_lookup_entry(dst_map, base_addr,
							&tmp_entry)) {
					vm_map_unlock(dst_map);
					return(KERN_INVALID_ADDRESS);
				}
				copy_size = 0;
				entry = tmp_entry;
				continue;
			}
			if (entry->is_sub_map) {
				vm_map_offset_t	sub_start;
				vm_map_offset_t	sub_end;
				vm_map_offset_t	local_end;

		        	if (entry->needs_copy) {
					/* if this is a COW submap */
					/* just back the range with a */
					/* anonymous entry */
					if(entry->vme_end < dst_end)
						sub_end = entry->vme_end;
					else
						sub_end = dst_end;
					if(entry->vme_start < base_addr)
						sub_start = base_addr;
					else
						sub_start = entry->vme_start;
					vm_map_clip_end(
						dst_map, entry, sub_end);
					vm_map_clip_start(
						dst_map, entry, sub_start);
					assert(!entry->use_pmap);
					assert(!entry->iokit_acct);
					entry->use_pmap = TRUE;
					entry->is_sub_map = FALSE;
					vm_map_deallocate(
						VME_SUBMAP(entry));
					VME_OBJECT_SET(entry, NULL);
					VME_OFFSET_SET(entry, 0);
					entry->is_shared = FALSE;
					entry->needs_copy = FALSE;
					entry->protection = VM_PROT_DEFAULT;
					entry->max_protection = VM_PROT_ALL;
					entry->wired_count = 0;
					entry->user_wired_count = 0;
					if(entry->inheritance
					   == VM_INHERIT_SHARE)
						entry->inheritance = VM_INHERIT_COPY;
					continue;
				}
				/* first take care of any non-sub_map */
				/* entries to send */
				if(base_addr < entry->vme_start) {
					/* stuff to send */
					copy_size =
						entry->vme_start - base_addr;
					break;
				}
				sub_start = VME_OFFSET(entry);

				if(entry->vme_end < dst_end)
					sub_end = entry->vme_end;
				else
					sub_end = dst_end;
				sub_end -= entry->vme_start;
				sub_end += VME_OFFSET(entry);
				local_end = entry->vme_end;
				vm_map_unlock(dst_map);
				copy_size = sub_end - sub_start;

				/* adjust the copy object */
				if (total_size > copy_size) {
					vm_map_size_t	local_size = 0;
					vm_map_size_t	entry_size;

					nentries = 1;
					new_offset = copy->offset;
					copy_entry = vm_map_copy_first_entry(copy);
					while(copy_entry !=
					      vm_map_copy_to_entry(copy)){
						entry_size = copy_entry->vme_end -
							copy_entry->vme_start;
						if((local_size < copy_size) &&
						   ((local_size + entry_size)
						    >= copy_size)) {
							vm_map_copy_clip_end(copy,
									     copy_entry,
									     copy_entry->vme_start +
									     (copy_size - local_size));
							entry_size = copy_entry->vme_end -
								copy_entry->vme_start;
							local_size += entry_size;
							new_offset += entry_size;
						}
						if(local_size >= copy_size) {
							next_copy = copy_entry->vme_next;
							copy_entry->vme_next =
								vm_map_copy_to_entry(copy);
							previous_prev =
								copy->cpy_hdr.links.prev;
							copy->cpy_hdr.links.prev = copy_entry;
							copy->size = copy_size;
							remaining_entries =
								copy->cpy_hdr.nentries;
							remaining_entries -= nentries;
							copy->cpy_hdr.nentries = nentries;
							break;
						} else {
							local_size += entry_size;
							new_offset += entry_size;
							nentries++;
						}
						copy_entry = copy_entry->vme_next;
					}
				}

				if((entry->use_pmap) && (pmap == NULL)) {
					kr = vm_map_copy_overwrite_nested(
						VME_SUBMAP(entry),
						sub_start,
						copy,
						interruptible,
						VME_SUBMAP(entry)->pmap,
						TRUE);
				} else if (pmap != NULL) {
					kr = vm_map_copy_overwrite_nested(
						VME_SUBMAP(entry),
						sub_start,
						copy,
						interruptible, pmap,
						TRUE);
				} else {
					kr = vm_map_copy_overwrite_nested(
						VME_SUBMAP(entry),
						sub_start,
						copy,
						interruptible,
						dst_map->pmap,
						TRUE);
				}
				if(kr != KERN_SUCCESS) {
					if(next_copy != NULL) {
						copy->cpy_hdr.nentries +=
							remaining_entries;
						copy->cpy_hdr.links.prev->vme_next =
							next_copy;
						copy->cpy_hdr.links.prev
							= previous_prev;
						copy->size = total_size;
					}
					return kr;
				}
				if (dst_end <= local_end) {
					return(KERN_SUCCESS);
				}
				/* otherwise copy no longer exists, it was */
				/* destroyed after successful copy_overwrite */
				copy = vm_map_copy_allocate();
				copy->type = VM_MAP_COPY_ENTRY_LIST;
				copy->offset = new_offset;

				/*
				 * XXX FBDP
				 * this does not seem to deal with
				 * the VM map store (R&B tree)
				 */

				total_size -= copy_size;
				copy_size = 0;
				/* put back remainder of copy in container */
				if(next_copy != NULL) {
					copy->cpy_hdr.nentries = remaining_entries;
					copy->cpy_hdr.links.next = next_copy;
					copy->cpy_hdr.links.prev = previous_prev;
					copy->size = total_size;
					next_copy->vme_prev =
						vm_map_copy_to_entry(copy);
					next_copy = NULL;
				}
				base_addr = local_end;
				vm_map_lock(dst_map);
				if(!vm_map_lookup_entry(dst_map,
							local_end, &tmp_entry)) {
					vm_map_unlock(dst_map);
					return(KERN_INVALID_ADDRESS);
				}
				entry = tmp_entry;
				continue;
			}
			if (dst_end <= entry->vme_end) {
				copy_size = dst_end - base_addr;
				break;
			}

			if ((next == vm_map_to_entry(dst_map)) ||
			    (next->vme_start != entry->vme_end)) {
				vm_map_unlock(dst_map);
				return(KERN_INVALID_ADDRESS);
			}

			entry = next;
		}/* for */

		next_copy = NULL;
		nentries = 1;

		/* adjust the copy object */
		if (total_size > copy_size) {
			vm_map_size_t	local_size = 0;
			vm_map_size_t	entry_size;

			new_offset = copy->offset;
			copy_entry = vm_map_copy_first_entry(copy);
			while(copy_entry != vm_map_copy_to_entry(copy)) {
				entry_size = copy_entry->vme_end -
					copy_entry->vme_start;
				if((local_size < copy_size) &&
				   ((local_size + entry_size)
				    >= copy_size)) {
					vm_map_copy_clip_end(copy, copy_entry,
							     copy_entry->vme_start +
							     (copy_size - local_size));
					entry_size = copy_entry->vme_end -
						copy_entry->vme_start;
					local_size += entry_size;
					new_offset += entry_size;
				}
				if(local_size >= copy_size) {
					next_copy = copy_entry->vme_next;
					copy_entry->vme_next =
						vm_map_copy_to_entry(copy);
					previous_prev =
						copy->cpy_hdr.links.prev;
					copy->cpy_hdr.links.prev = copy_entry;
					copy->size = copy_size;
					remaining_entries =
						copy->cpy_hdr.nentries;
					remaining_entries -= nentries;
					copy->cpy_hdr.nentries = nentries;
					break;
				} else {
					local_size += entry_size;
					new_offset += entry_size;
					nentries++;
				}
				copy_entry = copy_entry->vme_next;
			}
		}

		if (aligned) {
			pmap_t	local_pmap;

			if(pmap)
				local_pmap = pmap;
			else
				local_pmap = dst_map->pmap;

			if ((kr =  vm_map_copy_overwrite_aligned(
				     dst_map, tmp_entry, copy,
				     base_addr, local_pmap)) != KERN_SUCCESS) {
				if(next_copy != NULL) {
					copy->cpy_hdr.nentries +=
						remaining_entries;
				        copy->cpy_hdr.links.prev->vme_next =
						next_copy;
			       		copy->cpy_hdr.links.prev =
						previous_prev;
					copy->size += copy_size;
				}
				return kr;
			}
			vm_map_unlock(dst_map);
		} else {
			/*
			 * Performance gain:
			 *
			 * if the copy and dst address are misaligned but the same
			 * offset within the page we can copy_not_aligned the
			 * misaligned parts and copy aligned the rest.  If they are
			 * aligned but len is unaligned we simply need to copy
			 * the end bit unaligned.  We'll need to split the misaligned
			 * bits of the region in this case !
			 */
			/* ALWAYS UNLOCKS THE dst_map MAP */
			kr = vm_map_copy_overwrite_unaligned(
				dst_map,
				tmp_entry,
				copy,
				base_addr,
				discard_on_success);
			if (kr != KERN_SUCCESS) {
				if(next_copy != NULL) {
					copy->cpy_hdr.nentries +=
						remaining_entries;
			       		copy->cpy_hdr.links.prev->vme_next =
						next_copy;
			       		copy->cpy_hdr.links.prev =
						previous_prev;
					copy->size += copy_size;
				}
				return kr;
			}
		}
		total_size -= copy_size;
		if(total_size == 0)
			break;
		base_addr += copy_size;
		copy_size = 0;
		copy->offset = new_offset;
		if(next_copy != NULL) {
			copy->cpy_hdr.nentries = remaining_entries;
			copy->cpy_hdr.links.next = next_copy;
			copy->cpy_hdr.links.prev = previous_prev;
			next_copy->vme_prev = vm_map_copy_to_entry(copy);
			copy->size = total_size;
		}
		vm_map_lock(dst_map);
		while(TRUE) {
			if (!vm_map_lookup_entry(dst_map,
						 base_addr, &tmp_entry)) {
				vm_map_unlock(dst_map);
				return(KERN_INVALID_ADDRESS);
			}
                	if (tmp_entry->in_transition) {
                       		entry->needs_wakeup = TRUE;
                       		vm_map_entry_wait(dst_map, THREAD_UNINT);
			} else {
				break;
			}
		}
		vm_map_clip_start(dst_map,
				  tmp_entry,
				  vm_map_trunc_page(base_addr,
						    VM_MAP_PAGE_MASK(dst_map)));

		entry = tmp_entry;
	} /* while */

	/*
	 *	Throw away the vm_map_copy object
	 */
	if (discard_on_success)
		vm_map_copy_discard(copy);

	return(KERN_SUCCESS);
}