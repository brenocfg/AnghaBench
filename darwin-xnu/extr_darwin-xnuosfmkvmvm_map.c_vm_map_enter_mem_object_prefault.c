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
typedef  int /*<<< orphan*/  vm_tag_t ;
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int /*<<< orphan*/  vm_object_offset_t ;
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  int /*<<< orphan*/  vm_map_size_t ;
typedef  int /*<<< orphan*/  vm_map_offset_t ;
typedef  int /*<<< orphan*/  vm_map_kernel_flags_t ;
typedef  int /*<<< orphan*/  upl_page_list_ptr_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  VM_INHERIT_DEFAULT ; 
 int /*<<< orphan*/  vm_map_enter_mem_object_helper (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

kern_return_t
vm_map_enter_mem_object_prefault(
	vm_map_t		target_map,
	vm_map_offset_t		*address,
	vm_map_size_t		initial_size,
	vm_map_offset_t		mask,
	int			flags,
	vm_map_kernel_flags_t	vmk_flags,
	vm_tag_t		tag,
	ipc_port_t		port,
	vm_object_offset_t	offset,
	vm_prot_t		cur_protection,
	vm_prot_t		max_protection,
	upl_page_list_ptr_t	page_list,
	unsigned int		page_list_count)
{
	kern_return_t ret;

	ret = vm_map_enter_mem_object_helper(target_map,
					     address,
					     initial_size,
					     mask,
					     flags,
					     vmk_flags,
					     tag,
					     port,
					     offset,
					     FALSE,
					     cur_protection,
					     max_protection,
					     VM_INHERIT_DEFAULT,
					     page_list,
					     page_list_count);

#if KASAN
	if (ret == KERN_SUCCESS && address && target_map->pmap == kernel_pmap) {
		kasan_notify_address(*address, initial_size);
	}
#endif

	return ret;
}