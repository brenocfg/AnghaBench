#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_object_t ;
typedef  scalar_t__ vm_object_size_t ;
typedef  scalar_t__ vm_object_offset_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ kern_return_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_10__ {scalar_t__ copy; scalar_t__ vo_size; int /*<<< orphan*/  pager_ready; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ KERN_FAILURE ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  THREAD_UNINT ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VM_OBJECT_EVENT_COPY_CALL ; 
 int /*<<< orphan*/  VM_OBJECT_EVENT_PAGER_READY ; 
 scalar_t__ VM_OBJECT_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  copy_call_count ; 
 int /*<<< orphan*/  copy_call_restart_count ; 
 int /*<<< orphan*/  copy_call_sleep_count ; 
 int /*<<< orphan*/  mutex_pause (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_lock_try (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_set_wanted (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_sleep (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_unlock (TYPE_1__*) ; 
 scalar_t__ vm_object_wanted (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static kern_return_t
vm_object_copy_call(
	vm_object_t		src_object,
	vm_object_offset_t	src_offset,
	vm_object_size_t	size,
	vm_object_t		*_result_object)	/* OUT */
{
	kern_return_t	kr;
	vm_object_t	copy;
	boolean_t	check_ready = FALSE;
	uint32_t	try_failed_count = 0;

	/*
	 *	If a copy is already in progress, wait and retry.
	 *
	 *	XXX
	 *	Consider making this call interruptable, as Mike
	 *	intended it to be.
	 *
	 *	XXXO
	 *	Need a counter or version or something to allow
	 *	us to use the copy that the currently requesting
	 *	thread is obtaining -- is it worth adding to the
	 *	vm object structure? Depends how common this case it.
	 */
	copy_call_count++;
	while (vm_object_wanted(src_object, VM_OBJECT_EVENT_COPY_CALL)) {
		vm_object_sleep(src_object, VM_OBJECT_EVENT_COPY_CALL,
			       THREAD_UNINT);
		copy_call_restart_count++;
	}

	/*
	 *	Indicate (for the benefit of memory_object_create_copy)
	 *	that we want a copy for src_object. (Note that we cannot
	 *	do a real assert_wait before calling memory_object_copy,
	 *	so we simply set the flag.)
	 */

	vm_object_set_wanted(src_object, VM_OBJECT_EVENT_COPY_CALL);
	vm_object_unlock(src_object);

	/*
	 *	Ask the memory manager to give us a memory object
	 *	which represents a copy of the src object.
	 *	The memory manager may give us a memory object
	 *	which we already have, or it may give us a
	 *	new memory object. This memory object will arrive
	 *	via memory_object_create_copy.
	 */

	kr = KERN_FAILURE;	/* XXX need to change memory_object.defs */
	if (kr != KERN_SUCCESS) {
		return kr;
	}

	/*
	 *	Wait for the copy to arrive.
	 */
	vm_object_lock(src_object);
	while (vm_object_wanted(src_object, VM_OBJECT_EVENT_COPY_CALL)) {
		vm_object_sleep(src_object, VM_OBJECT_EVENT_COPY_CALL,
			       THREAD_UNINT);
		copy_call_sleep_count++;
	}
Retry:
	assert(src_object->copy != VM_OBJECT_NULL);
	copy = src_object->copy;
	if (!vm_object_lock_try(copy)) {
		vm_object_unlock(src_object);

		try_failed_count++;
		mutex_pause(try_failed_count);	/* wait a bit */

		vm_object_lock(src_object);
		goto Retry;
	}
	if (copy->vo_size < src_offset+size)
		copy->vo_size = src_offset+size;

	if (!copy->pager_ready)
		check_ready = TRUE;

	/*
	 *	Return the copy.
	 */
	*_result_object = copy;
	vm_object_unlock(copy);
	vm_object_unlock(src_object);

	/* Wait for the copy to be ready. */
	if (check_ready == TRUE) {
		vm_object_lock(copy);
		while (!copy->pager_ready) {
			vm_object_sleep(copy, VM_OBJECT_EVENT_PAGER_READY, THREAD_UNINT);
		}
		vm_object_unlock(copy);
	}

	return KERN_SUCCESS;
}