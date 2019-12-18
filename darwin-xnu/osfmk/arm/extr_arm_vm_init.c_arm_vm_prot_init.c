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
typedef  int vm_offset_t ;
typedef  int pt_entry_t ;
typedef  scalar_t__ pmap_paddr_t ;
struct TYPE_3__ {scalar_t__ topOfKernelData; } ;
typedef  TYPE_1__ boot_args ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  AP_RONA ; 
 int ARM_PGBYTES ; 
 int ARM_PTE_AP (int /*<<< orphan*/ ) ; 
 int ARM_PTE_APMASK ; 
 int ARM_TT_L2_INDEX_MASK ; 
 int ARM_TT_L2_SHIFT ; 
 int /*<<< orphan*/  FALSE ; 
 int HIGH_EXC_VECTORS ; 
 int PAGE_MAX_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  arm_vm_page_granular_RNX (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_vm_page_granular_ROX (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_vm_page_granular_RWNX (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_vm_page_granular_RWX (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ doconstro ; 
 int end_kern ; 
 int /*<<< orphan*/  fiqstack_high_guard ; 
 int gVirtBase ; 
 int /*<<< orphan*/  intstack_high_guard ; 
 int /*<<< orphan*/  intstack_low_guard ; 
 int phystokv (scalar_t__) ; 
 int sectCONSTB ; 
 int sectSizeCONST ; 
 int segBOOTDATAB ; 
 int segDATAB ; 
 int segEXTRADATA ; 
 int /*<<< orphan*/  segKLDB ; 
 int segLASTB ; 
 int segLINKB ; 
 int segPRELINKTEXTB ; 
 int segSizeBOOTDATA ; 
 int segSizeDATA ; 
 int segSizeEXTRADATA ; 
 int /*<<< orphan*/  segSizeKLD ; 
 int segSizeLAST ; 
 int segSizeLINK ; 
 int segSizePRELINKTEXT ; 
 int segSizeTEXT ; 
 int segTEXTB ; 
 int static_memory_end ; 

void
arm_vm_prot_init(boot_args * args)
{
#if __ARM_PTE_PHYSMAP__
	boolean_t force_coarse_physmap = TRUE;
#else
	boolean_t force_coarse_physmap = FALSE;
#endif
	/*
	 * Enforce W^X protections on segments that have been identified so far. This will be
	 * further refined for each KEXT's TEXT and DATA segments in readPrelinkedExtensions() 
	 */
	
	/*
	 * Protection on kernel text is loose here to allow shenanigans early on (e.g. copying exception vectors)
	 * and storing an address into "error_buffer" (see arm_init.c) !?!
	 * These protections are tightened in arm_vm_prot_finalize()
	 */
	arm_vm_page_granular_RWX(gVirtBase, segSizeTEXT + (segTEXTB - gVirtBase), FALSE);

	if (doconstro) {
		/*
		 * We map __DATA with 3 calls, so that the __const section can have its
		 * protections changed independently of the rest of the __DATA segment.
		 */
		arm_vm_page_granular_RWNX(segDATAB, sectCONSTB - segDATAB, FALSE);
		arm_vm_page_granular_RNX(sectCONSTB, sectSizeCONST, FALSE);
		arm_vm_page_granular_RWNX(sectCONSTB + sectSizeCONST, (segDATAB + segSizeDATA) - (sectCONSTB + sectSizeCONST), FALSE);
	} else {
		/* If we aren't protecting const, just map DATA as a single blob. */
		arm_vm_page_granular_RWNX(segDATAB, segSizeDATA, FALSE);
	}
	arm_vm_page_granular_RWNX(segBOOTDATAB, segSizeBOOTDATA, TRUE);
	arm_vm_page_granular_RNX((vm_offset_t)&intstack_low_guard, PAGE_MAX_SIZE, TRUE);
	arm_vm_page_granular_RNX((vm_offset_t)&intstack_high_guard, PAGE_MAX_SIZE, TRUE);
	arm_vm_page_granular_RNX((vm_offset_t)&fiqstack_high_guard, PAGE_MAX_SIZE, TRUE);

	arm_vm_page_granular_ROX(segKLDB, segSizeKLD, force_coarse_physmap);
	arm_vm_page_granular_RWNX(segLINKB, segSizeLINK, force_coarse_physmap);
	arm_vm_page_granular_RWNX(segLASTB, segSizeLAST, FALSE); // __LAST may be empty, but we cannot assume this
	arm_vm_page_granular_RWNX(segPRELINKTEXTB, segSizePRELINKTEXT, TRUE); // Refined in OSKext::readPrelinkedExtensions
	arm_vm_page_granular_RWNX(segPRELINKTEXTB + segSizePRELINKTEXT,
	                             end_kern - (segPRELINKTEXTB + segSizePRELINKTEXT), force_coarse_physmap); // PreLinkInfoDictionary
	arm_vm_page_granular_RWNX(end_kern, phystokv(args->topOfKernelData) - end_kern, force_coarse_physmap); // Device Tree, RAM Disk (if present), bootArgs, trust caches
	arm_vm_page_granular_RNX(segEXTRADATA, segSizeEXTRADATA, FALSE); // tighter trust cache protection
	arm_vm_page_granular_RWNX(phystokv(args->topOfKernelData), ARM_PGBYTES * 8, FALSE); // boot_tte, cpu_tte

	/*
	 * FIXME: Any page table pages that arm_vm_page_granular_* created with ROX entries in the range
	 * phystokv(args->topOfKernelData) to phystokv(prot_avail_start) should themselves be
	 * write protected in the static mapping of that range.
	 * [Page table pages whose page table entries grant execute (X) privileges should themselves be
	 * marked read-only. This aims to thwart attacks that replace the X entries with vectors to evil code
	 * (relying on some thread of execution to eventually arrive at what previously was a trusted routine).]
	 */
	arm_vm_page_granular_RWNX(phystokv(args->topOfKernelData) + ARM_PGBYTES * 8, ARM_PGBYTES, FALSE); /* Excess physMem over 1MB */
	arm_vm_page_granular_RWX(phystokv(args->topOfKernelData) + ARM_PGBYTES * 9, ARM_PGBYTES, FALSE); /* refined in finalize */

	/* Map the remainder of xnu owned memory. */
	arm_vm_page_granular_RWNX(phystokv(args->topOfKernelData) + ARM_PGBYTES * 10,
	                          static_memory_end - (phystokv(args->topOfKernelData) + ARM_PGBYTES * 10), force_coarse_physmap); /* rest of physmem */

	/*
	 * Special case write protection for the mapping of ExceptionVectorsBase (EVB) at 0xFFFF0000.
	 * Recall that start.s handcrafted a page table page for EVB mapping
	 */
	pmap_paddr_t p = (pmap_paddr_t)(args->topOfKernelData) + (ARM_PGBYTES * 9);
	pt_entry_t *ppte = (pt_entry_t *)phystokv(p);

	int idx = (HIGH_EXC_VECTORS & ARM_TT_L2_INDEX_MASK) >> ARM_TT_L2_SHIFT;
	pt_entry_t ptmp = ppte[idx];

	ptmp = (ptmp & ~ARM_PTE_APMASK) | ARM_PTE_AP(AP_RONA);

	ppte[idx] = ptmp;
}