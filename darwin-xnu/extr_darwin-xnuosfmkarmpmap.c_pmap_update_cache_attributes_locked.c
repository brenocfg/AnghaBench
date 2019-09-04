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
typedef  int /*<<< orphan*/  vm_map_address_t ;
typedef  int /*<<< orphan*/  pv_entry_t ;
typedef  int pt_entry_t ;
typedef  int /*<<< orphan*/  ppnum_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/  pmap_paddr_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int ARM_PTE_ATTRINDXMASK ; 
 int ARM_PTE_SHMASK ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int* PT_ENTRY_NULL ; 
 int /*<<< orphan*/ * PVE_NEXT_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PVH_TYPE_PTEP ; 
 int /*<<< orphan*/  PVH_TYPE_PVEP ; 
 int /*<<< orphan*/ * PV_ENTRY_NULL ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WRITE_PTE_STRONG (int*,int) ; 
 int /*<<< orphan*/  flush_mmu_tlb_region_asid_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pa_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** pai_to_pvh (unsigned int) ; 
 int /*<<< orphan*/  ptep_get_pmap (int*) ; 
 int /*<<< orphan*/  ptep_get_va (int*) ; 
 int /*<<< orphan*/  ptoa (int /*<<< orphan*/ ) ; 
 int* pve_get_ptep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pve_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pvh_list (int /*<<< orphan*/ **) ; 
 int* pvh_ptep (int /*<<< orphan*/ **) ; 
 scalar_t__ pvh_test_type (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_tlb_flush () ; 
 int wimg_to_pte (unsigned int) ; 

void
pmap_update_cache_attributes_locked(
	ppnum_t ppnum,
	unsigned attributes)
{
	pmap_paddr_t    phys = ptoa(ppnum);
	pv_entry_t      *pve_p;
	pt_entry_t      *pte_p;
	pv_entry_t      **pv_h;
	pt_entry_t      tmplate;
	unsigned int    pai;
	boolean_t       tlb_flush_needed = FALSE;

#if __ARM_PTE_PHYSMAP__
	vm_offset_t kva = phystokv(phys);
	pte_p = pmap_pte(kernel_pmap, kva);

	tmplate = *pte_p;
	tmplate &= ~(ARM_PTE_ATTRINDXMASK | ARM_PTE_SHMASK);
	tmplate |= wimg_to_pte(attributes);
#if (__ARM_VMSA__ > 7)
	if (tmplate & ARM_PTE_HINT_MASK) {
		panic("%s: physical aperture PTE %p has hint bit set, va=%p, pte=0x%llx",
		      __FUNCTION__, pte_p, (void *)kva, tmplate);
	}
#endif
	WRITE_PTE_STRONG(pte_p, tmplate);
	flush_mmu_tlb_region_asid_async(kva, PAGE_SIZE, kernel_pmap);
	tlb_flush_needed = TRUE;
#endif

	pai = (unsigned int)pa_index(phys);

	pv_h = pai_to_pvh(pai);

	pte_p = PT_ENTRY_NULL;
	pve_p = PV_ENTRY_NULL;
	if (pvh_test_type(pv_h, PVH_TYPE_PTEP)) {
		pte_p = pvh_ptep(pv_h);
	} else if  (pvh_test_type(pv_h, PVH_TYPE_PVEP)) {
		pve_p = pvh_list(pv_h);
		pte_p = PT_ENTRY_NULL;
	}

	while ((pve_p != PV_ENTRY_NULL) || (pte_p != PT_ENTRY_NULL)) {
		vm_map_address_t va;
		pmap_t          pmap;

		if (pve_p != PV_ENTRY_NULL)
			pte_p = pve_get_ptep(pve_p);
#ifdef PVH_FLAG_IOMMU
		if ((vm_offset_t)pte_p & PVH_FLAG_IOMMU)
			goto cache_skip_pve;
#endif
		pmap = ptep_get_pmap(pte_p);
		va = ptep_get_va(pte_p);

		tmplate = *pte_p;
		tmplate &= ~(ARM_PTE_ATTRINDXMASK | ARM_PTE_SHMASK);
		tmplate |= wimg_to_pte(attributes);

		WRITE_PTE_STRONG(pte_p, tmplate);
		flush_mmu_tlb_region_asid_async(va, PAGE_SIZE, pmap);
		tlb_flush_needed = TRUE;

#ifdef PVH_FLAG_IOMMU
	cache_skip_pve:
#endif
		pte_p = PT_ENTRY_NULL;
		if (pve_p != PV_ENTRY_NULL)
			pve_p = PVE_NEXT_PTR(pve_next(pve_p));

	}
	if (tlb_flush_needed)
		sync_tlb_flush();
}