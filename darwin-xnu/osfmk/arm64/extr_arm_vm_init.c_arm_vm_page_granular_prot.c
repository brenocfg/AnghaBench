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
typedef  int vm_offset_t ;
typedef  int tt_entry_t ;
typedef  int /*<<< orphan*/  pt_entry_t ;
typedef  int pmap_paddr_t ;

/* Variables and functions */
 int ARM_TTE_BLOCK_AF ; 
 int ARM_TTE_BLOCK_AP (int) ; 
 int ARM_TTE_BLOCK_ATTRINDX (int /*<<< orphan*/ ) ; 
 int ARM_TTE_BLOCK_L2_MASK ; 
 int ARM_TTE_BLOCK_NG ; 
 int ARM_TTE_BLOCK_NX ; 
 int ARM_TTE_BLOCK_PNX ; 
 int ARM_TTE_BLOCK_SH (int /*<<< orphan*/ ) ; 
 int ARM_TTE_TYPE_BLOCK ; 
 int ARM_TTE_VALID ; 
 int ARM_TT_L2_OFFMASK ; 
 int ARM_TT_L2_SIZE ; 
 int /*<<< orphan*/  CACHE_ATTRINDX_WRITEBACK ; 
 int /*<<< orphan*/  SH_OUTER_MEMORY ; 
 int* arm_kva_to_tte (int) ; 
 int /*<<< orphan*/  arm_vm_page_granular_helper (int,int,int,int,int,int,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int gPhysBase ; 
 int gVirtBase ; 
 int real_avail_end ; 

__attribute__((used)) static void
arm_vm_page_granular_prot(vm_offset_t start, unsigned long size, pmap_paddr_t pa_offset,
                          int tte_prot_XN, int pte_prot_APX, int pte_prot_XN,
                          bool force_page_granule)
{
	pt_entry_t *deferred_pte = NULL, deferred_ptmp = 0;
	vm_offset_t _end = start + size;
	vm_offset_t align_start = (start + ARM_TT_L2_OFFMASK) & ~ARM_TT_L2_OFFMASK;

	if (size == 0x0UL)
		return;

	if (align_start > _end) {
		arm_vm_page_granular_helper(start, _end, start, pa_offset, pte_prot_APX, pte_prot_XN, force_page_granule, NULL, NULL);
		return;
	}

	arm_vm_page_granular_helper(start, align_start, start, pa_offset, pte_prot_APX, pte_prot_XN, force_page_granule, &deferred_pte, &deferred_ptmp);

	while ((_end - align_start) >= ARM_TT_L2_SIZE) {
		if (force_page_granule)
			arm_vm_page_granular_helper(align_start, align_start+ARM_TT_L2_SIZE, align_start + 1, pa_offset,
			                            pte_prot_APX, pte_prot_XN, force_page_granule, NULL, NULL);
		else {
			pmap_paddr_t pa = align_start - gVirtBase + gPhysBase - pa_offset;
			assert((pa & ARM_TT_L2_OFFMASK) == 0); 
			tt_entry_t *tte2;
			tt_entry_t tmplate;

			tte2 = arm_kva_to_tte(align_start);

			if ((pa >= gPhysBase) && (pa < real_avail_end)) {
				tmplate = (pa & ARM_TTE_BLOCK_L2_MASK) | ARM_TTE_TYPE_BLOCK
					| ARM_TTE_VALID | ARM_TTE_BLOCK_AF | ARM_TTE_BLOCK_NX
					| ARM_TTE_BLOCK_AP(pte_prot_APX) | ARM_TTE_BLOCK_SH(SH_OUTER_MEMORY)
					| ARM_TTE_BLOCK_ATTRINDX(CACHE_ATTRINDX_WRITEBACK);
				
#if __ARM_KERNEL_PROTECT__
				tmplate = tmplate | ARM_TTE_BLOCK_NG;
#endif /* __ARM_KERNEL_PROTECT__ */
				if (tte_prot_XN)
					tmplate = tmplate | ARM_TTE_BLOCK_PNX;

				*tte2 = tmplate;
			}
		}
		align_start += ARM_TT_L2_SIZE;
	}

	if (align_start < _end)
		arm_vm_page_granular_helper(align_start, _end, _end, pa_offset, pte_prot_APX, pte_prot_XN, force_page_granule, &deferred_pte, &deferred_ptmp);

	if (deferred_pte != NULL)
		*deferred_pte = deferred_ptmp;
}