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
typedef  int vm_prot_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  vm_map_address_t ;
typedef  int pt_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  AP_RONA ; 
 int /*<<< orphan*/  AP_RWNA ; 
 int ARM_PTE_AF ; 
 int ARM_PTE_AP (int /*<<< orphan*/ ) ; 
 int ARM_PTE_ATTRINDX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARM_PTE_IS_COMPRESSED (int) ; 
 int ARM_PTE_NG ; 
 int ARM_PTE_NX ; 
 int ARM_PTE_PNX ; 
 int ARM_PTE_TYPE ; 
 int /*<<< orphan*/  CACHE_ATTRINDX_DISABLE ; 
 scalar_t__ PAGE_SIZE ; 
 int* PT_ENTRY_NULL ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  WRITE_PTE_STRONG (int*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  flush_mmu_tlb_region (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int pa_to_pte (scalar_t__) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int* pmap_pte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_increment_pa (int) ; 

vm_map_address_t
pmap_map_bd(
	vm_map_address_t virt,
	vm_offset_t start,
	vm_offset_t end,
	vm_prot_t prot)
{
	pt_entry_t      tmplate;
	pt_entry_t		*ptep;
	vm_map_address_t vaddr;
	vm_offset_t		paddr;

	/* not cacheable and not buffered */
	tmplate = pa_to_pte(start)
	          | ARM_PTE_TYPE | ARM_PTE_AF | ARM_PTE_NX | ARM_PTE_PNX
	          | ARM_PTE_AP((prot & VM_PROT_WRITE) ? AP_RWNA : AP_RONA)
	          | ARM_PTE_ATTRINDX(CACHE_ATTRINDX_DISABLE);
#if __ARM_KERNEL_PROTECT__
	tmplate |= ARM_PTE_NG;
#endif /* __ARM_KERNEL_PROTECT__ */

	vaddr = virt;
	paddr = start;
	while (paddr < end) {

		ptep = pmap_pte(kernel_pmap, vaddr);
		if (ptep == PT_ENTRY_NULL) {
			panic("pmap_map_bd");
		}
		assert(!ARM_PTE_IS_COMPRESSED(*ptep));
		WRITE_PTE_STRONG(ptep, tmplate);

		pte_increment_pa(tmplate);
		vaddr += PAGE_SIZE;
		paddr += PAGE_SIZE;
	}

	if (end >= start)
		flush_mmu_tlb_region(virt, (unsigned)(end - start));

	return (vaddr);
}