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
typedef  int /*<<< orphan*/  vm_tag_t ;
typedef  scalar_t__ vm_map_t ;
typedef  int vm_map_size_t ;
typedef  int vm_map_offset_t ;
struct TYPE_4__ {int /*<<< orphan*/  vmkf_beyond_max; } ;
typedef  TYPE_1__ vm_map_kernel_flags_t ;
typedef  scalar_t__ task_t ;
typedef  scalar_t__ kern_return_t ;
typedef  scalar_t__ ipc_port_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IPC_PORT_NULL ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  SHARED_REGION_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  SHARED_REGION_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int VM_FLAGS_FIXED ; 
 int /*<<< orphan*/  VM_INHERIT_DEFAULT ; 
 int /*<<< orphan*/  VM_INHERIT_SHARE ; 
 scalar_t__ VM_KERNEL_ADDRPERM (scalar_t__) ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_NONE ; 
 TYPE_1__ VM_MAP_KERNEL_FLAGS_NONE ; 
 int /*<<< orphan*/  VM_MEMORY_SHARED_PMAP ; 
 int VM_PROT_ALL ; 
 int VM_PROT_EXECUTE ; 
 int VM_PROT_READ ; 
 int _COMM_PAGE32_AREA_LENGTH ; 
 scalar_t__ _COMM_PAGE32_BASE_ADDRESS ; 
 int _COMM_PAGE32_OBJC_BASE ; 
 int _COMM_PAGE32_OBJC_SIZE ; 
 int _COMM_PAGE64_AREA_LENGTH ; 
 scalar_t__ _COMM_PAGE64_BASE_ADDRESS ; 
 int _COMM_PAGE64_OBJC_BASE ; 
 int _COMM_PAGE64_OBJC_SIZE ; 
 int _COMM_PAGE_TEXT_AREA_LENGTH ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ commpage32_handle ; 
 scalar_t__ commpage64_handle ; 
 scalar_t__ commpage_text32_handle ; 
 scalar_t__ commpage_text32_location ; 
 scalar_t__ commpage_text64_handle ; 
 scalar_t__ commpage_text64_location ; 
 int /*<<< orphan*/  pmap_insert_sharedpage (int /*<<< orphan*/ ) ; 
 int pmap_nesting_size_min ; 
 scalar_t__ vm_map_enter_mem_object (scalar_t__,int*,int,int /*<<< orphan*/ ,int,TYPE_1__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int vm_map_is_64bit (scalar_t__) ; 
 int /*<<< orphan*/  vm_map_pmap (scalar_t__) ; 

kern_return_t
vm_commpage_enter(
	vm_map_t	map,
	task_t		task,
	boolean_t	is64bit)
{
#if	defined(__arm__)
#pragma unused(is64bit)
	(void)task;
	(void)map;
	return KERN_SUCCESS;
#elif 	defined(__arm64__)
#pragma unused(is64bit)
	(void)task;
	(void)map;
	pmap_insert_sharedpage(vm_map_pmap(map));
	return KERN_SUCCESS;
#else
	ipc_port_t		commpage_handle, commpage_text_handle;
	vm_map_offset_t		commpage_address, objc_address, commpage_text_address;
	vm_map_size_t		commpage_size, objc_size, commpage_text_size;
	int			vm_flags;
	vm_map_kernel_flags_t	vmk_flags;
	kern_return_t		kr;

	SHARED_REGION_TRACE_DEBUG(
		("commpage: -> enter(%p,%p)\n",
		 (void *)VM_KERNEL_ADDRPERM(map),
		 (void *)VM_KERNEL_ADDRPERM(task)));

	commpage_text_size = _COMM_PAGE_TEXT_AREA_LENGTH;
	/* the comm page is likely to be beyond the actual end of the VM map */
	vm_flags = VM_FLAGS_FIXED;
	vmk_flags = VM_MAP_KERNEL_FLAGS_NONE;
	vmk_flags.vmkf_beyond_max = TRUE;

	/* select the appropriate comm page for this task */
	assert(! (is64bit ^ vm_map_is_64bit(map)));
	if (is64bit) {
		commpage_handle = commpage64_handle;
		commpage_address = (vm_map_offset_t) _COMM_PAGE64_BASE_ADDRESS;
		commpage_size = _COMM_PAGE64_AREA_LENGTH;
		objc_size = _COMM_PAGE64_OBJC_SIZE;
		objc_address = _COMM_PAGE64_OBJC_BASE;
		commpage_text_handle = commpage_text64_handle;
		commpage_text_address = (vm_map_offset_t) commpage_text64_location;
	} else {
		commpage_handle = commpage32_handle;
		commpage_address =
			(vm_map_offset_t)(unsigned) _COMM_PAGE32_BASE_ADDRESS;
		commpage_size = _COMM_PAGE32_AREA_LENGTH;
		objc_size = _COMM_PAGE32_OBJC_SIZE;
		objc_address = _COMM_PAGE32_OBJC_BASE;
		commpage_text_handle = commpage_text32_handle;
		commpage_text_address = (vm_map_offset_t) commpage_text32_location;
	}

    vm_tag_t tag = VM_KERN_MEMORY_NONE;
	if ((commpage_address & (pmap_nesting_size_min - 1)) == 0 &&
	    (commpage_size & (pmap_nesting_size_min - 1)) == 0) {
		/* the commpage is properly aligned or sized for pmap-nesting */
		tag = VM_MEMORY_SHARED_PMAP;
	}
	/* map the comm page in the task's address space */
	assert(commpage_handle != IPC_PORT_NULL);
	kr = vm_map_enter_mem_object(
		map,
		&commpage_address,
		commpage_size,
		0,
		vm_flags,
		vmk_flags,
		tag,
		commpage_handle,
		0,
		FALSE,
		VM_PROT_READ,
		VM_PROT_READ,
		VM_INHERIT_SHARE);
	if (kr != KERN_SUCCESS) {
		SHARED_REGION_TRACE_ERROR(
			("commpage: enter(%p,0x%llx,0x%llx) "
			 "commpage %p mapping failed 0x%x\n",
			 (void *)VM_KERNEL_ADDRPERM(map),
			 (long long)commpage_address,
			 (long long)commpage_size,
			 (void *)VM_KERNEL_ADDRPERM(commpage_handle), kr));
	}

	/* map the comm text page in the task's address space */
	assert(commpage_text_handle != IPC_PORT_NULL);
	kr = vm_map_enter_mem_object(
		map,
		&commpage_text_address,
		commpage_text_size,
		0,
		vm_flags,
		vmk_flags,
		tag,
		commpage_text_handle,
		0,
		FALSE,
		VM_PROT_READ|VM_PROT_EXECUTE,
		VM_PROT_READ|VM_PROT_EXECUTE,
		VM_INHERIT_SHARE);
	if (kr != KERN_SUCCESS) {
		SHARED_REGION_TRACE_ERROR(
			("commpage text: enter(%p,0x%llx,0x%llx) "
			 "commpage text %p mapping failed 0x%x\n",
			 (void *)VM_KERNEL_ADDRPERM(map),
			 (long long)commpage_text_address,
			 (long long)commpage_text_size,
			 (void *)VM_KERNEL_ADDRPERM(commpage_text_handle), kr));
	}

	/*
	 * Since we're here, we also pre-allocate some virtual space for the
	 * Objective-C run-time, if needed...
	 */
	if (objc_size != 0) {
		kr = vm_map_enter_mem_object(
			map,
			&objc_address,
			objc_size,
			0,
			VM_FLAGS_FIXED,
			vmk_flags,
			tag,
			IPC_PORT_NULL,
			0,
			FALSE,
			VM_PROT_ALL,
			VM_PROT_ALL,
			VM_INHERIT_DEFAULT);
		if (kr != KERN_SUCCESS) {
			SHARED_REGION_TRACE_ERROR(
				("commpage: enter(%p,0x%llx,0x%llx) "
				 "objc mapping failed 0x%x\n",
				 (void *)VM_KERNEL_ADDRPERM(map),
				 (long long)objc_address,
				 (long long)objc_size, kr));
		}
	}

	SHARED_REGION_TRACE_DEBUG(
		("commpage: enter(%p,%p) <- 0x%x\n",
		 (void *)VM_KERNEL_ADDRPERM(map),
		 (void *)VM_KERNEL_ADDRPERM(task), kr));
	return kr;
#endif
}