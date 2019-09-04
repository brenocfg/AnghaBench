#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_object_t ;
typedef  int /*<<< orphan*/  memory_object_control_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_6__ {int /*<<< orphan*/  code_signed; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__* VM_OBJECT_NULL ; 
 TYPE_1__* memory_object_control_to_vm_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_lock_shared (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_unlock (TYPE_1__*) ; 

boolean_t
memory_object_is_signed(
	memory_object_control_t	control)
{
	boolean_t	is_signed;
	vm_object_t	object;

	object = memory_object_control_to_vm_object(control);
	if (object == VM_OBJECT_NULL)
		return FALSE;

	vm_object_lock_shared(object);
	is_signed = object->code_signed;
	vm_object_unlock(object);

	return is_signed;
}