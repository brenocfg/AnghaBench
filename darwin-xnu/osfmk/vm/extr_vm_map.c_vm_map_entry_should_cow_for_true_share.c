#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_object_t ;
typedef  TYPE_2__* vm_map_entry_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_11__ {int /*<<< orphan*/  should_cow_but_wired; } ;
struct TYPE_10__ {scalar_t__ wired_count; scalar_t__ needs_copy; scalar_t__ is_sub_map; } ;
struct TYPE_9__ {scalar_t__ copy_strategy; int vo_size; scalar_t__ true_share; int /*<<< orphan*/  internal; } ;

/* Variables and functions */
 int ANON_CHUNK_SIZE ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MEMORY_OBJECT_COPY_SYMMETRIC ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ VME_ALIAS (TYPE_2__*) ; 
 TYPE_1__* VME_OBJECT (TYPE_2__*) ; 
 scalar_t__ VM_MEMORY_MALLOC ; 
 scalar_t__ VM_MEMORY_MALLOC_SMALL ; 
 TYPE_1__* VM_OBJECT_NULL ; 
 TYPE_4__ vm_counters ; 

boolean_t
vm_map_entry_should_cow_for_true_share(
	vm_map_entry_t	entry)
{
	vm_object_t	object;

	if (entry->is_sub_map) {
		/* entry does not point at a VM object */
		return FALSE;
	}

	if (entry->needs_copy) {
		/* already set for copy_on_write: done! */
		return FALSE;
	}

	if (VME_ALIAS(entry) != VM_MEMORY_MALLOC &&
	    VME_ALIAS(entry) != VM_MEMORY_MALLOC_SMALL) {
		/* not a malloc heap or Obj-C Garbage Collector heap */
		return FALSE;
	}

	if (entry->wired_count) {
		/* wired: can't change the map entry... */
		vm_counters.should_cow_but_wired++;
		return FALSE;
	}

	object = VME_OBJECT(entry);

	if (object == VM_OBJECT_NULL) {
		/* no object yet... */
		return FALSE;
	}

	if (!object->internal) {
		/* not an internal object */
		return FALSE;
	}

	if (object->copy_strategy != MEMORY_OBJECT_COPY_SYMMETRIC) {
		/* not the default copy strategy */
		return FALSE;
	}

	if (object->true_share) {
		/* already true_share: too late to avoid it */
		return FALSE;
	}

	if (VME_ALIAS(entry) == VM_MEMORY_MALLOC &&
	    object->vo_size != ANON_CHUNK_SIZE) {
		/* ... not an object created for the ObjC Garbage Collector */
		return FALSE;
	}

	if (VME_ALIAS(entry) == VM_MEMORY_MALLOC_SMALL &&
	    object->vo_size != 2048 * 4096) {
		/* ... not a "MALLOC_SMALL" heap */
		return FALSE;
	}

	/*
	 * All the criteria match: we have a large object being targeted for "true_share".
	 * To limit the adverse side-effects linked with "true_share", tell the caller to
	 * try and avoid setting up the entire object for "true_share" by clipping the
	 * targeted range and setting it up for copy-on-write.
	 */
	return TRUE;
}