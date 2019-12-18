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
typedef  int /*<<< orphan*/  vm_object_size_t ;
typedef  int /*<<< orphan*/ * memory_object_t ;
typedef  int /*<<< orphan*/ * memory_object_control_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_10__ {int internal; int pager_created; void* pager_initialized; void* pager_ready; void* named; int /*<<< orphan*/ * pager_control; int /*<<< orphan*/ * pager; int /*<<< orphan*/  copy_strategy; void* pager_trusted; } ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/ * MEMORY_OBJECT_CONTROL_NULL ; 
 int /*<<< orphan*/  MEMORY_OBJECT_COPY_INVALID ; 
 int /*<<< orphan*/ * MEMORY_OBJECT_NULL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 void* TRUE ; 
 int /*<<< orphan*/  VM_OBJECT_EVENT_INITIALIZED ; 
 int /*<<< orphan*/  VM_OBJECT_EVENT_PAGER_READY ; 
 TYPE_1__* VM_OBJECT_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * memory_object_control_allocate (TYPE_1__*) ; 
 int /*<<< orphan*/  memory_object_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_object_reference (int /*<<< orphan*/ *) ; 
 TYPE_1__* vm_object_allocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_wakeup (TYPE_1__*,int /*<<< orphan*/ ) ; 

vm_object_t
vm_object_memory_object_associate(
	memory_object_t		pager,
	vm_object_t		object,
	vm_object_size_t	size,
	boolean_t		named)
{
	memory_object_control_t control;

	assert(pager != MEMORY_OBJECT_NULL);

	if (object != VM_OBJECT_NULL) {
		assert(object->internal);
		assert(object->pager_created);
		assert(!object->pager_initialized);
		assert(!object->pager_ready);
	} else {
		object = vm_object_allocate(size);
		assert(object != VM_OBJECT_NULL);
		object->internal = FALSE;
		object->pager_trusted = FALSE;
		/* copy strategy invalid until set by memory manager */
		object->copy_strategy = MEMORY_OBJECT_COPY_INVALID;
	}

	/*
	 *	Allocate request port.
	 */

	control = memory_object_control_allocate(object);
	assert (control != MEMORY_OBJECT_CONTROL_NULL);

	vm_object_lock(object);

	assert(!object->pager_ready);
	assert(!object->pager_initialized);
	assert(object->pager == NULL);
	assert(object->pager_control == NULL);

	/*
	 *	Copy the reference we were given.
	 */

	memory_object_reference(pager);
	object->pager_created = TRUE;
	object->pager = pager;
	object->pager_control = control;
	object->pager_ready = FALSE;

	vm_object_unlock(object);

	/*
	 *	Let the pager know we're using it.
	 */

	(void) memory_object_init(pager,
				  object->pager_control,
				  PAGE_SIZE);

	vm_object_lock(object);
	if (named)
		object->named = TRUE;
	if (object->internal) {
		object->pager_ready = TRUE;
		vm_object_wakeup(object, VM_OBJECT_EVENT_PAGER_READY);
	}

	object->pager_initialized = TRUE;
	vm_object_wakeup(object, VM_OBJECT_EVENT_INITIALIZED);

	vm_object_unlock(object);

	return object;
}