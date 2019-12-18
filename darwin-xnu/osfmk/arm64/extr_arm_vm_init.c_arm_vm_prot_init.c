#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
struct TYPE_4__ {int /*<<< orphan*/  topOfKernelData; } ;
typedef  TYPE_1__ boot_args ;
struct TYPE_5__ {int length; int /*<<< orphan*/  paddr; } ;
typedef  TYPE_2__ MemoryMapFileInfo ;
typedef  int /*<<< orphan*/  DTEntry ;

/* Variables and functions */
 int BOOTSTRAP_TABLE_SIZE ; 
 int DTGetProperty (int /*<<< orphan*/ ,char*,void**,unsigned int*) ; 
 int DTLookupEntry (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int PAGE_MAX_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ UINT64_MAX ; 
 int /*<<< orphan*/  arm_vm_page_granular_RNX (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_vm_page_granular_ROX (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_vm_page_granular_RWNX (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_vm_page_granular_RWX (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  excepstack_high_guard ; 
 int /*<<< orphan*/  intstack_high_guard ; 
 int /*<<< orphan*/  intstack_low_guard ; 
 int kSuccess ; 
 scalar_t__ phystokv (int /*<<< orphan*/ ) ; 
 scalar_t__ segBOOTDATAB ; 
 scalar_t__ segDATAB ; 
 scalar_t__ segDATACONSTB ; 
 scalar_t__ segEXTRADATA ; 
 int /*<<< orphan*/  segKLDB ; 
 int /*<<< orphan*/  segLASTB ; 
 scalar_t__ segLINKB ; 
 scalar_t__ segLOWESTTEXT ; 
 scalar_t__ segPLKDATACONSTB ; 
 scalar_t__ segPLKLINKEDITB ; 
 scalar_t__ segPLKLLVMCOVB ; 
 int /*<<< orphan*/  segPLKTEXTEXECB ; 
 scalar_t__ segPRELINKDATAB ; 
 scalar_t__ segPRELINKINFOB ; 
 scalar_t__ segPRELINKTEXTB ; 
 scalar_t__ segSizeBOOTDATA ; 
 scalar_t__ segSizeDATA ; 
 scalar_t__ segSizeDATACONST ; 
 int segSizeEXTRADATA ; 
 int /*<<< orphan*/  segSizeKLD ; 
 int /*<<< orphan*/  segSizeLAST ; 
 scalar_t__ segSizeLINK ; 
 scalar_t__ segSizePLKDATACONST ; 
 scalar_t__ segSizePLKLINKEDIT ; 
 scalar_t__ segSizePLKLLVMCOV ; 
 int /*<<< orphan*/  segSizePLKTEXTEXEC ; 
 scalar_t__ segSizePRELINKDATA ; 
 scalar_t__ segSizePRELINKINFO ; 
 scalar_t__ segSizePRELINKTEXT ; 
 int segSizeTEXT ; 
 int /*<<< orphan*/  segSizeTEXTEXEC ; 
 scalar_t__ segTEXTB ; 
 int /*<<< orphan*/  segTEXTEXECB ; 

void
arm_vm_prot_init(boot_args * args)
{

	segLOWESTTEXT = UINT64_MAX;
	if (segSizePRELINKTEXT  && (segPRELINKTEXTB < segLOWESTTEXT)) segLOWESTTEXT = segPRELINKTEXTB;
	assert(segSizeTEXT);
	if (segTEXTB < segLOWESTTEXT) segLOWESTTEXT = segTEXTB;
	assert(segLOWESTTEXT < UINT64_MAX);

	segEXTRADATA = segLOWESTTEXT;
	segSizeEXTRADATA = 0;

	DTEntry memory_map;
	MemoryMapFileInfo *trustCacheRange;
	unsigned int trustCacheRangeSize;
	int err;

	err = DTLookupEntry(NULL, "chosen/memory-map", &memory_map);
	assert(err == kSuccess);

	err = DTGetProperty(memory_map, "TrustCache", (void**)&trustCacheRange, &trustCacheRangeSize);
	if (err == kSuccess) {
		assert(trustCacheRangeSize == sizeof(MemoryMapFileInfo));

		segEXTRADATA = phystokv(trustCacheRange->paddr);
		segSizeEXTRADATA = trustCacheRange->length;

		arm_vm_page_granular_RNX(segEXTRADATA, segSizeEXTRADATA, FALSE);
	}

	/* Map coalesced kext TEXT segment RWNX for now */
	arm_vm_page_granular_RWNX(segPRELINKTEXTB, segSizePRELINKTEXT, FALSE); // Refined in OSKext::readPrelinkedExtensions

	/* Map coalesced kext DATA_CONST segment RWNX (could be empty) */
	arm_vm_page_granular_RWNX(segPLKDATACONSTB, segSizePLKDATACONST, FALSE); // Refined in OSKext::readPrelinkedExtensions

	/* Map coalesced kext TEXT_EXEC segment RWX (could be empty) */
	arm_vm_page_granular_ROX(segPLKTEXTEXECB, segSizePLKTEXTEXEC, FALSE); // Refined in OSKext::readPrelinkedExtensions

	/* if new segments not present, set space between PRELINK_TEXT and xnu TEXT to RWNX
	 * otherwise we no longer expect any space between the coalesced kext read only segments and xnu rosegments
	 */
	if (!segSizePLKDATACONST && !segSizePLKTEXTEXEC) {
		if (segSizePRELINKTEXT)
			arm_vm_page_granular_RWNX(segPRELINKTEXTB + segSizePRELINKTEXT, segTEXTB - (segPRELINKTEXTB + segSizePRELINKTEXT), FALSE);
	} else {
		/*
		 * If we have the new segments, we should still protect the gap between kext
		 * read-only pages and kernel read-only pages, in the event that this gap
		 * exists.
		 */
		if ((segPLKDATACONSTB + segSizePLKDATACONST) < segTEXTB) {
			arm_vm_page_granular_RWNX(segPLKDATACONSTB + segSizePLKDATACONST, segTEXTB - (segPLKDATACONSTB + segSizePLKDATACONST), FALSE);
		}
	}

	/*
	 * Protection on kernel text is loose here to allow shenanigans early on.  These
	 * protections are tightened in arm_vm_prot_finalize().  This is necessary because
	 * we currently patch LowResetVectorBase in cpu.c.
	 *
	 * TEXT segment contains mach headers and other non-executable data. This will become RONX later.
	 */
	arm_vm_page_granular_RNX(segTEXTB, segSizeTEXT, FALSE);

	/* Can DATACONST start out and stay RNX?
	 * NO, stuff in this segment gets modified during startup (viz. mac_policy_init()/mac_policy_list)
	 * Make RNX in prot_finalize
	 */
	arm_vm_page_granular_RWNX(segDATACONSTB, segSizeDATACONST, FALSE);

	/* TEXTEXEC contains read only executable code: becomes ROX in prot_finalize */
	arm_vm_page_granular_RWX(segTEXTEXECB, segSizeTEXTEXEC, FALSE);


	/* DATA segment will remain RWNX */
	arm_vm_page_granular_RWNX(segDATAB, segSizeDATA, FALSE);

	arm_vm_page_granular_RWNX(segBOOTDATAB, segSizeBOOTDATA, TRUE);
	arm_vm_page_granular_RNX((vm_offset_t)&intstack_low_guard, PAGE_MAX_SIZE, TRUE);
	arm_vm_page_granular_RNX((vm_offset_t)&intstack_high_guard, PAGE_MAX_SIZE, TRUE);
	arm_vm_page_granular_RNX((vm_offset_t)&excepstack_high_guard, PAGE_MAX_SIZE, TRUE);

	arm_vm_page_granular_ROX(segKLDB, segSizeKLD, FALSE);
	arm_vm_page_granular_RWNX(segLINKB, segSizeLINK, FALSE);
	arm_vm_page_granular_RWNX(segPLKLINKEDITB, segSizePLKLINKEDIT, FALSE); // Coalesced kext LINKEDIT segment
	arm_vm_page_granular_ROX(segLASTB, segSizeLAST, FALSE); // __LAST may be empty, but we cannot assume this

	arm_vm_page_granular_RWNX(segPRELINKDATAB, segSizePRELINKDATA, FALSE); // Prelink __DATA for kexts (RW data)

	if (segSizePLKLLVMCOV > 0)
		arm_vm_page_granular_RWNX(segPLKLLVMCOVB, segSizePLKLLVMCOV, FALSE); // LLVM code coverage data

	arm_vm_page_granular_RWNX(segPRELINKINFOB, segSizePRELINKINFO, FALSE); /* PreLinkInfoDictionary */

	arm_vm_page_granular_RNX(phystokv(args->topOfKernelData), BOOTSTRAP_TABLE_SIZE, FALSE); // Boot page tables; they should not be mutable.
}