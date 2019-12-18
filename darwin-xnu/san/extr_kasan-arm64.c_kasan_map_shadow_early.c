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
typedef  int vm_address_t ;
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  AP_RONA ; 
 int /*<<< orphan*/  AP_RWNA ; 
 scalar_t__ ARM_PGBYTES ; 
 int ARM_PTE_AF ; 
 int ARM_PTE_AP (int /*<<< orphan*/ ) ; 
 int ARM_PTE_APMASK ; 
 int ARM_PTE_ATTRINDX (int /*<<< orphan*/ ) ; 
 int ARM_PTE_NX ; 
 int ARM_PTE_PNX ; 
 int ARM_PTE_SH (int /*<<< orphan*/ ) ; 
 int ARM_PTE_TYPE ; 
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
 int /*<<< orphan*/  __nosan_bzero (void*,scalar_t__) ; 
 int /*<<< orphan*/  align_to_page (scalar_t__*,scalar_t__*) ; 
 int alloc_page () ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ bootstrap_pgtable_phys ; 
 int /*<<< orphan*/  flush_mmu_tlb () ; 
 scalar_t__ zero_page_phys ; 

__attribute__((used)) static void
kasan_map_shadow_early(vm_offset_t address, vm_size_t size, bool is_zero)
{
	align_to_page(&address, &size);

	vm_size_t j;
	uint64_t *pte;

	for (j = 0; j < size; j += ARM_PGBYTES) {
		vm_offset_t virt_shadow_target = (vm_offset_t)SHADOW_FOR_ADDRESS(address + j);

		assert(virt_shadow_target >= KASAN_SHADOW_MIN);
		assert(virt_shadow_target < KASAN_SHADOW_MAX);

		uint64_t *base = (uint64_t *)bootstrap_pgtable_phys;

#if !__ARM64_TWO_LEVEL_PMAP__
		/* lookup L1 entry */
		pte = base + ((virt_shadow_target & ARM_TT_L1_INDEX_MASK) >> ARM_TT_L1_SHIFT);
		if (*pte & ARM_TTE_VALID) {
			assert((*pte & ARM_TTE_TYPE_MASK) == ARM_TTE_TYPE_TABLE);
		} else {
			/* create new L1 table */
			vm_address_t pg = alloc_page();
			__nosan_bzero((void *)pg, ARM_PGBYTES);
			*pte = ((uint64_t)pg & ARM_TTE_TABLE_MASK) | ARM_TTE_VALID | ARM_TTE_TYPE_TABLE;
		}
		base = (uint64_t *)(*pte & ARM_TTE_TABLE_MASK);
#endif

		/* lookup L2 entry */
		pte = base + ((virt_shadow_target & ARM_TT_L2_INDEX_MASK) >> ARM_TT_L2_SHIFT);
		if (*pte & ARM_TTE_VALID) {
			assert((*pte & ARM_TTE_TYPE_MASK) == ARM_TTE_TYPE_TABLE);
		} else {
			/* create new L3 table */
			vm_address_t pg = alloc_page();
			__nosan_bzero((void *)pg, ARM_PGBYTES);
			*pte = ((uint64_t)pg & ARM_TTE_TABLE_MASK) | ARM_TTE_VALID | ARM_TTE_TYPE_TABLE;
		}
		base = (uint64_t *)(*pte & ARM_TTE_TABLE_MASK);

		/* lookup L3 entry */
		pte = base + ((virt_shadow_target & ARM_TT_L3_INDEX_MASK) >> ARM_TT_L3_SHIFT);

		if ((*pte & (ARM_PTE_TYPE|ARM_PTE_APMASK)) == (ARM_PTE_TYPE_VALID|ARM_PTE_AP(AP_RWNA))) {
			/* L3 entry valid and mapped RW - do nothing */
		} else {
			/* Not mapped, or mapped RO - create new L3 entry or upgrade to RW */

			uint64_t newpte;
			if (is_zero) {
				/* map the zero page RO */
				newpte = (uint64_t)zero_page_phys | ARM_PTE_AP(AP_RONA);
			} else {
				/* map a fresh page RW */
				vm_address_t pg = alloc_page();
				__nosan_bzero((void *)pg, ARM_PGBYTES);
				newpte = pg | ARM_PTE_AP(AP_RWNA);
			}

			/* add the default attributes */
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