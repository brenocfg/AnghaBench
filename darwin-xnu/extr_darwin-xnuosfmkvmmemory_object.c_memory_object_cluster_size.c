#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  TYPE_1__* vm_object_t ;
typedef  int /*<<< orphan*/  vm_object_offset_t ;
typedef  scalar_t__ vm_object_fault_info_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ memory_object_offset_t ;
typedef  scalar_t__ memory_object_fault_info_t ;
typedef  int /*<<< orphan*/  memory_object_control_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_5__ {scalar_t__ paging_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 TYPE_1__* VM_OBJECT_NULL ; 
 TYPE_1__* memory_object_control_to_vm_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_cluster_size (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 

kern_return_t
memory_object_cluster_size(
	memory_object_control_t	control,
	memory_object_offset_t	*start,
	vm_size_t		*length,
	uint32_t		*io_streaming,
	memory_object_fault_info_t mo_fault_info)
{
	vm_object_t		object;
	vm_object_fault_info_t	fault_info;

	object = memory_object_control_to_vm_object(control);

	if (object == VM_OBJECT_NULL || object->paging_offset > *start)
		return KERN_INVALID_ARGUMENT;

	*start -= object->paging_offset;

	fault_info = (vm_object_fault_info_t)(uintptr_t) mo_fault_info;
	vm_object_cluster_size(object,
			       (vm_object_offset_t *)start,
			       length,
			       fault_info,
			       io_streaming);

	*start += object->paging_offset;

	return KERN_SUCCESS;
}