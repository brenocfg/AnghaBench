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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_TTE_EMPTY ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  _COMM_PAGE32_BASE_ADDRESS ; 
 int /*<<< orphan*/  _COMM_PAGE64_BASE_ADDRESS ; 
 int /*<<< orphan*/  flush_mmu_tlb_region_asid_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_pmap ; 
 scalar_t__ pmap_is_64bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_tlb_flush () ; 

__attribute__((used)) static void
pmap_unmap_sharedpage(
	pmap_t pmap)
{
	pt_entry_t *ttep;
	vm_offset_t sharedpage_vaddr;

#if _COMM_PAGE_AREA_LENGTH != PAGE_SIZE
#error We assume a single page.
#endif

	if (pmap_is_64bit(pmap)) {
		sharedpage_vaddr = _COMM_PAGE64_BASE_ADDRESS;
	} else {
		sharedpage_vaddr = _COMM_PAGE32_BASE_ADDRESS;
	}

#if (ARM_PGSHIFT == 12)
#if __ARM64_TWO_LEVEL_PMAP__
#error A two level page table with a page shift of 12 is not currently supported
#endif
	ttep = pmap_tt1e(pmap, sharedpage_vaddr);

	if (ttep == NULL) {
		return;
	}

	/* It had better be mapped to the shared page */
	if (*ttep != ARM_TTE_EMPTY && *ttep != *pmap_tt1e(sharedpage_pmap, sharedpage_vaddr)) {
		panic("%s: Something other than commpage mapped in shared page slot?", __FUNCTION__);
	}
#elif (ARM_PGSHIFT == 14)
	ttep = pmap_tt2e(pmap, sharedpage_vaddr);

	if (ttep == NULL) {
		return;
	}

	/* It had better be mapped to the shared page */
	if (*ttep != ARM_TTE_EMPTY && *ttep != *pmap_tt2e(sharedpage_pmap, sharedpage_vaddr)) {
		panic("%s: Something other than commpage mapped in shared page slot?", __FUNCTION__);
	}
#endif

	*ttep = ARM_TTE_EMPTY;
	flush_mmu_tlb_region_asid_async(sharedpage_vaddr, PAGE_SIZE, kernel_pmap);

#if (ARM_PGSHIFT == 12)
#if __ARM64_TWO_LEVEL_PMAP__
#error A two level page table with a page shift of 12 is not currently supported
#endif
	flush_mmu_tlb_entry_async(tlbi_addr(sharedpage_vaddr & ~ARM_TT_L1_OFFMASK) | tlbi_asid(pmap->asid));
#elif (ARM_PGSHIFT == 14)
	flush_mmu_tlb_entry_async(tlbi_addr(sharedpage_vaddr & ~ARM_TT_L2_OFFMASK) | tlbi_asid(pmap->asid));
#endif
	sync_tlb_flush();
}