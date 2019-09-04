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
typedef  TYPE_1__* vm_shared_region_t ;
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  scalar_t__ vm_map_size_t ;
typedef  scalar_t__ vm_map_offset_t ;
typedef  void task ;
typedef  void _vm_map ;
typedef  scalar_t__ kern_return_t ;
typedef  void* ipc_port_t ;
typedef  int /*<<< orphan*/  cpu_type_t ;
typedef  int /*<<< orphan*/  cpu_subtype_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_5__ {scalar_t__ sr_base_address; scalar_t__ sr_size; scalar_t__ sr_pmap_nesting_start; scalar_t__ sr_pmap_nesting_size; void* sr_mem_entry; } ;

/* Variables and functions */
 scalar_t__ KERN_FAILURE ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  SHARED_REGION_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  SHARED_REGION_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VM_FLAGS_FIXED ; 
 int /*<<< orphan*/  VM_INHERIT_SHARE ; 
 scalar_t__ VM_KERNEL_ADDRPERM (void*) ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_NONE ; 
 int /*<<< orphan*/  VM_MAP_KERNEL_FLAGS_NONE ; 
 int /*<<< orphan*/  VM_MEMORY_SHARED_PMAP ; 
 int /*<<< orphan*/  VM_PROT_ALL ; 
 int /*<<< orphan*/  VM_PROT_READ ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ pmap_nesting_size_max ; 
 scalar_t__ vm_map_enter_mem_object (void*,scalar_t__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_shared_region_deallocate (TYPE_1__*) ; 
 TYPE_1__* vm_shared_region_lookup (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_shared_region_set (void*,TYPE_1__*) ; 

kern_return_t
vm_shared_region_enter(
	struct _vm_map		*map,
	struct task		*task,
	boolean_t		is_64bit,
	void			*fsroot,
	cpu_type_t		cpu,
	cpu_subtype_t		cpu_subtype)
{
	kern_return_t		kr;
	vm_shared_region_t	shared_region;
	vm_map_offset_t		sr_address, sr_offset, target_address;
	vm_map_size_t		sr_size, mapping_size;
	vm_map_offset_t		sr_pmap_nesting_start;
	vm_map_size_t		sr_pmap_nesting_size;
	ipc_port_t		sr_handle;
	vm_prot_t		cur_prot, max_prot;

	SHARED_REGION_TRACE_DEBUG(
		("shared_region: -> "
		 "enter(map=%p,task=%p,root=%p,cpu=<%d,%d>,64bit=%d)\n",
		 (void *)VM_KERNEL_ADDRPERM(map),
		 (void *)VM_KERNEL_ADDRPERM(task),
		 (void *)VM_KERNEL_ADDRPERM(fsroot),
		 cpu, cpu_subtype, is_64bit));

	/* lookup (create if needed) the shared region for this environment */
	shared_region = vm_shared_region_lookup(fsroot, cpu, cpu_subtype, is_64bit);
	if (shared_region == NULL) {
		/* this should not happen ! */
		SHARED_REGION_TRACE_ERROR(
			("shared_region: -> "
			 "enter(map=%p,task=%p,root=%p,cpu=<%d,%d>,64bit=%d): "
			 "lookup failed !\n",
			 (void *)VM_KERNEL_ADDRPERM(map),
			 (void *)VM_KERNEL_ADDRPERM(task),
			 (void *)VM_KERNEL_ADDRPERM(fsroot),
			 cpu, cpu_subtype, is_64bit));
		//panic("shared_region_enter: lookup failed\n");
		return KERN_FAILURE;
	}
	
	kr = KERN_SUCCESS;
	/* no need to lock since this data is never modified */
	sr_address = shared_region->sr_base_address;
	sr_size = shared_region->sr_size;
	sr_handle = shared_region->sr_mem_entry;
	sr_pmap_nesting_start = shared_region->sr_pmap_nesting_start;
	sr_pmap_nesting_size = shared_region->sr_pmap_nesting_size;

	cur_prot = VM_PROT_READ;
#if __x86_64__
	/*
	 * XXX BINARY COMPATIBILITY
	 * java6 apparently needs to modify some code in the
	 * dyld shared cache and needs to be allowed to add
	 * write access...
	 */
	max_prot = VM_PROT_ALL;
#else /* __x86_64__ */
	max_prot = VM_PROT_READ;
#endif /* __x86_64__ */
	/*
	 * Start mapping the shared region's VM sub map into the task's VM map.
	 */
	sr_offset = 0;

	if (sr_pmap_nesting_start > sr_address) {
		/* we need to map a range without pmap-nesting first */
		target_address = sr_address;
		mapping_size = sr_pmap_nesting_start - sr_address;
		kr = vm_map_enter_mem_object(
			map,
			&target_address,
			mapping_size,
			0,
			VM_FLAGS_FIXED,
			VM_MAP_KERNEL_FLAGS_NONE,
			VM_KERN_MEMORY_NONE,
			sr_handle,
			sr_offset,
			TRUE,
			cur_prot,
			max_prot,
			VM_INHERIT_SHARE);
		if (kr != KERN_SUCCESS) {
			SHARED_REGION_TRACE_ERROR(
				("shared_region: enter(%p,%p,%p,%d,%d,%d): "
				 "vm_map_enter(0x%llx,0x%llx,%p) error 0x%x\n",
				 (void *)VM_KERNEL_ADDRPERM(map),
				 (void *)VM_KERNEL_ADDRPERM(task),
				 (void *)VM_KERNEL_ADDRPERM(fsroot),
				 cpu, cpu_subtype, is_64bit,
				 (long long)target_address,
				 (long long)mapping_size,
				 (void *)VM_KERNEL_ADDRPERM(sr_handle), kr));
			goto done;
		}
		SHARED_REGION_TRACE_DEBUG(
			("shared_region: enter(%p,%p,%p,%d,%d,%d): "
			 "vm_map_enter(0x%llx,0x%llx,%p) error 0x%x\n",
			 (void *)VM_KERNEL_ADDRPERM(map),
			 (void *)VM_KERNEL_ADDRPERM(task),
			 (void *)VM_KERNEL_ADDRPERM(fsroot),
			 cpu, cpu_subtype, is_64bit,
			 (long long)target_address, (long long)mapping_size,
			 (void *)VM_KERNEL_ADDRPERM(sr_handle), kr));
		sr_offset += mapping_size;
		sr_size -= mapping_size;
	}
	/*
	 * We may need to map several pmap-nested portions, due to platform
	 * specific restrictions on pmap nesting.
	 * The pmap-nesting is triggered by the "VM_MEMORY_SHARED_PMAP" alias...
	 */
	for (;
	     sr_pmap_nesting_size > 0;
	     sr_offset += mapping_size,
		     sr_size -= mapping_size,
		     sr_pmap_nesting_size -= mapping_size) {
		target_address = sr_address + sr_offset;
		mapping_size = sr_pmap_nesting_size;
		if (mapping_size > pmap_nesting_size_max) {
			mapping_size = (vm_map_offset_t) pmap_nesting_size_max;
		}
		kr = vm_map_enter_mem_object(
			map,
			&target_address,
			mapping_size,
			0,
			VM_FLAGS_FIXED,
			VM_MAP_KERNEL_FLAGS_NONE,
			VM_MEMORY_SHARED_PMAP,
			sr_handle,
			sr_offset,
			TRUE,
			cur_prot,
			max_prot,
			VM_INHERIT_SHARE);
		if (kr != KERN_SUCCESS) {
			SHARED_REGION_TRACE_ERROR(
				("shared_region: enter(%p,%p,%p,%d,%d,%d): "
				 "vm_map_enter(0x%llx,0x%llx,%p) error 0x%x\n",
				 (void *)VM_KERNEL_ADDRPERM(map),
				 (void *)VM_KERNEL_ADDRPERM(task),
				 (void *)VM_KERNEL_ADDRPERM(fsroot),
				 cpu, cpu_subtype, is_64bit,
				 (long long)target_address,
				 (long long)mapping_size,
				 (void *)VM_KERNEL_ADDRPERM(sr_handle), kr));
			goto done;
		}
		SHARED_REGION_TRACE_DEBUG(
			("shared_region: enter(%p,%p,%p,%d,%d,%d): "
			 "nested vm_map_enter(0x%llx,0x%llx,%p) error 0x%x\n",
			 (void *)VM_KERNEL_ADDRPERM(map),
			 (void *)VM_KERNEL_ADDRPERM(task),
			 (void *)VM_KERNEL_ADDRPERM(fsroot),
			 cpu, cpu_subtype, is_64bit,
			 (long long)target_address, (long long)mapping_size,
			 (void *)VM_KERNEL_ADDRPERM(sr_handle), kr));
	}
	if (sr_size > 0) {
		/* and there's some left to be mapped without pmap-nesting */
		target_address = sr_address + sr_offset;
		mapping_size = sr_size;
		kr = vm_map_enter_mem_object(
			map,
			&target_address,
			mapping_size,
			0,
			VM_FLAGS_FIXED,
			VM_MAP_KERNEL_FLAGS_NONE,
			VM_KERN_MEMORY_NONE,
			sr_handle,
			sr_offset,
			TRUE,
			cur_prot,
			max_prot,
			VM_INHERIT_SHARE);
		if (kr != KERN_SUCCESS) {
			SHARED_REGION_TRACE_ERROR(
				("shared_region: enter(%p,%p,%p,%d,%d,%d): "
				 "vm_map_enter(0x%llx,0x%llx,%p) error 0x%x\n",
				 (void *)VM_KERNEL_ADDRPERM(map),
				 (void *)VM_KERNEL_ADDRPERM(task),
				 (void *)VM_KERNEL_ADDRPERM(fsroot),
				 cpu, cpu_subtype, is_64bit,
				 (long long)target_address,
				 (long long)mapping_size,
				 (void *)VM_KERNEL_ADDRPERM(sr_handle), kr));
			goto done;
		}
		SHARED_REGION_TRACE_DEBUG(
			("shared_region: enter(%p,%p,%p,%d,%d,%d): "
			 "vm_map_enter(0x%llx,0x%llx,%p) error 0x%x\n",
			 (void *)VM_KERNEL_ADDRPERM(map),
			 (void *)VM_KERNEL_ADDRPERM(task),
			 (void *)VM_KERNEL_ADDRPERM(fsroot),
			 cpu, cpu_subtype, is_64bit,
			 (long long)target_address, (long long)mapping_size,
			 (void *)VM_KERNEL_ADDRPERM(sr_handle), kr));
		sr_offset += mapping_size;
		sr_size -= mapping_size;
	}
	assert(sr_size == 0);

done:
	if (kr == KERN_SUCCESS) {
		/* let the task use that shared region */
		vm_shared_region_set(task, shared_region);
	} else {
		/* drop our reference since we're not using it */
		vm_shared_region_deallocate(shared_region);
		vm_shared_region_set(task, NULL);
	}

	SHARED_REGION_TRACE_DEBUG(
		("shared_region: enter(%p,%p,%p,%d,%d,%d) <- 0x%x\n",
		 (void *)VM_KERNEL_ADDRPERM(map),
		 (void *)VM_KERNEL_ADDRPERM(task),
		 (void *)VM_KERNEL_ADDRPERM(fsroot),
		 cpu, cpu_subtype, is_64bit, kr));
	return kr;
}