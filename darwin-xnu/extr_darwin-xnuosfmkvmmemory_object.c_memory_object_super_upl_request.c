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
typedef  int /*<<< orphan*/  upl_t ;
typedef  int /*<<< orphan*/  upl_size_t ;
typedef  int /*<<< orphan*/  upl_page_info_t ;
typedef  int /*<<< orphan*/  upl_control_flags_t ;
typedef  int /*<<< orphan*/  memory_object_offset_t ;
typedef  int /*<<< orphan*/  memory_object_control_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 scalar_t__ VM_OBJECT_NULL ; 
 scalar_t__ memory_object_control_to_vm_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_super_upl_request (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*,int /*<<< orphan*/ ,int) ; 

kern_return_t
memory_object_super_upl_request(
	memory_object_control_t control,
	memory_object_offset_t	offset,
	upl_size_t		size,
	upl_size_t		super_cluster,
	upl_t			*upl,
	upl_page_info_t		*user_page_list,
	unsigned int		*page_list_count,
	int			cntrl_flags,
	int		        tag)
{
	vm_object_t		object;

	object = memory_object_control_to_vm_object(control);
	if (object == VM_OBJECT_NULL)
		return (KERN_INVALID_ARGUMENT);

	return vm_object_super_upl_request(object,
					   offset,
					   size,
					   super_cluster,
					   upl,
					   user_page_list,
					   page_list_count,
					   (upl_control_flags_t)(unsigned int) cntrl_flags,
					   tag);
}