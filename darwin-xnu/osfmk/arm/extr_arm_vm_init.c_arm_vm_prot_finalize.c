#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  topOfKernelData; } ;
typedef  TYPE_1__ boot_args ;

/* Variables and functions */
 int ARM_PGBYTES ; 
 int /*<<< orphan*/  BootCpuData ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FlushPoC_Dcache () ; 
 int /*<<< orphan*/  arm_vm_page_granular_ROX (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_vm_page_granular_RWNX (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_stack_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_mmu_tlb () ; 
 scalar_t__ gVirtBase ; 
 int /*<<< orphan*/  ml_static_mfree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ phystokv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  segBOOTDATAB ; 
 int /*<<< orphan*/  segSizeBOOTDATA ; 
 scalar_t__ segSizeTEXT ; 
 scalar_t__ segTEXTB ; 

void
arm_vm_prot_finalize(boot_args * args)
{
	cpu_stack_alloc(&BootCpuData);
	ml_static_mfree(segBOOTDATAB, segSizeBOOTDATA);
	/*
	 * Naively we could have:
	 * arm_vm_page_granular_ROX(segTEXTB, segSizeTEXT, FALSE);
	 * but, at present, that would miss a 1Mb boundary at the beginning of the segment and
	 * so would force a (wasteful) coarse page (e.g. when gVirtBase is 0x80000000, segTEXTB is 0x80001000).
	 */
	arm_vm_page_granular_ROX(gVirtBase, segSizeTEXT + (segTEXTB - gVirtBase), FALSE);

	arm_vm_page_granular_RWNX(phystokv(args->topOfKernelData) + ARM_PGBYTES * 9, ARM_PGBYTES, FALSE); /* commpage, EVB */

#ifndef  __ARM_L1_PTW__
	FlushPoC_Dcache();
#endif
	flush_mmu_tlb();
}