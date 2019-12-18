#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_15__ ;

/* Type definitions */
typedef  TYPE_1__* vm_region_extended_info_t ;
typedef  struct vm_object* vm_object_t ;
typedef  int vm_object_size_t ;
typedef  scalar_t__ vm_object_offset_t ;
typedef  TYPE_2__* vm_map_t ;
typedef  scalar_t__ vm_map_offset_t ;
typedef  TYPE_3__* vm_map_entry_t ;
struct vm_object {int ref_count; scalar_t__ purgable; scalar_t__ resident_page_count; scalar_t__ wired_page_count; scalar_t__ paging_in_progress; struct vm_object* shadow; scalar_t__ true_share; int /*<<< orphan*/  internal; int /*<<< orphan*/  pager_trusted; int /*<<< orphan*/  pager; scalar_t__ phys_contiguous; } ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_21__ {scalar_t__ vme_start; struct TYPE_21__* vme_next; scalar_t__ needs_copy; scalar_t__ iokit_acct; scalar_t__ superpage_size; scalar_t__ is_sub_map; } ;
struct TYPE_20__ {int /*<<< orphan*/  pmap; scalar_t__ has_corpse_footprint; } ;
struct TYPE_19__ {scalar_t__ share_mode; int ref_count; int shadow_depth; int external_pager; unsigned int pages_resident; int /*<<< orphan*/  pages_dirtied; int /*<<< orphan*/  pages_swapped_out; int /*<<< orphan*/  pages_reusable; } ;
struct TYPE_18__ {TYPE_2__* map; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ PAGE_SIZE_64 ; 
 int PMAP_QUERY_PAGE_ALTACCT ; 
 int PMAP_QUERY_PAGE_COMPRESSED ; 
 int PMAP_QUERY_PAGE_COMPRESSED_ALTACCT ; 
 int PMAP_QUERY_PAGE_INTERNAL ; 
 int PMAP_QUERY_PAGE_PRESENT ; 
 int PMAP_QUERY_PAGE_REUSABLE ; 
 scalar_t__ SM_COW ; 
 scalar_t__ SM_EMPTY ; 
 scalar_t__ SM_LARGE_PAGE ; 
 scalar_t__ SM_PRIVATE ; 
 scalar_t__ SM_PRIVATE_ALIASED ; 
 scalar_t__ SM_SHARED ; 
 scalar_t__ SM_SHARED_ALIASED ; 
 scalar_t__ SM_TRUESHARED ; 
 struct vm_object* VME_OBJECT (TYPE_3__*) ; 
 scalar_t__ VME_OFFSET (TYPE_3__*) ; 
 struct vm_object* VM_OBJECT_NULL ; 
 TYPE_15__* VM_OBJECT_OWNER (struct vm_object*) ; 
 scalar_t__ VM_PURGABLE_DENY ; 
 scalar_t__ VM_PURGABLE_EMPTY ; 
 scalar_t__ VM_PURGABLE_NONVOLATILE ; 
 scalar_t__ VM_PURGABLE_VOLATILE ; 
 int /*<<< orphan*/  pmap_query_page_info (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 scalar_t__ task_self_region_footprint () ; 
 scalar_t__ vm_compressor_pager_get_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_corpse_footprint_query_page_info (TYPE_2__*,scalar_t__,int*) ; 
 TYPE_3__* vm_map_first_entry (TYPE_2__*) ; 
 scalar_t__ vm_map_region_count_obj_refs (TYPE_3__*,struct vm_object*) ; 
 int /*<<< orphan*/  vm_map_region_look_for_page (TYPE_2__*,scalar_t__,struct vm_object*,scalar_t__,int,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* vm_map_to_entry (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_lock (struct vm_object*) ; 
 int /*<<< orphan*/  vm_object_unlock (struct vm_object*) ; 

void
vm_map_region_walk(
	vm_map_t		   	map,
	vm_map_offset_t			va,
	vm_map_entry_t			entry,
	vm_object_offset_t		offset,
	vm_object_size_t		range,
	vm_region_extended_info_t	extended,
	boolean_t			look_for_pages,
	mach_msg_type_number_t count)
{
        struct vm_object *obj, *tmp_obj;
	vm_map_offset_t       last_offset;
	int               i;
	int               ref_count;
	struct vm_object	*shadow_object;
	int			shadow_depth;
	boolean_t	  do_region_footprint;

	do_region_footprint = task_self_region_footprint();

	if ((VME_OBJECT(entry) == 0) ||
	    (entry->is_sub_map) ||
	    (VME_OBJECT(entry)->phys_contiguous &&
	     !entry->superpage_size)) {
		extended->share_mode = SM_EMPTY;
		extended->ref_count = 0;
		return;
	}

	if (entry->superpage_size) {
		extended->shadow_depth = 0;
		extended->share_mode = SM_LARGE_PAGE;
		extended->ref_count = 1;
		extended->external_pager = 0;
		extended->pages_resident = (unsigned int)(range >> PAGE_SHIFT);
		extended->shadow_depth = 0;
		return;
	}

	obj = VME_OBJECT(entry);

	vm_object_lock(obj);

	if ((ref_count = obj->ref_count) > 1 && obj->paging_in_progress)
		ref_count--;

	if (look_for_pages) {
		for (last_offset = offset + range;
		     offset < last_offset;
		     offset += PAGE_SIZE_64, va += PAGE_SIZE) {

			if (do_region_footprint) {
				int disp;

				disp = 0;
				if (map->has_corpse_footprint) {
					/*
					 * Query the page info data we saved
					 * while forking the corpse.
					 */
					vm_map_corpse_footprint_query_page_info(
						map,
						va,
						&disp);
				} else {
					/*
					 * Query the pmap.
					 */
					pmap_query_page_info(map->pmap,
							     va,
							     &disp);
				}
				if (disp & PMAP_QUERY_PAGE_PRESENT) {
					if (!(disp & PMAP_QUERY_PAGE_ALTACCT)) {
						extended->pages_resident++;
					}
					if (disp & PMAP_QUERY_PAGE_REUSABLE) {
						extended->pages_reusable++;
					} else if (!(disp & PMAP_QUERY_PAGE_INTERNAL) ||
						   (disp & PMAP_QUERY_PAGE_ALTACCT)) {
						/* alternate accounting */
					} else {
						extended->pages_dirtied++;
					}
				} else if (disp & PMAP_QUERY_PAGE_COMPRESSED) {
					if (disp & PMAP_QUERY_PAGE_COMPRESSED_ALTACCT) {
						/* alternate accounting */
					} else {
						extended->pages_swapped_out++;
					}
				}
				/* deal with alternate accounting */
				if (obj->purgable == VM_PURGABLE_NONVOLATILE &&
				    /* && not tagged as no-footprint? */
				    VM_OBJECT_OWNER(obj) != NULL &&
				    VM_OBJECT_OWNER(obj)->map == map) {
					if ((((va
					       - entry->vme_start
					       + VME_OFFSET(entry))
					      / PAGE_SIZE) <
					     (obj->resident_page_count +
					      vm_compressor_pager_get_count(obj->pager)))) {
						/*
						 * Non-volatile purgeable object owned
						 * by this task: report the first
						 * "#resident + #compressed" pages as
						 * "resident" (to show that they
						 * contribute to the footprint) but not
						 * "dirty" (to avoid double-counting
						 * with the fake "non-volatile" region
						 * we'll report at the end of the
						 * address space to account for all
						 * (mapped or not) non-volatile memory
						 * owned by this task.
						 */
						extended->pages_resident++;
					}
				} else if ((obj->purgable == VM_PURGABLE_VOLATILE ||
					    obj->purgable == VM_PURGABLE_EMPTY) &&
					   /* && not tagged as no-footprint? */
					   VM_OBJECT_OWNER(obj) != NULL &&
					   VM_OBJECT_OWNER(obj)->map == map) {
					if ((((va
					       - entry->vme_start
					       + VME_OFFSET(entry))
					      / PAGE_SIZE) <
					     obj->wired_page_count)) {
						/*
						 * Volatile|empty purgeable object owned
						 * by this task: report the first
						 * "#wired" pages as "resident" (to
						 * show that they contribute to the
						 * footprint) but not "dirty" (to avoid
						 * double-counting with the fake
						 * "non-volatile" region we'll report
						 * at the end of the address space to
						 * account for all (mapped or not)
						 * non-volatile memory owned by this
						 * task.
						 */
						extended->pages_resident++;
					}
				} else if (obj->purgable != VM_PURGABLE_DENY) {
					/*
					 * Pages from purgeable objects
					 * will be reported as dirty 
					 * appropriately in an extra
					 * fake memory region at the end of
					 * the address space.
					 */
				} else if (entry->iokit_acct) {
					/*
					 * IOKit mappings are considered
					 * as fully dirty for footprint's
					 * sake.
					 */
					extended->pages_dirtied++;
				}
				continue;
			}

			vm_map_region_look_for_page(map, va, obj,
						    offset, ref_count,
						    0, extended, count);
		}

		if (do_region_footprint) {
			goto collect_object_info;
		}

	} else {
	collect_object_info:
		shadow_object = obj->shadow;
		shadow_depth = 0;

		if ( !(obj->pager_trusted) && !(obj->internal))
			extended->external_pager = 1;

		if (shadow_object != VM_OBJECT_NULL) {
			vm_object_lock(shadow_object);
			for (;
			     shadow_object != VM_OBJECT_NULL;
			     shadow_depth++) {
				vm_object_t	next_shadow;

				if ( !(shadow_object->pager_trusted) &&
				     !(shadow_object->internal))
					extended->external_pager = 1;

				next_shadow = shadow_object->shadow;
				if (next_shadow) {
					vm_object_lock(next_shadow);
				}
				vm_object_unlock(shadow_object);
				shadow_object = next_shadow;
			}
		}
		extended->shadow_depth = shadow_depth;
	}

	if (extended->shadow_depth || entry->needs_copy)
		extended->share_mode = SM_COW;
	else {
		if (ref_count == 1)
			extended->share_mode = SM_PRIVATE;
		else {
			if (obj->true_share)
				extended->share_mode = SM_TRUESHARED;
			else
				extended->share_mode = SM_SHARED;
		}
	}
	extended->ref_count = ref_count - extended->shadow_depth;

	for (i = 0; i < extended->shadow_depth; i++) {
		if ((tmp_obj = obj->shadow) == 0)
			break;
		vm_object_lock(tmp_obj);
		vm_object_unlock(obj);

		if ((ref_count = tmp_obj->ref_count) > 1 && tmp_obj->paging_in_progress)
			ref_count--;

		extended->ref_count += ref_count;
		obj = tmp_obj;
	}
	vm_object_unlock(obj);

	if (extended->share_mode == SM_SHARED) {
		vm_map_entry_t	     cur;
		vm_map_entry_t	     last;
		int      my_refs;

		obj = VME_OBJECT(entry);
		last = vm_map_to_entry(map);
		my_refs = 0;

		if ((ref_count = obj->ref_count) > 1 && obj->paging_in_progress)
			ref_count--;
		for (cur = vm_map_first_entry(map); cur != last; cur = cur->vme_next)
			my_refs += vm_map_region_count_obj_refs(cur, obj);

		if (my_refs == ref_count)
			extended->share_mode = SM_PRIVATE_ALIASED;
		else if (my_refs > 1)
			extended->share_mode = SM_SHARED_ALIASED;
	}
}