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
typedef  scalar_t__ vm_size_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  KMEM_FREE_CODE ; 
 int /*<<< orphan*/  KMEM_FREE_CODE_2 ; 
 int /*<<< orphan*/  TRACE_MACHLEAKS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  VM_MAP_PAGE_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_MAP_REMOVE_KUNWIRE ; 
 scalar_t__ VM_MIN_KERNEL_AND_KEXT_ADDRESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_round_page (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_trunc_page (scalar_t__,int /*<<< orphan*/ ) ; 

void
kmem_free(
	vm_map_t	map,
	vm_offset_t	addr,
	vm_size_t	size)
{
	kern_return_t kr;

	assert(addr >= VM_MIN_KERNEL_AND_KEXT_ADDRESS);

	TRACE_MACHLEAKS(KMEM_FREE_CODE, KMEM_FREE_CODE_2, size, addr);

	if(size == 0) {
#if MACH_ASSERT
		printf("kmem_free called with size==0 for map: %p with addr: 0x%llx\n",map,(uint64_t)addr);
#endif
		return;
	}

	kr = vm_map_remove(map,
			   vm_map_trunc_page(addr,
					     VM_MAP_PAGE_MASK(map)),
			   vm_map_round_page(addr + size,
					     VM_MAP_PAGE_MASK(map)), 
			   VM_MAP_REMOVE_KUNWIRE);
	if (kr != KERN_SUCCESS)
		panic("kmem_free");
}