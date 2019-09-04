#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_20__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_18__ ;

/* Type definitions */
typedef  TYPE_2__* vm_region_submap_short_info_64_t ;
typedef  TYPE_3__* vm_region_submap_info_64_t ;
struct TYPE_33__ {unsigned int pages_resident; unsigned int pages_swapped_out; unsigned int pages_dirtied; scalar_t__ share_mode; int ref_count; scalar_t__ shadow_depth; scalar_t__ external_pager; scalar_t__ pages_reusable; scalar_t__ pages_shared_now_private; } ;
typedef  TYPE_4__ vm_region_extended_info_data_t ;
typedef  TYPE_5__* vm_map_t ;
typedef  scalar_t__ vm_map_size_t ;
typedef  scalar_t__ vm_map_offset_t ;
typedef  TYPE_6__* vm_map_entry_t ;
typedef  scalar_t__ vm_map_address_t ;
typedef  void* uint32_t ;
typedef  unsigned int natural_t ;
typedef  scalar_t__ mach_msg_type_number_t ;
typedef  int ledger_amount_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_35__ {scalar_t__ vme_start; scalar_t__ vme_end; scalar_t__ use_pmap; scalar_t__ is_sub_map; scalar_t__ user_wired_count; void* behavior; void* max_protection; void* inheritance; void* protection; struct TYPE_35__* vme_next; } ;
struct TYPE_34__ {int map_refcnt; TYPE_1__* pmap; } ;
struct TYPE_32__ {int user_tag; unsigned int pages_resident; unsigned int pages_swapped_out; unsigned int pages_dirtied; int ref_count; scalar_t__ share_mode; scalar_t__ pages_reusable; scalar_t__ shadow_depth; scalar_t__ external_pager; scalar_t__ pages_shared_now_private; void* object_id; scalar_t__ is_submap; scalar_t__ user_wired_count; void* behavior; void* max_protection; void* inheritance; void* protection; scalar_t__ offset; } ;
struct TYPE_31__ {int user_tag; scalar_t__ share_mode; int ref_count; scalar_t__ shadow_depth; scalar_t__ external_pager; void* object_id; scalar_t__ is_submap; scalar_t__ user_wired_count; void* behavior; void* max_protection; void* inheritance; void* protection; scalar_t__ offset; } ;
struct TYPE_30__ {int /*<<< orphan*/  purgeable_nonvolatile; int /*<<< orphan*/  purgeable_nonvolatile_compressed; } ;
struct TYPE_29__ {int /*<<< orphan*/  ledger; } ;
struct TYPE_28__ {scalar_t__ vme_end; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 void* INFO_MAKE_FAKE_OBJECT_ID (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_INVALID_ADDRESS ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ MAX (scalar_t__,scalar_t__) ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 int PAGE_SIZE ; 
 scalar_t__ SM_EMPTY ; 
 void* SM_PRIVATE ; 
 scalar_t__ SM_SHARED ; 
 scalar_t__ SM_TRUESHARED ; 
 scalar_t__ TRUE ; 
 void* VME_ALIAS (TYPE_6__*) ; 
 int /*<<< orphan*/  VME_OBJECT (TYPE_6__*) ; 
 scalar_t__ VME_OFFSET (TYPE_6__*) ; 
 TYPE_5__* VME_SUBMAP (TYPE_6__*) ; 
 void* VM_BEHAVIOR_DEFAULT ; 
 void* VM_INHERIT_DEFAULT ; 
 scalar_t__ VM_KERNEL_ADDRPERM (int /*<<< orphan*/ ) ; 
 TYPE_5__* VM_MAP_NULL ; 
 void* VM_PROT_DEFAULT ; 
 int /*<<< orphan*/  VM_REGION_EXTENDED_INFO_COUNT ; 
 scalar_t__ VM_REGION_SUBMAP_INFO_V0_COUNT_64 ; 
 scalar_t__ VM_REGION_SUBMAP_INFO_V1_COUNT_64 ; 
 scalar_t__ VM_REGION_SUBMAP_SHORT_INFO_COUNT_64 ; 
 int /*<<< orphan*/  ledger_get_balance (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ not_in_kdp ; 
 TYPE_20__ task_ledgers ; 
 scalar_t__ task_self_region_footprint () ; 
 TYPE_18__* vm_map_last_entry (TYPE_5__*) ; 
 int /*<<< orphan*/  vm_map_lock_read (TYPE_5__*) ; 
 scalar_t__ vm_map_lookup_entry (TYPE_5__*,scalar_t__,TYPE_6__**) ; 
 int /*<<< orphan*/  vm_map_region_walk (TYPE_5__*,scalar_t__,TYPE_6__*,scalar_t__,scalar_t__,TYPE_4__*,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_6__* vm_map_to_entry (TYPE_5__*) ; 
 int /*<<< orphan*/  vm_map_unlock_read (TYPE_5__*) ; 

kern_return_t
vm_map_region_recurse_64(
	vm_map_t		 map,
	vm_map_offset_t	*address,		/* IN/OUT */
	vm_map_size_t		*size,			/* OUT */
	natural_t	 	*nesting_depth,	/* IN/OUT */
	vm_region_submap_info_64_t	submap_info,	/* IN/OUT */
	mach_msg_type_number_t	*count)	/* IN/OUT */
{
	mach_msg_type_number_t	original_count;
	vm_region_extended_info_data_t	extended;
	vm_map_entry_t			tmp_entry;
	vm_map_offset_t			user_address;
	unsigned int			user_max_depth;

	/*
	 * "curr_entry" is the VM map entry preceding or including the
	 * address we're looking for.
	 * "curr_map" is the map or sub-map containing "curr_entry".
	 * "curr_address" is the equivalent of the top map's "user_address"
	 * in the current map.
	 * "curr_offset" is the cumulated offset of "curr_map" in the
	 * target task's address space.
	 * "curr_depth" is the depth of "curr_map" in the chain of
	 * sub-maps.
	 *
	 * "curr_max_below" and "curr_max_above" limit the range (around
	 * "curr_address") we should take into account in the current (sub)map.
	 * They limit the range to what's visible through the map entries
	 * we've traversed from the top map to the current map.

	 */
	vm_map_entry_t			curr_entry;
	vm_map_address_t		curr_address;
	vm_map_offset_t			curr_offset;
	vm_map_t			curr_map;
	unsigned int			curr_depth;
	vm_map_offset_t			curr_max_below, curr_max_above;
	vm_map_offset_t			curr_skip;

	/*
	 * "next_" is the same as "curr_" but for the VM region immediately
	 * after the address we're looking for.  We need to keep track of this
	 * too because we want to return info about that region if the
	 * address we're looking for is not mapped.
	 */
	vm_map_entry_t			next_entry;
	vm_map_offset_t			next_offset;
	vm_map_offset_t			next_address;
	vm_map_t			next_map;
	unsigned int			next_depth;
	vm_map_offset_t			next_max_below, next_max_above;
	vm_map_offset_t			next_skip;

	boolean_t			look_for_pages;
	vm_region_submap_short_info_64_t short_info;
	boolean_t			do_region_footprint;

	if (map == VM_MAP_NULL) {
		/* no address space to work on */
		return KERN_INVALID_ARGUMENT;
	}


	if (*count < VM_REGION_SUBMAP_SHORT_INFO_COUNT_64) {
		/*
		 * "info" structure is not big enough and
		 * would overflow
		 */
		return KERN_INVALID_ARGUMENT;
	}

	do_region_footprint = task_self_region_footprint();
	original_count = *count;

	if (original_count < VM_REGION_SUBMAP_INFO_V0_COUNT_64) {
		*count = VM_REGION_SUBMAP_SHORT_INFO_COUNT_64;
		look_for_pages = FALSE;
		short_info = (vm_region_submap_short_info_64_t) submap_info;
		submap_info = NULL;
	} else {
		look_for_pages = TRUE;
		*count = VM_REGION_SUBMAP_INFO_V0_COUNT_64;
		short_info = NULL;

		if (original_count >= VM_REGION_SUBMAP_INFO_V1_COUNT_64) {
			*count = VM_REGION_SUBMAP_INFO_V1_COUNT_64;
		}
	}

	user_address = *address;
	user_max_depth = *nesting_depth;

	if (not_in_kdp) {
		vm_map_lock_read(map);
	}

recurse_again:
	curr_entry = NULL;
	curr_map = map;
	curr_address = user_address;
	curr_offset = 0;
	curr_skip = 0;
	curr_depth = 0;
	curr_max_above = ((vm_map_offset_t) -1) - curr_address;
	curr_max_below = curr_address;

	next_entry = NULL;
	next_map = NULL;
	next_address = 0;
	next_offset = 0;
	next_skip = 0;
	next_depth = 0;
	next_max_above = (vm_map_offset_t) -1;
	next_max_below = (vm_map_offset_t) -1;

	for (;;) {
		if (vm_map_lookup_entry(curr_map,
					curr_address,
					&tmp_entry)) {
			/* tmp_entry contains the address we're looking for */
			curr_entry = tmp_entry;
		} else {
			vm_map_offset_t skip;
			/*
			 * The address is not mapped.  "tmp_entry" is the
			 * map entry preceding the address.  We want the next
			 * one, if it exists.
			 */
			curr_entry = tmp_entry->vme_next;

			if (curr_entry == vm_map_to_entry(curr_map) ||
			    (curr_entry->vme_start >=
			     curr_address + curr_max_above)) {
				/* no next entry at this level: stop looking */
				if (not_in_kdp) {
					vm_map_unlock_read(curr_map);
				}
				curr_entry = NULL;
				curr_map = NULL;
				curr_skip = 0;
				curr_offset = 0;
				curr_depth = 0;
				curr_max_above = 0;
				curr_max_below = 0;
				break;
			}

			/* adjust current address and offset */
			skip = curr_entry->vme_start - curr_address;
			curr_address = curr_entry->vme_start;
			curr_skip += skip;
			curr_offset += skip;
			curr_max_above -= skip;
			curr_max_below = 0;
		}

		/*
		 * Is the next entry at this level closer to the address (or
		 * deeper in the submap chain) than the one we had
		 * so far ?
		 */
		tmp_entry = curr_entry->vme_next;
		if (tmp_entry == vm_map_to_entry(curr_map)) {
			/* no next entry at this level */
		} else if (tmp_entry->vme_start >=
			   curr_address + curr_max_above) {
			/*
			 * tmp_entry is beyond the scope of what we mapped of
			 * this submap in the upper level: ignore it.
			 */
		} else if ((next_entry == NULL) ||
			   (tmp_entry->vme_start + curr_offset <=
			    next_entry->vme_start + next_offset)) {
			/*
			 * We didn't have a "next_entry" or this one is
			 * closer to the address we're looking for:
			 * use this "tmp_entry" as the new "next_entry".
			 */
			if (next_entry != NULL) {
				/* unlock the last "next_map" */
				if (next_map != curr_map && not_in_kdp) {
					vm_map_unlock_read(next_map);
				}
			}
			next_entry = tmp_entry;
			next_map = curr_map;
			next_depth = curr_depth;
			next_address = next_entry->vme_start;
			next_skip = curr_skip;
			next_skip += (next_address - curr_address);
			next_offset = curr_offset;
			next_offset += (next_address - curr_address);
			next_max_above = MIN(next_max_above, curr_max_above);
			next_max_above = MIN(next_max_above,
					     next_entry->vme_end - next_address);
			next_max_below = MIN(next_max_below, curr_max_below);
			next_max_below = MIN(next_max_below,
					     next_address - next_entry->vme_start);
		}

		/*
		 * "curr_max_{above,below}" allow us to keep track of the
		 * portion of the submap that is actually mapped at this level:
		 * the rest of that submap is irrelevant to us, since it's not
		 * mapped here.
		 * The relevant portion of the map starts at
		 * "VME_OFFSET(curr_entry)" up to the size of "curr_entry".
		 */
		curr_max_above = MIN(curr_max_above,
				     curr_entry->vme_end - curr_address);
		curr_max_below = MIN(curr_max_below,
				     curr_address - curr_entry->vme_start);

		if (!curr_entry->is_sub_map ||
		    curr_depth >= user_max_depth) {
			/*
			 * We hit a leaf map or we reached the maximum depth
			 * we could, so stop looking.  Keep the current map
			 * locked.
			 */
			break;
		}

		/*
		 * Get down to the next submap level.
		 */

		/*
		 * Lock the next level and unlock the current level,
		 * unless we need to keep it locked to access the "next_entry"
		 * later.
		 */
		if (not_in_kdp) {
			vm_map_lock_read(VME_SUBMAP(curr_entry));
		}
		if (curr_map == next_map) {
			/* keep "next_map" locked in case we need it */
		} else {
			/* release this map */
			if (not_in_kdp)
				vm_map_unlock_read(curr_map);
		}

		/*
		 * Adjust the offset.  "curr_entry" maps the submap
		 * at relative address "curr_entry->vme_start" in the
		 * curr_map but skips the first "VME_OFFSET(curr_entry)"
		 * bytes of the submap.
		 * "curr_offset" always represents the offset of a virtual
		 * address in the curr_map relative to the absolute address
		 * space (i.e. the top-level VM map).
		 */
		curr_offset +=
			(VME_OFFSET(curr_entry) - curr_entry->vme_start);
		curr_address = user_address + curr_offset;
		/* switch to the submap */
		curr_map = VME_SUBMAP(curr_entry);
		curr_depth++;
		curr_entry = NULL;
	}

// LP64todo: all the current tools are 32bit, obviously never worked for 64b
// so probably should be a real 32b ID vs. ptr.
// Current users just check for equality

	if (curr_entry == NULL) {
		/* no VM region contains the address... */

		if (do_region_footprint && /* we want footprint numbers */
		    next_entry == NULL && /* & there are no more regions */
		    /* & we haven't already provided our fake region: */
		    user_address <= vm_map_last_entry(map)->vme_end) {
			ledger_amount_t nonvol, nonvol_compressed;
			/*
			 * Add a fake memory region to account for
			 * purgeable memory that counts towards this
			 * task's memory footprint, i.e. the resident
			 * compressed pages of non-volatile objects
			 * owned by that task.
			 */
			ledger_get_balance(
				map->pmap->ledger,
				task_ledgers.purgeable_nonvolatile,
				&nonvol);
			ledger_get_balance(
				map->pmap->ledger,
				task_ledgers.purgeable_nonvolatile_compressed,
				&nonvol_compressed);
			if (nonvol + nonvol_compressed == 0) {
				/* no purgeable memory usage to report */
				return KERN_INVALID_ADDRESS;
			}
			/* fake region to show nonvolatile footprint */
			if (look_for_pages) {
				submap_info->protection = VM_PROT_DEFAULT;
				submap_info->max_protection = VM_PROT_DEFAULT;
				submap_info->inheritance = VM_INHERIT_DEFAULT;
				submap_info->offset = 0;
				submap_info->user_tag = -1;
				submap_info->pages_resident = (unsigned int) (nonvol / PAGE_SIZE);
				submap_info->pages_shared_now_private = 0;
				submap_info->pages_swapped_out = (unsigned int) (nonvol_compressed / PAGE_SIZE);
				submap_info->pages_dirtied = submap_info->pages_resident;
				submap_info->ref_count = 1;
				submap_info->shadow_depth = 0;
				submap_info->external_pager = 0;
				submap_info->share_mode = SM_PRIVATE;
				submap_info->is_submap = 0;
				submap_info->behavior = VM_BEHAVIOR_DEFAULT;
				submap_info->object_id = INFO_MAKE_FAKE_OBJECT_ID(map, task_ledgers.purgeable_nonvolatile);
				submap_info->user_wired_count = 0;
				submap_info->pages_reusable = 0;
			} else {
				short_info->user_tag = -1;
				short_info->offset = 0;
				short_info->protection = VM_PROT_DEFAULT;
				short_info->inheritance = VM_INHERIT_DEFAULT;
				short_info->max_protection = VM_PROT_DEFAULT;
				short_info->behavior = VM_BEHAVIOR_DEFAULT;
				short_info->user_wired_count = 0;
				short_info->is_submap = 0;
				short_info->object_id = INFO_MAKE_FAKE_OBJECT_ID(map, task_ledgers.purgeable_nonvolatile);
				short_info->external_pager = 0;
				short_info->shadow_depth = 0;
				short_info->share_mode = SM_PRIVATE;
				short_info->ref_count = 1;
			}
			*nesting_depth = 0;
			*size = (vm_map_size_t) (nonvol + nonvol_compressed);
//			*address = user_address;
			*address = vm_map_last_entry(map)->vme_end;
			return KERN_SUCCESS;
		}

		if (next_entry == NULL) {
			/* ... and no VM region follows it either */
			return KERN_INVALID_ADDRESS;
		}
		/* ... gather info about the next VM region */
		curr_entry = next_entry;
		curr_map = next_map;	/* still locked ... */
		curr_address = next_address;
		curr_skip = next_skip;
		curr_offset = next_offset;
		curr_depth = next_depth;
		curr_max_above = next_max_above;
		curr_max_below = next_max_below;
	} else {
		/* we won't need "next_entry" after all */
		if (next_entry != NULL) {
			/* release "next_map" */
			if (next_map != curr_map && not_in_kdp) {
				vm_map_unlock_read(next_map);
			}
		}
	}
	next_entry = NULL;
	next_map = NULL;
	next_offset = 0;
	next_skip = 0;
	next_depth = 0;
	next_max_below = -1;
	next_max_above = -1;

	if (curr_entry->is_sub_map &&
	    curr_depth < user_max_depth) {
		/*
		 * We're not as deep as we could be:  we must have
		 * gone back up after not finding anything mapped
		 * below the original top-level map entry's.
		 * Let's move "curr_address" forward and recurse again.
		 */
		user_address = curr_address;
		goto recurse_again;
	}

	*nesting_depth = curr_depth;
	*size = curr_max_above + curr_max_below;
	*address = user_address + curr_skip - curr_max_below;

// LP64todo: all the current tools are 32bit, obviously never worked for 64b
// so probably should be a real 32b ID vs. ptr.
// Current users just check for equality
#define INFO_MAKE_OBJECT_ID(p)	((uint32_t)(uintptr_t)VM_KERNEL_ADDRPERM(p))

	if (look_for_pages) {
		submap_info->user_tag = VME_ALIAS(curr_entry);
		submap_info->offset = VME_OFFSET(curr_entry);
		submap_info->protection = curr_entry->protection;
		submap_info->inheritance = curr_entry->inheritance;
		submap_info->max_protection = curr_entry->max_protection;
		submap_info->behavior = curr_entry->behavior;
		submap_info->user_wired_count = curr_entry->user_wired_count;
		submap_info->is_submap = curr_entry->is_sub_map;
		submap_info->object_id = INFO_MAKE_OBJECT_ID(VME_OBJECT(curr_entry));
	} else {
		short_info->user_tag = VME_ALIAS(curr_entry);
		short_info->offset = VME_OFFSET(curr_entry);
		short_info->protection = curr_entry->protection;
		short_info->inheritance = curr_entry->inheritance;
		short_info->max_protection = curr_entry->max_protection;
		short_info->behavior = curr_entry->behavior;
		short_info->user_wired_count = curr_entry->user_wired_count;
		short_info->is_submap = curr_entry->is_sub_map;
		short_info->object_id = INFO_MAKE_OBJECT_ID(VME_OBJECT(curr_entry));
	}

	extended.pages_resident = 0;
	extended.pages_swapped_out = 0;
	extended.pages_shared_now_private = 0;
	extended.pages_dirtied = 0;
	extended.pages_reusable = 0;
	extended.external_pager = 0;
	extended.shadow_depth = 0;
	extended.share_mode = SM_EMPTY;
	extended.ref_count = 0;

	if (not_in_kdp) {
		if (!curr_entry->is_sub_map) {
			vm_map_offset_t range_start, range_end;
			range_start = MAX((curr_address - curr_max_below),
					  curr_entry->vme_start);
			range_end = MIN((curr_address + curr_max_above),
					curr_entry->vme_end);
			vm_map_region_walk(curr_map,
					   range_start,
					   curr_entry,
					   (VME_OFFSET(curr_entry) +
					    (range_start -
					     curr_entry->vme_start)),
					   range_end - range_start,
					   &extended,
					   look_for_pages, VM_REGION_EXTENDED_INFO_COUNT);
			if (extended.external_pager &&
			    extended.ref_count == 2 &&
			    extended.share_mode == SM_SHARED) {
				extended.share_mode = SM_PRIVATE;
			}
		} else {
			if (curr_entry->use_pmap) {
				extended.share_mode = SM_TRUESHARED;
			} else {
				extended.share_mode = SM_PRIVATE;
			}
			extended.ref_count = VME_SUBMAP(curr_entry)->map_refcnt;
		}
	}

	if (look_for_pages) {
		submap_info->pages_resident = extended.pages_resident;
		submap_info->pages_swapped_out = extended.pages_swapped_out;
		submap_info->pages_shared_now_private =
			extended.pages_shared_now_private;
		submap_info->pages_dirtied = extended.pages_dirtied;
		submap_info->external_pager = extended.external_pager;
		submap_info->shadow_depth = extended.shadow_depth;
		submap_info->share_mode = extended.share_mode;
		submap_info->ref_count = extended.ref_count;

		if (original_count >= VM_REGION_SUBMAP_INFO_V1_COUNT_64) {
			submap_info->pages_reusable = extended.pages_reusable;
		}
	} else {
		short_info->external_pager = extended.external_pager;
		short_info->shadow_depth = extended.shadow_depth;
		short_info->share_mode = extended.share_mode;
		short_info->ref_count = extended.ref_count;
	}

	if (not_in_kdp) {
		vm_map_unlock_read(curr_map);
	}

	return KERN_SUCCESS;
}