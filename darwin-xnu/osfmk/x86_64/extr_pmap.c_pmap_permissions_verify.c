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
typedef  int /*<<< orphan*/  vm_region_recurse_info_t ;
typedef  int vm_prot_t ;
typedef  int vm_offset_t ;
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct vm_region_submap_info_64 {int protection; scalar_t__ is_submap; } ;
typedef  int pt_entry_t ;
typedef  int /*<<< orphan*/  ppnum_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int mach_vm_size_t ;
typedef  int /*<<< orphan*/  mach_vm_address_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 int INTEL_PTE_NX ; 
 int INTEL_PTE_VALID ; 
 int INTEL_PTE_WRITE ; 
 scalar_t__ KERN_FAILURE ; 
 scalar_t__ KERN_SUCCESS ; 
 int NBPD ; 
 int NBPML4 ; 
 int PAGE_MASK_64 ; 
 scalar_t__ PAGE_SIZE ; 
 int PDMASK ; 
 int PML4MASK ; 
 int VM_PROT_EXECUTE ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  VM_REGION_SUBMAP_INFO_COUNT_64 ; 
 scalar_t__ __improbable (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ i386_btop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_ept_pmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 scalar_t__ mach_vm_region_recurse (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pmap64_pde (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * pmap64_pdpt (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * pmap64_pml4 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ pmap_pde (int /*<<< orphan*/ ,int) ; 
 int* pmap_pte (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmap_valid_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_to_pa (int) ; 

kern_return_t
pmap_permissions_verify(pmap_t ipmap, vm_map_t ivmmap, vm_offset_t sv, vm_offset_t ev) {
	vm_offset_t cv = sv;
	kern_return_t rv = KERN_SUCCESS;
	uint64_t skip4 = 0, skip2 = 0;

	assert(!is_ept_pmap(ipmap));

	sv &= ~PAGE_MASK_64;
	ev &= ~PAGE_MASK_64;
	while (cv < ev) {
		if (__improbable((cv > 0x00007FFFFFFFFFFFULL) &&
			(cv < 0xFFFF800000000000ULL))) {
			cv = 0xFFFF800000000000ULL;
		}
		/* Potential inconsistencies from not holding pmap lock
		 * but harmless for the moment.
		 */
		if (((cv & PML4MASK) == 0) && (pmap64_pml4(ipmap, cv) == 0)) {
			if ((cv + NBPML4) > cv)
				cv += NBPML4;
			else
				break;
			skip4++;
			continue;
		}
		if (((cv & PDMASK) == 0) && (pmap_pde(ipmap, cv) == 0)) {
			if ((cv + NBPD) > cv)
				cv += NBPD;
			else
				break;
			skip2++;
			continue;
		}

		pt_entry_t *ptep = pmap_pte(ipmap, cv);
		if (ptep && (*ptep & INTEL_PTE_VALID)) {
			if (*ptep & INTEL_PTE_WRITE) {
				if (!(*ptep & INTEL_PTE_NX)) {
					kprintf("W+X PTE at 0x%lx, P4: 0x%llx, P3: 0x%llx, P2: 0x%llx, PT: 0x%llx, VP: %u\n", cv, *pmap64_pml4(ipmap, cv), *pmap64_pdpt(ipmap, cv), *pmap64_pde(ipmap, cv), *ptep, pmap_valid_page((ppnum_t)(i386_btop(pte_to_pa(*ptep)))));
					rv = KERN_FAILURE;
				}
			}
		}
		cv += PAGE_SIZE;
	}
	kprintf("Completed pmap scan\n");
	cv = sv;

	struct vm_region_submap_info_64 vbr;
	mach_msg_type_number_t vbrcount = 0;
	mach_vm_size_t	vmsize;
	vm_prot_t	prot;
	uint32_t nesting_depth = 0;
	kern_return_t kret;
	
	while (cv < ev) {
		
		for (;;) {
			vbrcount = VM_REGION_SUBMAP_INFO_COUNT_64;
			if((kret = mach_vm_region_recurse(ivmmap, 
				    (mach_vm_address_t *) &cv, &vmsize, &nesting_depth, 
					(vm_region_recurse_info_t)&vbr,
					&vbrcount)) != KERN_SUCCESS) {
				break;
			}

			if(vbr.is_submap) {
				nesting_depth++;
				continue;
			} else {
				break;
			}
		}

		if(kret != KERN_SUCCESS)
			break;

		prot = vbr.protection;

		if ((prot & (VM_PROT_WRITE | VM_PROT_EXECUTE)) == (VM_PROT_WRITE | VM_PROT_EXECUTE)) {
			kprintf("W+X map entry at address 0x%lx\n", cv);
			rv = KERN_FAILURE;
		}

		if (prot) {
			vm_offset_t pcv;
			for (pcv = cv; pcv < cv + vmsize; pcv += PAGE_SIZE) {
				pt_entry_t *ptep = pmap_pte(ipmap, pcv);
				vm_prot_t tprot;

				if ((ptep == NULL) || !(*ptep & INTEL_PTE_VALID))
					continue;
				tprot = VM_PROT_READ;
				if (*ptep & INTEL_PTE_WRITE)
					tprot |= VM_PROT_WRITE;
				if ((*ptep & INTEL_PTE_NX) == 0)
					tprot |= VM_PROT_EXECUTE;
				if (tprot != prot) {
					kprintf("PTE/map entry permissions mismatch at address 0x%lx, pte: 0x%llx, protection: 0x%x\n", pcv, *ptep, prot);
					rv = KERN_FAILURE;
				}
			}
		}
		cv += vmsize;
	}
	return rv;
}