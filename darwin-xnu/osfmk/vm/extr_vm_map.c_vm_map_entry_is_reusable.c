#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_object_t ;
typedef  TYPE_2__* vm_map_entry_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_9__ {scalar_t__ protection; scalar_t__ max_protection; scalar_t__ inheritance; scalar_t__ superpage_size; scalar_t__ wired_count; scalar_t__ user_wired_count; scalar_t__ zero_wired_pages; scalar_t__ permanent; scalar_t__ no_cache; scalar_t__ in_transition; scalar_t__ is_sub_map; } ;
struct TYPE_8__ {int ref_count; scalar_t__ wired_page_count; scalar_t__ purgable; scalar_t__ copy_strategy; scalar_t__ wimg_bits; int /*<<< orphan*/  code_signed; int /*<<< orphan*/  true_share; scalar_t__ internal; struct TYPE_8__* shadow; struct TYPE_8__* copy; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ MEMORY_OBJECT_COPY_DELAY ; 
 scalar_t__ TRUE ; 
 int VME_ALIAS (TYPE_2__*) ; 
 TYPE_1__* VME_OBJECT (TYPE_2__*) ; 
 scalar_t__ VM_INHERIT_DEFAULT ; 
#define  VM_MEMORY_MALLOC 134 
#define  VM_MEMORY_MALLOC_LARGE 133 
#define  VM_MEMORY_MALLOC_LARGE_REUSABLE 132 
#define  VM_MEMORY_MALLOC_LARGE_REUSED 131 
#define  VM_MEMORY_MALLOC_SMALL 130 
#define  VM_MEMORY_MALLOC_TINY 129 
#define  VM_MEMORY_REALLOC 128 
 TYPE_1__* VM_OBJECT_NULL ; 
 scalar_t__ VM_PROT_ALL ; 
 scalar_t__ VM_PROT_DEFAULT ; 
 scalar_t__ VM_PURGABLE_DENY ; 
 scalar_t__ VM_WIMG_USE_DEFAULT ; 

__attribute__((used)) static boolean_t
vm_map_entry_is_reusable(
	vm_map_entry_t entry)
{
	/* Only user map entries */

	vm_object_t object;

	if (entry->is_sub_map) {
		return FALSE;
	}

	switch (VME_ALIAS(entry)) {
	case VM_MEMORY_MALLOC:
	case VM_MEMORY_MALLOC_SMALL:
	case VM_MEMORY_MALLOC_LARGE:
	case VM_MEMORY_REALLOC:
	case VM_MEMORY_MALLOC_TINY:
	case VM_MEMORY_MALLOC_LARGE_REUSABLE:
	case VM_MEMORY_MALLOC_LARGE_REUSED:
		/*
		 * This is a malloc() memory region: check if it's still
		 * in its original state and can be re-used for more
		 * malloc() allocations.
		 */
		break;
	default:
		/*
		 * Not a malloc() memory region: let the caller decide if
		 * it's re-usable.
		 */
		return TRUE;
	}

	if (/*entry->is_shared ||*/
	    entry->is_sub_map ||
	    entry->in_transition ||
	    entry->protection != VM_PROT_DEFAULT ||
	    entry->max_protection != VM_PROT_ALL ||
	    entry->inheritance != VM_INHERIT_DEFAULT ||
	    entry->no_cache ||
	    entry->permanent ||
	    entry->superpage_size != FALSE ||
	    entry->zero_wired_pages ||
	    entry->wired_count != 0 ||
	    entry->user_wired_count != 0) {
		return FALSE;
	}

	object = VME_OBJECT(entry);
	if (object == VM_OBJECT_NULL) {
		return TRUE;
	}
	if (
#if 0
		/*
		 * Let's proceed even if the VM object is potentially
		 * shared.
		 * We check for this later when processing the actual
		 * VM pages, so the contents will be safe if shared.
		 *
		 * But we can still mark this memory region as "reusable" to
		 * acknowledge that the caller did let us know that the memory
		 * could be re-used and should not be penalized for holding
		 * on to it.  This allows its "resident size" to not include
		 * the reusable range.
		 */
	    object->ref_count == 1 &&
#endif
	    object->wired_page_count == 0 &&
	    object->copy == VM_OBJECT_NULL &&
	    object->shadow == VM_OBJECT_NULL &&
	    object->internal &&
	    object->purgable == VM_PURGABLE_DENY &&
	    object->copy_strategy != MEMORY_OBJECT_COPY_DELAY &&
	    !object->true_share &&
	    object->wimg_bits == VM_WIMG_USE_DEFAULT &&
	    !object->code_signed) {
		return TRUE;
	}
	return FALSE;


}