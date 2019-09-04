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

/* Variables and functions */
 int ARM_TTE_BLOCK_AP (int) ; 
 int ARM_TTE_BLOCK_APMASK ; 
 int ARM_TTE_BLOCK_NX ; 
 int ARM_TTE_BLOCK_NX_MASK ; 
 int ARM_TT_L1_PT_OFFMASK ; 
 scalar_t__ ARM_TT_L1_PT_SIZE ; 
 int /*<<< orphan*/  arm_vm_page_granular_helper (int,int,int,int,int) ; 
 int* cpu_tte ; 
 size_t ttenum (int) ; 

__attribute__((used)) static void
arm_vm_page_granular_prot(vm_offset_t start, unsigned long size, 
                          int tte_prot_XN, int pte_prot_APX, int pte_prot_XN, int force_page_granule)
{
	vm_offset_t _end = start + size;
	vm_offset_t align_start = (start + ARM_TT_L1_PT_OFFMASK) & ~ARM_TT_L1_PT_OFFMASK;
	vm_offset_t align_end = _end & ~ARM_TT_L1_PT_OFFMASK;

	arm_vm_page_granular_helper(start, _end, start, pte_prot_APX, pte_prot_XN);

	while (align_start < align_end) {
		if (force_page_granule) {
			arm_vm_page_granular_helper(align_start, align_end, align_start + 1, 
			                            pte_prot_APX, pte_prot_XN);
		} else {
			tt_entry_t *tte = &cpu_tte[ttenum(align_start)];
			for (int i = 0; i < 4; ++i) {
				tt_entry_t tmplate = tte[i];

				tmplate = (tmplate & ~ARM_TTE_BLOCK_APMASK) | ARM_TTE_BLOCK_AP(pte_prot_APX);
				tmplate = (tmplate & ~ARM_TTE_BLOCK_NX_MASK);
				if (tte_prot_XN)
					tmplate = tmplate | ARM_TTE_BLOCK_NX;

				tte[i] = tmplate;
			}
		}
		align_start += ARM_TT_L1_PT_SIZE;
	}

	arm_vm_page_granular_helper(start, _end, _end, pte_prot_APX, pte_prot_XN);
}