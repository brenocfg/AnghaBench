#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ vm_object_t ;
typedef  int /*<<< orphan*/ * memory_object_control_t ;

/* Variables and functions */
 scalar_t__ VM_OBJECT_NULL ; 
 scalar_t__ memory_object_control_to_vm_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_object_cache_remove (scalar_t__) ; 

void
memory_object_mark_used(
        memory_object_control_t	control)
{
	vm_object_t		object;

	if (control == NULL)
		return;

	object = memory_object_control_to_vm_object(control);

	if (object != VM_OBJECT_NULL)
		vm_object_cache_remove(object);
}