#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_map_t ;
typedef  TYPE_2__* vm_map_entry_t ;
struct TYPE_22__ {scalar_t__ vme_end; scalar_t__ vme_start; scalar_t__ is_sub_map; scalar_t__ behavior; scalar_t__ needs_copy; scalar_t__ protection; scalar_t__ max_protection; scalar_t__ inheritance; scalar_t__ use_pmap; scalar_t__ no_cache; scalar_t__ permanent; scalar_t__ map_aligned; scalar_t__ zero_wired_pages; scalar_t__ used_for_jit; scalar_t__ pmap_cs_associated; scalar_t__ iokit_acct; scalar_t__ vme_resilient_codesign; scalar_t__ vme_resilient_media; scalar_t__ wired_count; scalar_t__ user_wired_count; scalar_t__ vme_atomic; scalar_t__ in_transition; scalar_t__ needs_wakeup; scalar_t__ is_shared; scalar_t__ superpage_size; struct TYPE_22__* vme_prev; } ;
struct TYPE_21__ {scalar_t__ holelistenabled; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SAVE_HINT_MAP_WRITE (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ VME_ALIAS (TYPE_2__*) ; 
 scalar_t__ VME_OBJECT (TYPE_2__*) ; 
 scalar_t__ VME_OFFSET (TYPE_2__*) ; 
 int /*<<< orphan*/  VME_OFFSET_SET (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  VME_SUBMAP (TYPE_2__*) ; 
 int VM_MAP_PAGE_ALIGNED (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_MAP_PAGE_MASK (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  c_vm_map_simplified ; 
 int /*<<< orphan*/  c_vm_map_simplify_entry_called ; 
 int /*<<< orphan*/  counter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_deallocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_entry_dispose (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_store_entry_unlink (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_store_update_first_free (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* vm_map_to_entry (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_deallocate (scalar_t__) ; 

void
vm_map_simplify_entry(
	vm_map_t	map,
	vm_map_entry_t	this_entry)
{
	vm_map_entry_t	prev_entry;

	counter(c_vm_map_simplify_entry_called++);

	prev_entry = this_entry->vme_prev;

	if ((this_entry != vm_map_to_entry(map)) &&
	    (prev_entry != vm_map_to_entry(map)) &&

	    (prev_entry->vme_end == this_entry->vme_start) &&

	    (prev_entry->is_sub_map == this_entry->is_sub_map) &&
	    (VME_OBJECT(prev_entry) == VME_OBJECT(this_entry)) &&
	    ((VME_OFFSET(prev_entry) + (prev_entry->vme_end -
				    prev_entry->vme_start))
	     == VME_OFFSET(this_entry)) &&

	    (prev_entry->behavior == this_entry->behavior) &&
	    (prev_entry->needs_copy == this_entry->needs_copy) &&
	    (prev_entry->protection == this_entry->protection) &&
	    (prev_entry->max_protection == this_entry->max_protection) &&
	    (prev_entry->inheritance == this_entry->inheritance) &&
	    (prev_entry->use_pmap == this_entry->use_pmap) &&
	    (VME_ALIAS(prev_entry) == VME_ALIAS(this_entry)) &&
	    (prev_entry->no_cache == this_entry->no_cache) &&
	    (prev_entry->permanent == this_entry->permanent) &&
	    (prev_entry->map_aligned == this_entry->map_aligned) &&
	    (prev_entry->zero_wired_pages == this_entry->zero_wired_pages) &&
	    (prev_entry->used_for_jit == this_entry->used_for_jit) &&
	    (prev_entry->pmap_cs_associated == this_entry->pmap_cs_associated) &&
	    /* from_reserved_zone: OK if that field doesn't match */
	    (prev_entry->iokit_acct == this_entry->iokit_acct) &&
	    (prev_entry->vme_resilient_codesign ==
	     this_entry->vme_resilient_codesign) &&
	    (prev_entry->vme_resilient_media ==
	     this_entry->vme_resilient_media) &&

	    (prev_entry->wired_count == this_entry->wired_count) &&
	    (prev_entry->user_wired_count == this_entry->user_wired_count) &&

	    ((prev_entry->vme_atomic == FALSE) && (this_entry->vme_atomic == FALSE)) &&
	    (prev_entry->in_transition == FALSE) &&
	    (this_entry->in_transition == FALSE) &&
	    (prev_entry->needs_wakeup == FALSE) &&
	    (this_entry->needs_wakeup == FALSE) &&
	    (prev_entry->is_shared == FALSE) &&
	    (this_entry->is_shared == FALSE) &&
	    (prev_entry->superpage_size == FALSE) &&
	    (this_entry->superpage_size == FALSE)
		) {
		vm_map_store_entry_unlink(map, prev_entry);
		assert(prev_entry->vme_start < this_entry->vme_end);
		if (prev_entry->map_aligned)
			assert(VM_MAP_PAGE_ALIGNED(prev_entry->vme_start,
						   VM_MAP_PAGE_MASK(map)));
		this_entry->vme_start = prev_entry->vme_start;
		VME_OFFSET_SET(this_entry, VME_OFFSET(prev_entry));

		if (map->holelistenabled) {
			vm_map_store_update_first_free(map, this_entry, TRUE);
		}

		if (prev_entry->is_sub_map) {
			vm_map_deallocate(VME_SUBMAP(prev_entry));
		} else {
			vm_object_deallocate(VME_OBJECT(prev_entry));
		}
		vm_map_entry_dispose(map, prev_entry);
		SAVE_HINT_MAP_WRITE(map, this_entry);
		counter(c_vm_map_simplified++);
	}
}