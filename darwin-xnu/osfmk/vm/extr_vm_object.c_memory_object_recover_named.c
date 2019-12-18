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
typedef  int /*<<< orphan*/  memory_object_control_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_10__ {scalar_t__ named; int /*<<< orphan*/  pager_ready; int /*<<< orphan*/  ref_count; int /*<<< orphan*/  alive; scalar_t__ terminating; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  THREAD_UNINT ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VM_OBJECT_EVENT_PAGER_READY ; 
 int /*<<< orphan*/  VM_OBJECT_EVENT_PAGING_IN_PROGRESS ; 
 TYPE_1__* VM_OBJECT_NULL ; 
 TYPE_1__* memory_object_control_to_vm_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_lock_assert_exclusive (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_res_reference (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_sleep (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_wait (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
memory_object_recover_named(
	memory_object_control_t	control,
	boolean_t		wait_on_terminating)
{
	vm_object_t		object;

	object = memory_object_control_to_vm_object(control);
	if (object == VM_OBJECT_NULL) {
		return (KERN_INVALID_ARGUMENT);
	}
restart:
	vm_object_lock(object);

	if (object->terminating && wait_on_terminating) {
		vm_object_wait(object, 
			VM_OBJECT_EVENT_PAGING_IN_PROGRESS, 
			THREAD_UNINT);
		goto restart;
	}

	if (!object->alive) {
		vm_object_unlock(object);
		return KERN_FAILURE;
	}

	if (object->named == TRUE) {
		vm_object_unlock(object);
		return KERN_SUCCESS;
	}
	object->named = TRUE;
	vm_object_lock_assert_exclusive(object);
	object->ref_count++;
	vm_object_res_reference(object);
	while (!object->pager_ready) {
		vm_object_sleep(object,
				VM_OBJECT_EVENT_PAGER_READY,
				THREAD_UNINT);
	}
	vm_object_unlock(object);
	return (KERN_SUCCESS);
}