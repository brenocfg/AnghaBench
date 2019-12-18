#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_object_t ;
struct TYPE_14__ {int ref_count; scalar_t__ res_count; int /*<<< orphan*/  named; struct TYPE_14__* copy; scalar_t__ vo_shadow_offset; struct TYPE_14__* shadow; int /*<<< orphan*/  phys_contiguous; } ;

/* Variables and functions */
 TYPE_1__* VM_OBJECT_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  object_bypasses ; 
 int /*<<< orphan*/  vm_object_activity_begin (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_activity_end (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_deallocate (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_lock_assert_exclusive (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_reference (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_res_deallocate (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_res_reference (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_unlock (TYPE_1__*) ; 

__attribute__((used)) static void
vm_object_do_bypass(
	vm_object_t object,
	vm_object_t backing_object)
{
	/*
	 *	Make the parent shadow the next object
	 *	in the chain.
	 */
	
	vm_object_lock_assert_exclusive(object);
	vm_object_lock_assert_exclusive(backing_object);

#if	TASK_SWAPPER
	/*
	 *	Do object reference in-line to 
	 *	conditionally increment shadow's
	 *	residence count.  If object is not
	 *	resident, leave residence count
	 *	on shadow alone.
	 */
	if (backing_object->shadow != VM_OBJECT_NULL) {
		vm_object_lock(backing_object->shadow);
		vm_object_lock_assert_exclusive(backing_object->shadow);
		backing_object->shadow->ref_count++;
		if (object->res_count != 0)
			vm_object_res_reference(backing_object->shadow);
		vm_object_unlock(backing_object->shadow);
	}
#else	/* TASK_SWAPPER */
	vm_object_reference(backing_object->shadow);
#endif	/* TASK_SWAPPER */

	assert(!object->phys_contiguous);
	assert(!backing_object->phys_contiguous);
	object->shadow = backing_object->shadow;
	if (object->shadow) {
		object->vo_shadow_offset += backing_object->vo_shadow_offset;
	} else {
		/* no shadow, therefore no shadow offset... */
		object->vo_shadow_offset = 0;
	}
	
	/*
	 *	Backing object might have had a copy pointer
	 *	to us.  If it did, clear it. 
	 */
	if (backing_object->copy == object) {
		backing_object->copy = VM_OBJECT_NULL;
	}
	
	/*
	 *	Drop the reference count on backing_object.
#if	TASK_SWAPPER
	 *	Since its ref_count was at least 2, it
	 *	will not vanish; so we don't need to call
	 *	vm_object_deallocate.
	 *	[with a caveat for "named" objects]
	 * 
	 *	The res_count on the backing object is
	 *	conditionally decremented.  It's possible
	 *	(via vm_pageout_scan) to get here with
	 *	a "swapped" object, which has a 0 res_count,
	 *	in which case, the backing object res_count
	 *	is already down by one.
#else
	 *	Don't call vm_object_deallocate unless
	 *	ref_count drops to zero.
	 *
	 *	The ref_count can drop to zero here if the
	 *	backing object could be bypassed but not
	 *	collapsed, such as when the backing object
	 *	is temporary and cachable.
#endif
	 */
	if (backing_object->ref_count > 2 ||
	    (!backing_object->named && backing_object->ref_count > 1)) {
		vm_object_lock_assert_exclusive(backing_object);
		backing_object->ref_count--;
#if	TASK_SWAPPER
		if (object->res_count != 0)
			vm_object_res_deallocate(backing_object);
		assert(backing_object->ref_count > 0);
#endif	/* TASK_SWAPPER */
		vm_object_unlock(backing_object);
	} else {

		/*
		 *	Drop locks so that we can deallocate
		 *	the backing object.
		 */

#if	TASK_SWAPPER
		if (object->res_count == 0) {
			/* XXX get a reference for the deallocate below */
			vm_object_res_reference(backing_object);
		}
#endif	/* TASK_SWAPPER */
		/*
		 * vm_object_collapse (the caller of this function) is
		 * now called from contexts that may not guarantee that a
		 * valid reference is held on the object... w/o a valid
		 * reference, it is unsafe and unwise (you will definitely
		 * regret it) to unlock the object and then retake the lock
		 * since the object may be terminated and recycled in between.
		 * The "activity_in_progress" reference will keep the object
		 * 'stable'.
		 */
		vm_object_activity_begin(object);
		vm_object_unlock(object);

		vm_object_unlock(backing_object);
		vm_object_deallocate(backing_object);

		/*
		 *	Relock object. We don't have to reverify
		 *	its state since vm_object_collapse will
		 *	do that for us as it starts at the
		 *	top of its loop.
		 */

		vm_object_lock(object);
		vm_object_activity_end(object);
	}
	
	object_bypasses++;
}