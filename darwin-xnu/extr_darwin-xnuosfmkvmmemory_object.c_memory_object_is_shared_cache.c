#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_object_t ;
typedef  int /*<<< orphan*/  memory_object_control_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_4__ {int /*<<< orphan*/  object_is_shared_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__* VM_OBJECT_NULL ; 
 TYPE_1__* memory_object_control_to_vm_object (int /*<<< orphan*/ ) ; 

boolean_t
memory_object_is_shared_cache(
	memory_object_control_t	control)
{
	vm_object_t	object = VM_OBJECT_NULL;

	object = memory_object_control_to_vm_object(control);
	if (object == VM_OBJECT_NULL)
		return FALSE;

	return object->object_is_shared_cache;
}