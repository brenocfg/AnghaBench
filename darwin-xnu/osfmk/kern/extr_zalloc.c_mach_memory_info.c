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
typedef  unsigned int vm_size_t ;
typedef  unsigned int vm_offset_t ;
typedef  int /*<<< orphan*/  vm_map_size_t ;
typedef  scalar_t__ vm_map_copy_t ;
typedef  int /*<<< orphan*/  vm_map_address_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  mach_zone_name_t ;
typedef  int /*<<< orphan*/ * mach_zone_name_array_t ;
struct TYPE_5__ {int /*<<< orphan*/  mzi_collectable; } ;
typedef  TYPE_1__ mach_zone_info_t ;
typedef  TYPE_1__* mach_zone_info_array_t ;
typedef  unsigned int mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  mach_memory_info_t ;
typedef  int /*<<< orphan*/ * mach_memory_info_array_t ;
typedef  scalar_t__ kern_return_t ;
typedef  scalar_t__ host_priv_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GET_MZI_COLLECTABLE_BYTES (int /*<<< orphan*/ ) ; 
 scalar_t__ HOST_NULL ; 
 scalar_t__ KERN_INVALID_HOST ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  PE_i_can_has_debugger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_IPC ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  all_zones_lock ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ create_vm_map_copy (unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  get_zone_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_kernel_map ; 
 scalar_t__ kmem_alloc_pageable (int /*<<< orphan*/ ,unsigned int*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 scalar_t__ num_zones ; 
 unsigned int round_page (unsigned int) ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ vm_map_copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ vm_map_unwire (int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_wire_kernel (int /*<<< orphan*/ ,unsigned int,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_diagnose (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int vm_page_diagnose_estimate () ; 
 int /*<<< orphan*/ * zone_array ; 

kern_return_t
mach_memory_info(
	host_priv_t		host,
	mach_zone_name_array_t	*namesp,
	mach_msg_type_number_t  *namesCntp,
	mach_zone_info_array_t	*infop,
	mach_msg_type_number_t  *infoCntp,
	mach_memory_info_array_t *memoryInfop,
	mach_msg_type_number_t   *memoryInfoCntp)
{
	mach_zone_name_t	*names;
	vm_offset_t		names_addr;
	vm_size_t		names_size;

	mach_zone_info_t	*info;
	vm_offset_t		info_addr;
	vm_size_t		info_size;

	mach_memory_info_t	*memory_info;
	vm_offset_t		memory_info_addr;
	vm_size_t		memory_info_size;
	vm_size_t		memory_info_vmsize;
	unsigned int		num_info;

	unsigned int		max_zones, used_zones, i;
	mach_zone_name_t	*zn;
	mach_zone_info_t    	*zi;
	kern_return_t		kr;
	
	uint64_t 		zones_collectable_bytes = 0;

	if (host == HOST_NULL)
		return KERN_INVALID_HOST;
#if CONFIG_DEBUGGER_FOR_ZONE_INFO
	if (!PE_i_can_has_debugger(NULL))
		return KERN_INVALID_HOST;
#endif

	/*
	 *	We assume that zones aren't freed once allocated.
	 *	We won't pick up any zones that are allocated later.
	 */

	simple_lock(&all_zones_lock);
	max_zones = (unsigned int)(num_zones);
	simple_unlock(&all_zones_lock);

	names_size = round_page(max_zones * sizeof *names);
	kr = kmem_alloc_pageable(ipc_kernel_map,
				 &names_addr, names_size, VM_KERN_MEMORY_IPC);
	if (kr != KERN_SUCCESS)
		return kr;
	names = (mach_zone_name_t *) names_addr;

	info_size = round_page(max_zones * sizeof *info);
	kr = kmem_alloc_pageable(ipc_kernel_map,
				 &info_addr, info_size, VM_KERN_MEMORY_IPC);
	if (kr != KERN_SUCCESS) {
		kmem_free(ipc_kernel_map,
			  names_addr, names_size);
		return kr;
	}
	info = (mach_zone_info_t *) info_addr;

	zn = &names[0];
	zi = &info[0];

	used_zones = max_zones;
	for (i = 0; i < max_zones; i++) {
		if (!get_zone_info(&(zone_array[i]), zn, zi)) {
			used_zones--;
			continue;
		}
		zones_collectable_bytes += GET_MZI_COLLECTABLE_BYTES(zi->mzi_collectable);
		zn++;
		zi++;
	}

	*namesp = (mach_zone_name_t *) create_vm_map_copy(names_addr, names_size, used_zones * sizeof *names);
	*namesCntp = used_zones;

	*infop = (mach_zone_info_t *) create_vm_map_copy(info_addr, info_size, used_zones * sizeof *info);
	*infoCntp = used_zones;
	
	num_info = 0;
	memory_info_addr = 0;

	if (memoryInfop && memoryInfoCntp)
	{
		vm_map_copy_t		copy;
		num_info = vm_page_diagnose_estimate();
		memory_info_size = num_info * sizeof(*memory_info);
		memory_info_vmsize = round_page(memory_info_size);
		kr = kmem_alloc_pageable(ipc_kernel_map,
					 &memory_info_addr, memory_info_vmsize, VM_KERN_MEMORY_IPC);
		if (kr != KERN_SUCCESS) {
			return kr;
		}

		kr = vm_map_wire_kernel(ipc_kernel_map, memory_info_addr, memory_info_addr + memory_info_vmsize,
				     VM_PROT_READ|VM_PROT_WRITE, VM_KERN_MEMORY_IPC, FALSE);
		assert(kr == KERN_SUCCESS);

		memory_info = (mach_memory_info_t *) memory_info_addr;
		vm_page_diagnose(memory_info, num_info, zones_collectable_bytes);

		kr = vm_map_unwire(ipc_kernel_map, memory_info_addr, memory_info_addr + memory_info_vmsize, FALSE);
		assert(kr == KERN_SUCCESS);
	
		kr = vm_map_copyin(ipc_kernel_map, (vm_map_address_t)memory_info_addr,
				   (vm_map_size_t)memory_info_size, TRUE, &copy);
		assert(kr == KERN_SUCCESS);

		*memoryInfop = (mach_memory_info_t *) copy;
		*memoryInfoCntp = num_info;
	}

	return KERN_SUCCESS;
}