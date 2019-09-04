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
typedef  int vm_size_t ;
typedef  int vm_offset_t ;
typedef  int /*<<< orphan*/  vm_map_size_t ;
typedef  scalar_t__ vm_map_copy_t ;
typedef  int /*<<< orphan*/  vm_map_address_t ;
typedef  TYPE_1__* processor_t ;
typedef  scalar_t__ processor_info_t ;
typedef  scalar_t__ processor_info_array_t ;
typedef  int /*<<< orphan*/  processor_flavor_t ;
typedef  unsigned int natural_t ;
typedef  unsigned int mach_msg_type_number_t ;
typedef  scalar_t__ kern_return_t ;
typedef  scalar_t__ host_t ;
struct TYPE_4__ {struct TYPE_4__* processor_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ HOST_NULL ; 
 scalar_t__ KERN_INVALID_ARGUMENT ; 
 scalar_t__ KERN_RESOURCE_SHORTAGE ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_IPC ; 
 int /*<<< orphan*/  VM_MAP_PAGE_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  ipc_kernel_map ; 
 scalar_t__ kmem_alloc (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ,int,int) ; 
 unsigned int processor_count ; 
 scalar_t__ processor_info (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__,unsigned int*) ; 
 scalar_t__ processor_info_count (int /*<<< orphan*/ ,unsigned int*) ; 
 TYPE_1__* processor_list ; 
 int /*<<< orphan*/  processor_list_lock ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ vm_map_copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int vm_map_round_page (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_trunc_page (int,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_unwire (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

kern_return_t
host_processor_info(host_t host,
                    processor_flavor_t flavor,
                    natural_t * out_pcount,
                    processor_info_array_t * out_array,
                    mach_msg_type_number_t * out_array_count)
{
	kern_return_t result;
	processor_t processor;
	host_t thost;
	processor_info_t info;
	unsigned int icount, tcount;
	unsigned int pcount, i;
	vm_offset_t addr;
	vm_size_t size, needed;
	vm_map_copy_t copy;

	if (host == HOST_NULL)
		return (KERN_INVALID_ARGUMENT);

	result = processor_info_count(flavor, &icount);
	if (result != KERN_SUCCESS)
		return (result);

	pcount = processor_count;
	assert(pcount != 0);

	needed = pcount * icount * sizeof(natural_t);
	size = vm_map_round_page(needed, VM_MAP_PAGE_MASK(ipc_kernel_map));
	result = kmem_alloc(ipc_kernel_map, &addr, size, VM_KERN_MEMORY_IPC);
	if (result != KERN_SUCCESS)
		return (KERN_RESOURCE_SHORTAGE);

	info = (processor_info_t)addr;
	processor = processor_list;
	tcount = icount;

	result = processor_info(processor, flavor, &thost, info, &tcount);
	if (result != KERN_SUCCESS) {
		kmem_free(ipc_kernel_map, addr, size);
		return (result);
	}

	if (pcount > 1) {
		for (i = 1; i < pcount; i++) {
			simple_lock(&processor_list_lock);
			processor = processor->processor_list;
			simple_unlock(&processor_list_lock);

			info += icount;
			tcount = icount;
			result = processor_info(processor, flavor, &thost, info, &tcount);
			if (result != KERN_SUCCESS) {
				kmem_free(ipc_kernel_map, addr, size);
				return (result);
			}
		}
	}

	if (size != needed)
		bzero((char *)addr + needed, size - needed);

	result = vm_map_unwire(ipc_kernel_map, vm_map_trunc_page(addr, VM_MAP_PAGE_MASK(ipc_kernel_map)),
	                       vm_map_round_page(addr + size, VM_MAP_PAGE_MASK(ipc_kernel_map)), FALSE);
	assert(result == KERN_SUCCESS);
	result = vm_map_copyin(ipc_kernel_map, (vm_map_address_t)addr, (vm_map_size_t)needed, TRUE, &copy);
	assert(result == KERN_SUCCESS);

	*out_pcount = pcount;
	*out_array = (processor_info_array_t)copy;
	*out_array_count = pcount * icount;

	return (KERN_SUCCESS);
}