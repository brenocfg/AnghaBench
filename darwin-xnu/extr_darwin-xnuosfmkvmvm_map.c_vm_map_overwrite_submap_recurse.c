#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  scalar_t__ vm_map_size_t ;
typedef  scalar_t__ vm_map_offset_t ;
typedef  TYPE_1__* vm_map_entry_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  void* boolean_t ;
struct TYPE_11__ {scalar_t__ true_share; int /*<<< orphan*/  internal; } ;
struct TYPE_10__ {scalar_t__ vme_end; scalar_t__ vme_start; int protection; void* needs_wakeup; scalar_t__ in_transition; struct TYPE_10__* vme_next; scalar_t__ is_sub_map; int /*<<< orphan*/  use_pmap; } ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_INVALID_ADDRESS ; 
 int /*<<< orphan*/  KERN_PROTECTION_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  THREAD_UNINT ; 
 void* TRUE ; 
 TYPE_5__* VME_OBJECT (TYPE_1__*) ; 
 scalar_t__ VME_OFFSET (TYPE_1__*) ; 
 int /*<<< orphan*/  VME_SUBMAP (TYPE_1__*) ; 
 int /*<<< orphan*/  VM_MAP_PAGE_MASK (int /*<<< orphan*/ ) ; 
 TYPE_5__* VM_OBJECT_NULL ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vm_map_clip_start (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_entry_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_lookup_entry (int /*<<< orphan*/ ,scalar_t__,TYPE_1__**) ; 
 scalar_t__ vm_map_round_page (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* vm_map_to_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_trunc_page (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static kern_return_t
vm_map_overwrite_submap_recurse(
	vm_map_t	dst_map,
	vm_map_offset_t	dst_addr,
	vm_map_size_t	dst_size)
{
	vm_map_offset_t	dst_end;
	vm_map_entry_t	tmp_entry;
	vm_map_entry_t	entry;
	kern_return_t	result;
	boolean_t	encountered_sub_map = FALSE;



	/*
	 *	Verify that the destination is all writeable
	 *	initially.  We have to trunc the destination
	 *	address and round the copy size or we'll end up
	 *	splitting entries in strange ways.
	 */

	dst_end = vm_map_round_page(dst_addr + dst_size,
				    VM_MAP_PAGE_MASK(dst_map));
	vm_map_lock(dst_map);

start_pass_1:
	if (!vm_map_lookup_entry(dst_map, dst_addr, &tmp_entry)) {
		vm_map_unlock(dst_map);
		return(KERN_INVALID_ADDRESS);
	}

	vm_map_clip_start(dst_map,
			  tmp_entry,
			  vm_map_trunc_page(dst_addr,
					    VM_MAP_PAGE_MASK(dst_map)));
	if (tmp_entry->is_sub_map) {
		/* clipping did unnest if needed */
		assert(!tmp_entry->use_pmap);
	}

	for (entry = tmp_entry;;) {
		vm_map_entry_t	next;

		next = entry->vme_next;
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

			encountered_sub_map = TRUE;
			sub_start = VME_OFFSET(entry);

			if(entry->vme_end < dst_end)
				sub_end = entry->vme_end;
			else
				sub_end = dst_end;
			sub_end -= entry->vme_start;
			sub_end += VME_OFFSET(entry);
			local_end = entry->vme_end;
			vm_map_unlock(dst_map);

			result = vm_map_overwrite_submap_recurse(
				VME_SUBMAP(entry),
				sub_start,
				sub_end - sub_start);

			if(result != KERN_SUCCESS)
				return result;
			if (dst_end <= entry->vme_end)
				return KERN_SUCCESS;
			vm_map_lock(dst_map);
			if(!vm_map_lookup_entry(dst_map, local_end,
						&tmp_entry)) {
				vm_map_unlock(dst_map);
				return(KERN_INVALID_ADDRESS);
			}
			entry = tmp_entry;
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
		if (dst_end <= entry->vme_end) {
			vm_map_unlock(dst_map);
			return KERN_SUCCESS;
		}
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
			if(encountered_sub_map) {
				vm_map_unlock(dst_map);
				return(KERN_FAILURE);
			}
		}


		entry = next;
	}/* for */
	vm_map_unlock(dst_map);
	return(KERN_SUCCESS);
}