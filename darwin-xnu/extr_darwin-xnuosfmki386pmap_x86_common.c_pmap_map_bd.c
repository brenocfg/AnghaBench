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
typedef  scalar_t__ vm_map_offset_t ;
typedef  int pt_entry_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int INTEL_PTE_MOD ; 
 int INTEL_PTE_NCACHE ; 
 int INTEL_PTE_NX ; 
 int INTEL_PTE_PTA ; 
 int INTEL_PTE_REF ; 
 int INTEL_PTE_VALID ; 
 int INTEL_PTE_WIRED ; 
 int INTEL_PTE_WRITE ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PMAP_UPDATE_TLBS (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int* PT_ENTRY_NULL ; 
 scalar_t__ TRUE ; 
 unsigned int VM_MEM_GUARDED ; 
 unsigned int VM_MEM_NOT_CACHEABLE ; 
 int VM_PROT_EXECUTE ; 
 int VM_PROT_WRITE ; 
 unsigned int VM_WIMG_USE_DEFAULT ; 
 int /*<<< orphan*/  flush_tlb_raw () ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int pa_to_pte (scalar_t__) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int* pmap_pte (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pmap_store_pte (int*,int) ; 
 int /*<<< orphan*/  pte_increment_pa (int) ; 
 scalar_t__ pte_to_pa (int) ; 

vm_offset_t
pmap_map_bd(
	vm_offset_t	virt,
	vm_map_offset_t	start_addr,
	vm_map_offset_t	end_addr,
	vm_prot_t	prot,
	unsigned int	flags)
{
	pt_entry_t	template;
	pt_entry_t	*ptep;

	vm_offset_t	base = virt;
	boolean_t	doflush = FALSE;

	template = pa_to_pte(start_addr)
		| INTEL_PTE_REF
		| INTEL_PTE_MOD
		| INTEL_PTE_WIRED
		| INTEL_PTE_VALID;

	if ((flags & (VM_MEM_NOT_CACHEABLE | VM_WIMG_USE_DEFAULT)) == VM_MEM_NOT_CACHEABLE) {
		template |= INTEL_PTE_NCACHE;
		if (!(flags & (VM_MEM_GUARDED)))
			template |= INTEL_PTE_PTA;
	}

	if ((prot & VM_PROT_EXECUTE) == 0)
		template |= INTEL_PTE_NX;

	if (prot & VM_PROT_WRITE)
		template |= INTEL_PTE_WRITE;

	while (start_addr < end_addr) {
		ptep = pmap_pte(kernel_pmap, (vm_map_offset_t)virt);
		if (ptep == PT_ENTRY_NULL) {
			panic("pmap_map_bd: Invalid kernel address");
		}
		if (pte_to_pa(*ptep)) {
			doflush = TRUE;
		}
		pmap_store_pte(ptep, template);
		pte_increment_pa(template);
		virt += PAGE_SIZE;
		start_addr += PAGE_SIZE;
	}
	if (doflush) {
		flush_tlb_raw();
		PMAP_UPDATE_TLBS(kernel_pmap, base, base + end_addr - start_addr);
	}
	return(virt);
}