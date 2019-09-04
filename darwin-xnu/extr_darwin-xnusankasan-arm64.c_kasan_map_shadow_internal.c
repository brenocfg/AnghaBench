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
typedef  scalar_t__ vm_offset_t ;
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  AP_RONA ; 
 int /*<<< orphan*/  AP_RWNA ; 
 scalar_t__ ARM_PGBYTES ; 
 int /*<<< orphan*/  ARM_PGMASK ; 
 int ARM_PTE_AF ; 
 int ARM_PTE_AP (int /*<<< orphan*/ ) ; 
 int ARM_PTE_APMASK ; 
 int ARM_PTE_ATTRINDX (int /*<<< orphan*/ ) ; 
 int ARM_PTE_NX ; 
 int ARM_PTE_PNX ; 
 int ARM_PTE_SH (int /*<<< orphan*/ ) ; 
 int ARM_PTE_TYPE_VALID ; 
 int ARM_TTE_TABLE_MASK ; 
 int ARM_TTE_TYPE_MASK ; 
 int ARM_TTE_TYPE_TABLE ; 
 int ARM_TTE_VALID ; 
 scalar_t__ ARM_TT_L1_INDEX_MASK ; 
 scalar_t__ ARM_TT_L1_SHIFT ; 
 scalar_t__ ARM_TT_L2_INDEX_MASK ; 
 scalar_t__ ARM_TT_L2_SHIFT ; 
 scalar_t__ ARM_TT_L3_INDEX_MASK ; 
 scalar_t__ ARM_TT_L3_SHIFT ; 
 int /*<<< orphan*/  CACHE_ATTRINDX_DEFAULT ; 
 scalar_t__ KASAN_SHADOW_MAX ; 
 scalar_t__ KASAN_SHADOW_MIN ; 
 int /*<<< orphan*/  SHADOW_FOR_ADDRESS (scalar_t__) ; 
 int /*<<< orphan*/  SH_OUTER_MEMORY ; 
 scalar_t__ alloc_zero_page () ; 
 int /*<<< orphan*/  assert (int) ; 
 int* cpu_tte ; 
 int /*<<< orphan*/  flush_mmu_tlb () ; 
 scalar_t__ phystokv (int) ; 
 scalar_t__ vm_map_round_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_trunc_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zero_page_phys ; 

__attribute__((used)) static void
kasan_map_shadow_internal(vm_offset_t address, vm_size_t size, bool is_zero, bool back_page)
{
	size = (size + 0x7UL) & ~0x7UL;
	vm_offset_t shadow_base = vm_map_trunc_page(SHADOW_FOR_ADDRESS(address), ARM_PGMASK);
	vm_offset_t shadow_top = vm_map_round_page(SHADOW_FOR_ADDRESS(address + size), ARM_PGMASK);

	assert(shadow_base >= KASAN_SHADOW_MIN && shadow_top <= KASAN_SHADOW_MAX);
	assert((size & 0x7) == 0);

	for (; shadow_base < shadow_top; shadow_base += ARM_PGBYTES) {
		uint64_t *base = cpu_tte;
		uint64_t *pte;

#if !__ARM64_TWO_LEVEL_PMAP__
		/* lookup L1 entry */
		pte = base + ((shadow_base & ARM_TT_L1_INDEX_MASK) >> ARM_TT_L1_SHIFT);
		if (*pte & ARM_TTE_VALID) {
			assert((*pte & ARM_TTE_TYPE_MASK) == ARM_TTE_TYPE_TABLE);
		} else {
			/* create new L1 table */
			*pte = ((uint64_t)alloc_zero_page() & ARM_TTE_TABLE_MASK) | ARM_TTE_VALID | ARM_TTE_TYPE_TABLE;
		}
		base = (uint64_t *)phystokv(*pte & ARM_TTE_TABLE_MASK);
#endif

		/* lookup L2 entry */
		pte = base + ((shadow_base & ARM_TT_L2_INDEX_MASK) >> ARM_TT_L2_SHIFT);
		if (*pte & ARM_TTE_VALID) {
			assert((*pte & ARM_TTE_TYPE_MASK) == ARM_TTE_TYPE_TABLE);
		} else {
			/* create new L3 table */
			*pte = ((uint64_t)alloc_zero_page() & ARM_TTE_TABLE_MASK) | ARM_TTE_VALID | ARM_TTE_TYPE_TABLE;
		}
		base = (uint64_t *)phystokv(*pte & ARM_TTE_TABLE_MASK);

		if (!back_page) {
			continue;
		}

		/* lookup L3 entry */
		pte = base + ((shadow_base & ARM_TT_L3_INDEX_MASK) >> ARM_TT_L3_SHIFT);
		if ((*pte & ARM_PTE_TYPE_VALID) &&
		    ((((*pte) & ARM_PTE_APMASK) != ARM_PTE_AP(AP_RONA)) || is_zero)) {
			/* nothing to do - page already mapped and we are not
			 * upgrading */
		} else {
			/* create new L3 entry */
			uint64_t newpte;
			if (is_zero) {
				/* map the zero page RO */
				newpte = (uint64_t)zero_page_phys | ARM_PTE_AP(AP_RONA);
			} else {
				/* map a fresh page RW */
				newpte = (uint64_t)alloc_zero_page() | ARM_PTE_AP(AP_RWNA);
			}
			newpte |= ARM_PTE_TYPE_VALID
				| ARM_PTE_AF
				| ARM_PTE_SH(SH_OUTER_MEMORY)
				| ARM_PTE_ATTRINDX(CACHE_ATTRINDX_DEFAULT)
				| ARM_PTE_NX
				| ARM_PTE_PNX;
			*pte = newpte;
		}
	}

	flush_mmu_tlb();
}