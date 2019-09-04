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
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_4__ {scalar_t__ resident_page_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* VM_OBJECT_NULL ; 
 TYPE_1__* memory_object_control_to_vm_object (int /*<<< orphan*/ ) ; 

kern_return_t
memory_object_pages_resident(
	memory_object_control_t	control,
	boolean_t			*	has_pages_resident)
{
	vm_object_t		object;

	*has_pages_resident = FALSE;

	object = memory_object_control_to_vm_object(control);
	if (object == VM_OBJECT_NULL)
		return (KERN_INVALID_ARGUMENT);

	if (object->resident_page_count)
		*has_pages_resident = TRUE;
	
	return (KERN_SUCCESS);
}