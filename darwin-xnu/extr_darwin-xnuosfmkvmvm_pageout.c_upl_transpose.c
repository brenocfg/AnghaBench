#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* vm_object_t ;
typedef  int /*<<< orphan*/  vm_object_size_t ;
typedef  TYPE_1__* upl_t ;
typedef  scalar_t__ kern_return_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_7__ {int flags; scalar_t__ offset; scalar_t__ size; void* map_object; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ KERN_INVALID_ARGUMENT ; 
 scalar_t__ KERN_INVALID_VALUE ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ TRUE ; 
 TYPE_1__* UPL_NULL ; 
 int UPL_VECTOR ; 
 int /*<<< orphan*/  upl_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  upl_unlock (TYPE_1__*) ; 
 scalar_t__ vm_object_transpose (void*,void*,int /*<<< orphan*/ ) ; 

kern_return_t
upl_transpose(
	upl_t		upl1,
	upl_t		upl2)
{
	kern_return_t		retval;
	boolean_t		upls_locked;
	vm_object_t		object1, object2;

	if (upl1 == UPL_NULL || upl2 == UPL_NULL || upl1 == upl2  || ((upl1->flags & UPL_VECTOR)==UPL_VECTOR)  || ((upl2->flags & UPL_VECTOR)==UPL_VECTOR)) {
		return KERN_INVALID_ARGUMENT;
	}

	upls_locked = FALSE;

	/*
	 * Since we need to lock both UPLs at the same time,
	 * avoid deadlocks by always taking locks in the same order.
	 */
	if (upl1 < upl2) {
		upl_lock(upl1);
		upl_lock(upl2);
	} else {
		upl_lock(upl2);
		upl_lock(upl1);
	}
	upls_locked = TRUE;	/* the UPLs will need to be unlocked */

	object1 = upl1->map_object;
	object2 = upl2->map_object;

	if (upl1->offset != 0 || upl2->offset != 0 ||
	    upl1->size != upl2->size) {
		/*
		 * We deal only with full objects, not subsets.
		 * That's because we exchange the entire backing store info
		 * for the objects: pager, resident pages, etc...  We can't do
		 * only part of it.
		 */
		retval = KERN_INVALID_VALUE;
		goto done;
	}

	/*
	 * Tranpose the VM objects' backing store.
	 */
	retval = vm_object_transpose(object1, object2,
				     (vm_object_size_t) upl1->size);

	if (retval == KERN_SUCCESS) {
		/*
		 * Make each UPL point to the correct VM object, i.e. the
		 * object holding the pages that the UPL refers to...
		 */
#if CONFIG_IOSCHED || UPL_DEBUG
		if ((upl1->flags & UPL_TRACKED_BY_OBJECT) || (upl2->flags & UPL_TRACKED_BY_OBJECT)) {
			vm_object_lock(object1);
			vm_object_lock(object2);
		}
		if (upl1->flags & UPL_TRACKED_BY_OBJECT)
			queue_remove(&object1->uplq, upl1, upl_t, uplq);
		if (upl2->flags & UPL_TRACKED_BY_OBJECT)
			queue_remove(&object2->uplq, upl2, upl_t, uplq);
#endif
		upl1->map_object = object2;
		upl2->map_object = object1;

#if CONFIG_IOSCHED || UPL_DEBUG
		if (upl1->flags & UPL_TRACKED_BY_OBJECT)
			queue_enter(&object2->uplq, upl1, upl_t, uplq);
		if (upl2->flags & UPL_TRACKED_BY_OBJECT)
			queue_enter(&object1->uplq, upl2, upl_t, uplq);
		if ((upl1->flags & UPL_TRACKED_BY_OBJECT) || (upl2->flags & UPL_TRACKED_BY_OBJECT)) {
			vm_object_unlock(object2);
			vm_object_unlock(object1);
		}
#endif
	}

done:
	/*
	 * Cleanup.
	 */
	if (upls_locked) {
		upl_unlock(upl1);
		upl_unlock(upl2);
		upls_locked = FALSE;
	}

	return retval;
}