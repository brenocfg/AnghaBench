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
typedef  int /*<<< orphan*/  vm_map_offset_t ;
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int pmap_t ;
typedef  int pd_entry_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int addr64_t ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int INTEL_PDPTE_NESTED ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int NBPDE ; 
 scalar_t__ NBPDPT ; 
 scalar_t__ NPDEPG ; 
 int PDESHIFT ; 
 int PMAP_CODE (int /*<<< orphan*/ ) ; 
 int PMAP_INVALID_PDPTNUM ; 
 int /*<<< orphan*/  PMAP_LOCK (int) ; 
 int /*<<< orphan*/  PMAP_TRACE (int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int) ; 
 int /*<<< orphan*/  PMAP_UPDATE_TLBS (int,int,int) ; 
 int /*<<< orphan*/  PMAP__UNNEST ; 
 int /*<<< orphan*/  VM_KERNEL_ADDRHIDE (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ cpu_64bit ; 
 int /*<<< orphan*/  is_ept_pmap (int) ; 
 int /*<<< orphan*/  panic (char*,int,int,...) ; 
 int pdptnum (int,int) ; 
 int* pmap64_pdpt (int,int) ; 
 int pmap_nesting_size_min ; 
 int* pmap_pde (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_store_pte (int*,int) ; 

kern_return_t pmap_unnest(pmap_t grand, addr64_t vaddr, uint64_t size) {
	pd_entry_t *pde;
	unsigned int i;
	uint64_t num_pde;
	addr64_t va_start, va_end;
	uint64_t npdpt = PMAP_INVALID_PDPTNUM;

	PMAP_TRACE(PMAP_CODE(PMAP__UNNEST) | DBG_FUNC_START,
	           VM_KERNEL_ADDRHIDE(grand), VM_KERNEL_ADDRHIDE(vaddr));

	if ((size & (pmap_nesting_size_min-1)) ||
	    (vaddr & (pmap_nesting_size_min-1))) {
		panic("pmap_unnest(%p,0x%llx,0x%llx): unaligned...\n",
		    grand, vaddr, size);
	}

	assert(!is_ept_pmap(grand));

	/* align everything to PDE boundaries */
	va_start = vaddr & ~(NBPDE-1);
	va_end = (vaddr + size + NBPDE - 1) & ~(NBPDE-1);
	size = va_end - va_start;

	PMAP_LOCK(grand);

	num_pde = size >> PDESHIFT;
	vaddr = va_start;

	for (i = 0; i < num_pde; ) {
		if ((pdptnum(grand, vaddr) != npdpt) && cpu_64bit) {
			npdpt = pdptnum(grand, vaddr);
			pde = pmap64_pdpt(grand, vaddr);
			if (pde && (*pde & INTEL_PDPTE_NESTED)) {
				pmap_store_pte(pde, (pd_entry_t)0);
				i += (uint32_t) NPDEPG;
				vaddr += NBPDPT;
				continue;
			}
		}
		pde = pmap_pde(grand, (vm_map_offset_t)vaddr);
		if (pde == 0)
			panic("pmap_unnest: no pde, grand %p vaddr 0x%llx\n", grand, vaddr);
		pmap_store_pte(pde, (pd_entry_t)0);
		i++;
		vaddr += NBPDE;
	}

	PMAP_UPDATE_TLBS(grand, va_start, va_end);

	PMAP_UNLOCK(grand);

	PMAP_TRACE(PMAP_CODE(PMAP__UNNEST) | DBG_FUNC_END, KERN_SUCCESS);

	return KERN_SUCCESS;
}