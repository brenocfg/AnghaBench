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
typedef  int vm_prot_t ;
typedef  int vm_offset_t ;
typedef  scalar_t__ vm_map_address_t ;
typedef  scalar_t__ pv_entry_t ;
typedef  scalar_t__ pt_entry_t ;
typedef  int /*<<< orphan*/  ppnum_t ;
typedef  TYPE_1__* pmap_t ;
typedef  int /*<<< orphan*/  pmap_paddr_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_5__ {scalar_t__ min; scalar_t__ max; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_RWNA ; 
 int /*<<< orphan*/  AP_RWRW ; 
 scalar_t__ ARM_PTE_AF ; 
 scalar_t__ ARM_PTE_AP (int /*<<< orphan*/ ) ; 
 scalar_t__ ARM_PTE_APMASK ; 
 scalar_t__ ARM_PTE_EMPTY ; 
 scalar_t__ ARM_PTE_TYPE_FAULT ; 
 int /*<<< orphan*/  ASSERT_PVH_LOCKED (int) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  ISB_SY ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PP_ATTR_MODIFIED ; 
 int PP_ATTR_REFERENCED ; 
 scalar_t__* PT_ENTRY_NULL ; 
 scalar_t__* PVE_NEXT_PTR (int /*<<< orphan*/ ) ; 
 int PVH_FLAG_IOMMU ; 
 int /*<<< orphan*/  PVH_TYPE_PTEP ; 
 int /*<<< orphan*/  PVH_TYPE_PVEP ; 
 scalar_t__* PV_ENTRY_NULL ; 
 scalar_t__ TRUE ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  WRITE_PTE (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  WRITE_PTE_STRONG (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  __builtin_arm_isb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  flush_mmu_tlb_region_asid_async (scalar_t__,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* kernel_pmap ; 
 scalar_t__ pa_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_set_bits (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pa_valid (int /*<<< orphan*/ ) ; 
 scalar_t__** pai_to_pvh (int) ; 
 int /*<<< orphan*/  panic (char*,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ pte_is_ffr (scalar_t__) ; 
 int /*<<< orphan*/  pte_set_ffr (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* ptep_get_pmap (scalar_t__*) ; 
 scalar_t__ ptep_get_va (scalar_t__*) ; 
 int /*<<< orphan*/  ptoa (int /*<<< orphan*/ ) ; 
 scalar_t__* pve_get_ptep (scalar_t__*) ; 
 int /*<<< orphan*/  pve_next (scalar_t__*) ; 
 scalar_t__* pvh_list (scalar_t__**) ; 
 scalar_t__* pvh_ptep (scalar_t__**) ; 
 scalar_t__ pvh_test_type (scalar_t__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_tlb_flush () ; 
 int /*<<< orphan*/  vm_page_fictitious_addr ; 

boolean_t
arm_clear_fast_fault(
	ppnum_t ppnum,
	vm_prot_t fault_type)
{
	pmap_paddr_t    pa = ptoa(ppnum);
	pv_entry_t     *pve_p;
	pt_entry_t     *pte_p;
	int             pai;
	boolean_t       result;
	boolean_t	tlb_flush_needed = FALSE;
	pv_entry_t    **pv_h;

	assert(ppnum != vm_page_fictitious_addr);

	if (!pa_valid(pa)) {
		return FALSE;	/* Not a managed page. */
	}

	result = FALSE;
	pai = (int)pa_index(pa);
	ASSERT_PVH_LOCKED(pai);
	pv_h = pai_to_pvh(pai);

	pte_p = PT_ENTRY_NULL;
	pve_p = PV_ENTRY_NULL;
	if (pvh_test_type(pv_h, PVH_TYPE_PTEP))	{
		pte_p = pvh_ptep(pv_h);
	} else if  (pvh_test_type(pv_h, PVH_TYPE_PVEP)) {
		pve_p = pvh_list(pv_h);
	}

	while ((pve_p != PV_ENTRY_NULL) || (pte_p != PT_ENTRY_NULL)) {
		vm_map_address_t va;
		pt_entry_t		spte;
		pt_entry_t      tmplate;
		pmap_t          pmap;

		if (pve_p != PV_ENTRY_NULL)
			pte_p = pve_get_ptep(pve_p);

		if (pte_p == PT_ENTRY_NULL) {
			panic("pte_p is NULL: pve_p=%p ppnum=0x%x\n", pve_p, ppnum);
		}
#ifdef PVH_FLAG_IOMMU
		if ((vm_offset_t)pte_p & PVH_FLAG_IOMMU) {
			goto cff_skip_pve;
		} 
#endif
		if (*pte_p == ARM_PTE_EMPTY) {
			panic("pte is NULL: pte_p=%p ppnum=0x%x\n", pte_p, ppnum);
		}

		pmap = ptep_get_pmap(pte_p);
		va = ptep_get_va(pte_p);

		assert(va >= pmap->min && va < pmap->max);

		spte = *pte_p;
		tmplate = spte;

		if ((fault_type & VM_PROT_WRITE) && (pte_is_ffr(spte))) {
			{
				if (pmap == kernel_pmap)
					tmplate = ((spte & ~ARM_PTE_APMASK) | ARM_PTE_AP(AP_RWNA));
				else
					tmplate = ((spte & ~ARM_PTE_APMASK) | ARM_PTE_AP(AP_RWRW));
			}

			tmplate |= ARM_PTE_AF;

			pte_set_ffr(tmplate, 0);
			pa_set_bits(pa, PP_ATTR_REFERENCED | PP_ATTR_MODIFIED);

		} else if ((fault_type & VM_PROT_READ) && ((spte & ARM_PTE_AF) != ARM_PTE_AF)) {
			tmplate = spte | ARM_PTE_AF;

			{
				pa_set_bits(pa, PP_ATTR_REFERENCED);
			}
		}


		if (spte != tmplate) {
			if (spte != ARM_PTE_TYPE_FAULT) {
				WRITE_PTE_STRONG(pte_p, tmplate);
				flush_mmu_tlb_region_asid_async(va, PAGE_SIZE, pmap);
				tlb_flush_needed = TRUE;
			} else {
				WRITE_PTE(pte_p, tmplate);
				__builtin_arm_isb(ISB_SY);
			}
			result = TRUE;
		}

#ifdef PVH_FLAG_IOMMU
	cff_skip_pve:
#endif
		pte_p = PT_ENTRY_NULL;
		if (pve_p != PV_ENTRY_NULL)
			pve_p = PVE_NEXT_PTR(pve_next(pve_p));
	}
	if (tlb_flush_needed)
		sync_tlb_flush();
	return result;
}