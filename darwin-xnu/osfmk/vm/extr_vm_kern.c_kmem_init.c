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
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  vm_object_offset_t ;
typedef  scalar_t__ vm_map_size_t ;
typedef  scalar_t__ vm_map_offset_t ;
struct TYPE_4__ {void* vmkf_no_pmap_check; void* vmkf_permanent; } ;
typedef  TYPE_1__ vm_map_kernel_flags_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ MIN (int,int /*<<< orphan*/ ) ; 
 void* TRUE ; 
 int /*<<< orphan*/  VM_FLAGS_FIXED ; 
 int /*<<< orphan*/  VM_INHERIT_DEFAULT ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_NONE ; 
 TYPE_1__ VM_MAP_KERNEL_FLAGS_NONE ; 
 int /*<<< orphan*/  VM_MAP_PAGE_MASK (int /*<<< orphan*/ ) ; 
 scalar_t__ VM_MAX_KERNEL_ADDRESS ; 
 scalar_t__ VM_MIN_KERNEL_AND_KEXT_ADDRESS ; 
 int /*<<< orphan*/  VM_NOT_USER_WIREABLE ; 
 int /*<<< orphan*/  VM_OBJECT_NULL ; 
 int /*<<< orphan*/  VM_PROT_NONE ; 
 int /*<<< orphan*/  kernel_map ; 
 int max_mem ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pmap_kernel () ; 
 scalar_t__ pmap_virtual_region (unsigned int,scalar_t__*,scalar_t__*) ; 
 scalar_t__ vm_global_no_user_wire_amount ; 
 scalar_t__ vm_global_user_wire_limit ; 
 int /*<<< orphan*/  vm_map_create (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_enter (int /*<<< orphan*/ ,scalar_t__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_round_page (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_trunc_page (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_user_wire_limit ; 

void
kmem_init(
	vm_offset_t	start,
	vm_offset_t	end)
{
	vm_map_offset_t map_start;
	vm_map_offset_t map_end;
	vm_map_kernel_flags_t vmk_flags;

	vmk_flags = VM_MAP_KERNEL_FLAGS_NONE;
	vmk_flags.vmkf_permanent = TRUE;
	vmk_flags.vmkf_no_pmap_check = TRUE;

	map_start = vm_map_trunc_page(start,
				      VM_MAP_PAGE_MASK(kernel_map));
	map_end = vm_map_round_page(end,
				    VM_MAP_PAGE_MASK(kernel_map));

#if	defined(__arm__) || defined(__arm64__)
	kernel_map = vm_map_create(pmap_kernel(),VM_MIN_KERNEL_AND_KEXT_ADDRESS,
			    VM_MAX_KERNEL_ADDRESS, FALSE);
	/*
	 *	Reserve virtual memory allocated up to this time.
	 */
	{
		unsigned int	region_select = 0;
		vm_map_offset_t	region_start;
		vm_map_size_t	region_size;
		vm_map_offset_t map_addr;
		kern_return_t kr;

		while (pmap_virtual_region(region_select, &region_start, &region_size)) {

			map_addr = region_start;
			kr = vm_map_enter(kernel_map, &map_addr,
					  vm_map_round_page(region_size,
							    VM_MAP_PAGE_MASK(kernel_map)),
					  (vm_map_offset_t) 0,
			                  VM_FLAGS_FIXED,
					  vmk_flags,
					  VM_KERN_MEMORY_NONE,
					  VM_OBJECT_NULL, 
			                  (vm_object_offset_t) 0, FALSE, VM_PROT_NONE, VM_PROT_NONE,
			                  VM_INHERIT_DEFAULT);

			if (kr != KERN_SUCCESS) {
				panic("kmem_init(0x%llx,0x%llx): vm_map_enter(0x%llx,0x%llx) error 0x%x\n",
				       (uint64_t) start, (uint64_t) end, (uint64_t) region_start,
				       (uint64_t) region_size, kr);
			}	

			region_select++;
		}	
	}
#else
	kernel_map = vm_map_create(pmap_kernel(),VM_MIN_KERNEL_AND_KEXT_ADDRESS,
			    map_end, FALSE);
	/*
	 *	Reserve virtual memory allocated up to this time.
	 */
	if (start != VM_MIN_KERNEL_AND_KEXT_ADDRESS) {
		vm_map_offset_t map_addr;
		kern_return_t kr;
 
		vmk_flags = VM_MAP_KERNEL_FLAGS_NONE;
		vmk_flags.vmkf_no_pmap_check = TRUE;

		map_addr = VM_MIN_KERNEL_AND_KEXT_ADDRESS;
		kr = vm_map_enter(kernel_map,
				  &map_addr, 
				  (vm_map_size_t)(map_start - VM_MIN_KERNEL_AND_KEXT_ADDRESS),
				  (vm_map_offset_t) 0,
				  VM_FLAGS_FIXED,
				  vmk_flags,
				  VM_KERN_MEMORY_NONE,
				  VM_OBJECT_NULL, 
				  (vm_object_offset_t) 0, FALSE,
				  VM_PROT_NONE, VM_PROT_NONE,
				  VM_INHERIT_DEFAULT);
		
		if (kr != KERN_SUCCESS) {
			panic("kmem_init(0x%llx,0x%llx): vm_map_enter(0x%llx,0x%llx) error 0x%x\n",
			      (uint64_t) start, (uint64_t) end,
			      (uint64_t) VM_MIN_KERNEL_AND_KEXT_ADDRESS,
			      (uint64_t) (map_start - VM_MIN_KERNEL_AND_KEXT_ADDRESS),
			      kr);
		}	
	}
#endif

	/*
	 * Set the default global user wire limit which limits the amount of
	 * memory that can be locked via mlock().  We set this to the total
	 * amount of memory that are potentially usable by a user app (max_mem)
	 * minus a certain amount.  This can be overridden via a sysctl.
	 */
	vm_global_no_user_wire_amount = MIN(max_mem*20/100,
					    VM_NOT_USER_WIREABLE);
	vm_global_user_wire_limit = max_mem - vm_global_no_user_wire_amount;
	
	/* the default per user limit is the same as the global limit */
	vm_user_wire_limit = vm_global_user_wire_limit;
}