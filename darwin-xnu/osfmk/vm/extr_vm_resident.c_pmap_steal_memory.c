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
typedef  int vm_size_t ;
typedef  int vm_offset_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  ppnum_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ KERN_SUCCESS ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  VM_PROT_NONE ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  VM_WIMG_USE_DEFAULT ; 
 int /*<<< orphan*/  kasan_notify_address (void*,int) ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  panic (char*,unsigned long,...) ; 
 scalar_t__ pmap_enter (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_next_page_hi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_pre_expand (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmap_virtual_space (scalar_t__*,scalar_t__*) ; 
 void* round_page (int) ; 
 scalar_t__ trunc_page (scalar_t__) ; 
 scalar_t__ virtual_space_end ; 
 scalar_t__ virtual_space_start ; 
 int /*<<< orphan*/  vm_page_stolen_count ; 
 int /*<<< orphan*/  vm_page_wire_count ; 

void *
pmap_steal_memory(
	vm_size_t size)
{
	kern_return_t kr;
	vm_offset_t addr, vaddr;
	ppnum_t phys_page;

	/*
	 *	We round the size to a round multiple.
	 */

	size = (size + sizeof (void *) - 1) &~ (sizeof (void *) - 1);

	/*
	 *	If this is the first call to pmap_steal_memory,
	 *	we have to initialize ourself.
	 */

	if (virtual_space_start == virtual_space_end) {
		pmap_virtual_space(&virtual_space_start, &virtual_space_end);

		/*
		 *	The initial values must be aligned properly, and
		 *	we don't trust the pmap module to do it right.
		 */

		virtual_space_start = round_page(virtual_space_start);
		virtual_space_end = trunc_page(virtual_space_end);
	}

	/*
	 *	Allocate virtual memory for this request.
	 */

	addr = virtual_space_start;
	virtual_space_start += size;

	//kprintf("pmap_steal_memory: %08lX - %08lX; size=%08lX\n", (long)addr, (long)virtual_space_start, (long)size);	/* (TEST/DEBUG) */

	/*
	 *	Allocate and map physical pages to back new virtual pages.
	 */

	for (vaddr = round_page(addr);
	     vaddr < addr + size;
	     vaddr += PAGE_SIZE) {

		if (!pmap_next_page_hi(&phys_page))
			panic("pmap_steal_memory() size: 0x%llx\n", (uint64_t)size);

		/*
		 *	XXX Logically, these mappings should be wired,
		 *	but some pmap modules barf if they are.
		 */
#if defined(__LP64__)
#ifdef	__arm64__
		/* ARM64_TODO: verify that we really don't need this */
#else
		pmap_pre_expand(kernel_pmap, vaddr);
#endif
#endif

		kr = pmap_enter(kernel_pmap, vaddr, phys_page,
		                VM_PROT_READ|VM_PROT_WRITE, VM_PROT_NONE,
		                VM_WIMG_USE_DEFAULT, FALSE);

		if (kr != KERN_SUCCESS) {
			panic("pmap_steal_memory() pmap_enter failed, vaddr=%#lx, phys_page=%u",
			      (unsigned long)vaddr, phys_page);
		}

		/*
		 * Account for newly stolen memory
		 */
		vm_page_wire_count++;
		vm_page_stolen_count++;
	}

#if KASAN
	kasan_notify_address(round_page(addr), size);
#endif
	return (void *) addr;
}