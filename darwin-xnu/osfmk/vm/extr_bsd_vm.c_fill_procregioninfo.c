#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_13__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  obj_id; scalar_t__ shared_pages_resident; void* private_pages_resident; } ;
typedef  TYPE_1__ vm_region_top_info_data_t ;
struct TYPE_20__ {int ref_count; scalar_t__ share_mode; scalar_t__ shadow_depth; void* pages_dirtied; void* pages_swapped_out; scalar_t__ pages_shared_now_private; void* pages_resident; scalar_t__ external_pager; void* user_tag; void* protection; } ;
typedef  TYPE_2__ vm_region_extended_info_data_t ;
typedef  scalar_t__ vm_map_t ;
typedef  scalar_t__ vm_map_offset_t ;
typedef  TYPE_3__* vm_map_entry_t ;
typedef  void* uint64_t ;
typedef  void* uint32_t ;
typedef  TYPE_4__* task_t ;
struct proc_regioninfo_internal {int pri_user_tag; int pri_ref_count; scalar_t__ pri_share_mode; scalar_t__ pri_depth; void* pri_size; void* pri_address; int /*<<< orphan*/  pri_obj_id; scalar_t__ pri_shared_pages_resident; void* pri_private_pages_resident; scalar_t__ pri_shadow_depth; void* pri_pages_dirtied; void* pri_pages_swapped_out; scalar_t__ pri_pages_shared_now_private; void* pri_pages_resident; int /*<<< orphan*/  pri_flags; int /*<<< orphan*/  pri_user_wired_count; int /*<<< orphan*/  pri_behavior; int /*<<< orphan*/  pri_inheritance; void* pri_max_protection; void* pri_protection; scalar_t__ pri_offset; } ;
typedef  int ledger_amount_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_22__ {scalar_t__ map; int /*<<< orphan*/  ledger; } ;
struct TYPE_21__ {scalar_t__ vme_end; scalar_t__ vme_start; scalar_t__ is_sub_map; void* protection; scalar_t__ is_shared; int /*<<< orphan*/  user_wired_count; int /*<<< orphan*/  behavior; int /*<<< orphan*/  inheritance; void* max_protection; struct TYPE_21__* vme_next; } ;
struct TYPE_18__ {int /*<<< orphan*/  purgeable_nonvolatile; int /*<<< orphan*/  purgeable_nonvolatile_compressed; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFO_MAKE_FAKE_OBJECT_ID (scalar_t__,int /*<<< orphan*/ ) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PROC_REGION_SHARED ; 
 int /*<<< orphan*/  PROC_REGION_SUBMAP ; 
 void* SM_PRIVATE ; 
 scalar_t__ SM_SHARED ; 
 int /*<<< orphan*/  TRUE ; 
 void* VME_ALIAS (TYPE_3__*) ; 
 scalar_t__ VME_OFFSET (TYPE_3__*) ; 
 int /*<<< orphan*/  VM_BEHAVIOR_DEFAULT ; 
 int /*<<< orphan*/  VM_INHERIT_NONE ; 
 scalar_t__ VM_MAP_NULL ; 
 void* VM_PROT_DEFAULT ; 
 int /*<<< orphan*/  VM_REGION_EXTENDED_INFO_COUNT ; 
 scalar_t__ fill_vnodeinfoforaddr (TYPE_3__*,uintptr_t*,void**) ; 
 int /*<<< orphan*/  ledger_get_balance (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 TYPE_13__ task_ledgers ; 
 int /*<<< orphan*/  task_lock (TYPE_4__*) ; 
 scalar_t__ task_self_region_footprint () ; 
 int /*<<< orphan*/  task_unlock (TYPE_4__*) ; 
 int /*<<< orphan*/  vm_map_deallocate (scalar_t__) ; 
 int /*<<< orphan*/  vm_map_lock_read (scalar_t__) ; 
 int /*<<< orphan*/  vm_map_lookup_entry (scalar_t__,scalar_t__,TYPE_3__**) ; 
 int /*<<< orphan*/  vm_map_reference (scalar_t__) ; 
 int /*<<< orphan*/  vm_map_region_top_walk (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_region_walk (scalar_t__,scalar_t__,TYPE_3__*,scalar_t__,scalar_t__,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* vm_map_to_entry (scalar_t__) ; 
 int /*<<< orphan*/  vm_map_unlock_read (scalar_t__) ; 

int
fill_procregioninfo(task_t task, uint64_t arg, struct proc_regioninfo_internal *pinfo, uintptr_t *vnodeaddr, uint32_t  *vid)
{

	vm_map_t map;
	vm_map_offset_t	address = (vm_map_offset_t )arg;
	vm_map_entry_t		tmp_entry;
	vm_map_entry_t		entry;
	vm_map_offset_t		start;
	vm_region_extended_info_data_t extended;
	vm_region_top_info_data_t top;
	boolean_t do_region_footprint;

	    task_lock(task);
	    map = task->map;
	    if (map == VM_MAP_NULL) 
	    {
			task_unlock(task);
			return(0);
	    }
	    vm_map_reference(map); 
	    task_unlock(task);

	    do_region_footprint = task_self_region_footprint();

	    vm_map_lock_read(map);

	    start = address;

	    if (!vm_map_lookup_entry(map, start, &tmp_entry)) {
		if ((entry = tmp_entry->vme_next) == vm_map_to_entry(map)) {
			if (do_region_footprint &&
			    address == tmp_entry->vme_end) {
				ledger_amount_t nonvol, nonvol_compressed;

				/*
				 * This request is right after the last valid
				 * memory region;  instead of reporting the
				 * end of the address space, report a fake
				 * memory region to account for non-volatile
				 * purgeable memory owned by this task.
				 */

				ledger_get_balance(
					task->ledger,
					task_ledgers.purgeable_nonvolatile,
					&nonvol);
				ledger_get_balance(
					task->ledger,
					task_ledgers.purgeable_nonvolatile_compressed,
					&nonvol_compressed);
				if (nonvol + nonvol_compressed == 0) {
					/* nothing to report */
					vm_map_unlock_read(map);
					vm_map_deallocate(map);
					return 0;
				}
				/* provide fake region for purgeable */
				pinfo->pri_offset = address;
				pinfo->pri_protection = VM_PROT_DEFAULT;
				pinfo->pri_max_protection = VM_PROT_DEFAULT;
				pinfo->pri_inheritance = VM_INHERIT_NONE;
				pinfo->pri_behavior = VM_BEHAVIOR_DEFAULT;
				pinfo->pri_user_wired_count = 0;
				pinfo->pri_user_tag = -1;
				pinfo->pri_pages_resident =
					(uint32_t) (nonvol / PAGE_SIZE);
				pinfo->pri_pages_shared_now_private = 0;
				pinfo->pri_pages_swapped_out =
					(uint32_t) (nonvol_compressed / PAGE_SIZE);
				pinfo->pri_pages_dirtied =
					(uint32_t) (nonvol / PAGE_SIZE);
				pinfo->pri_ref_count = 1;
				pinfo->pri_shadow_depth = 0;
				pinfo->pri_share_mode = SM_PRIVATE;
				pinfo->pri_private_pages_resident =
					(uint32_t) (nonvol / PAGE_SIZE);
				pinfo->pri_shared_pages_resident = 0;
				pinfo->pri_obj_id = INFO_MAKE_FAKE_OBJECT_ID(map, task_ledgers.purgeable_nonvolatile);
				pinfo->pri_address = address;
				pinfo->pri_size =
					(uint64_t) (nonvol + nonvol_compressed);
				pinfo->pri_depth = 0;

				vm_map_unlock_read(map);
				vm_map_deallocate(map);
				return 1;
			}
			vm_map_unlock_read(map);
			vm_map_deallocate(map);
			return 0;
		}
	    } else {
		entry = tmp_entry;
	    }

	    start = entry->vme_start;

	    pinfo->pri_offset = VME_OFFSET(entry);
	    pinfo->pri_protection = entry->protection;
	    pinfo->pri_max_protection = entry->max_protection;
	    pinfo->pri_inheritance = entry->inheritance;
	    pinfo->pri_behavior = entry->behavior;
	    pinfo->pri_user_wired_count = entry->user_wired_count;
	    pinfo->pri_user_tag = VME_ALIAS(entry);

	    if (entry->is_sub_map) {
		pinfo->pri_flags |= PROC_REGION_SUBMAP;
	    } else {
		if (entry->is_shared)
			pinfo->pri_flags |= PROC_REGION_SHARED;
	    }


	    extended.protection = entry->protection;
	    extended.user_tag = VME_ALIAS(entry);
	    extended.pages_resident = 0;
	    extended.pages_swapped_out = 0;
	    extended.pages_shared_now_private = 0;
	    extended.pages_dirtied = 0;
	    extended.external_pager = 0;
	    extended.shadow_depth = 0;

	    vm_map_region_walk(map, start, entry, VME_OFFSET(entry), entry->vme_end - start, &extended, TRUE, VM_REGION_EXTENDED_INFO_COUNT);

	    if (extended.external_pager && extended.ref_count == 2 && extended.share_mode == SM_SHARED)
	            extended.share_mode = SM_PRIVATE;

	    top.private_pages_resident = 0;
	    top.shared_pages_resident = 0;
	    vm_map_region_top_walk(entry, &top);

	
	    pinfo->pri_pages_resident = extended.pages_resident;
	    pinfo->pri_pages_shared_now_private = extended.pages_shared_now_private;
	    pinfo->pri_pages_swapped_out = extended.pages_swapped_out;
	    pinfo->pri_pages_dirtied = extended.pages_dirtied;
	    pinfo->pri_ref_count = extended.ref_count;
	    pinfo->pri_shadow_depth = extended.shadow_depth;
	    pinfo->pri_share_mode = extended.share_mode;

	    pinfo->pri_private_pages_resident = top.private_pages_resident;
	    pinfo->pri_shared_pages_resident = top.shared_pages_resident;
	    pinfo->pri_obj_id = top.obj_id;
		
	    pinfo->pri_address = (uint64_t)start;
	    pinfo->pri_size = (uint64_t)(entry->vme_end - start);
	    pinfo->pri_depth = 0;
	
	    if ((vnodeaddr != 0) && (entry->is_sub_map == 0)) {
		*vnodeaddr = (uintptr_t)0;

		if (fill_vnodeinfoforaddr(entry, vnodeaddr, vid) ==0) {
			vm_map_unlock_read(map);
	    		vm_map_deallocate(map); 
			return(1);
		}
	    }

	    vm_map_unlock_read(map);
	    vm_map_deallocate(map); 
	    return(1);
}