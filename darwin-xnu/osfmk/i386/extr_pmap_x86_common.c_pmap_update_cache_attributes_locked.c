#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_map_offset_t ;
typedef  TYPE_1__* pv_rooted_entry_t ;
typedef  TYPE_2__* pv_hashed_entry_t ;
typedef  int /*<<< orphan*/  pt_entry_t ;
typedef  int /*<<< orphan*/  ppnum_t ;
typedef  scalar_t__ pmap_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_6__ {int /*<<< orphan*/  qlink; } ;
struct TYPE_5__ {scalar_t__ pmap; } ;

/* Variables and functions */
 unsigned int INTEL_EPT_CACHE_MASK ; 
 unsigned int INTEL_EPT_NCACHE ; 
 unsigned int INTEL_EPT_WB ; 
 unsigned int INTEL_PTE_NCACHE ; 
 int IS_MANAGED_PAGE (int /*<<< orphan*/ ) ; 
 scalar_t__ PAGE_SIZE ; 
 unsigned int PHYS_CACHEABILITY_MASK ; 
 scalar_t__ PMAP_NULL ; 
 int /*<<< orphan*/  PMAP_UPDATE_TLBS (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ PVE_VA (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  is_ept_pmap (scalar_t__) ; 
 int /*<<< orphan*/  kernel_pmap ; 
 TYPE_1__* pai_to_pvh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmap_pte (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pmap_update_pte (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 scalar_t__ queue_next (int /*<<< orphan*/ *) ; 

void
pmap_update_cache_attributes_locked(ppnum_t pn, unsigned attributes) {
	pv_rooted_entry_t	pv_h, pv_e;
	pv_hashed_entry_t       pvh_e, nexth;
	vm_map_offset_t vaddr;
	pmap_t	pmap;
	pt_entry_t	*ptep;
	boolean_t	is_ept;
	unsigned	ept_attributes;
	
	assert(IS_MANAGED_PAGE(pn));
	assert(((~PHYS_CACHEABILITY_MASK) & attributes) == 0);

	/* We don't support the PTA bit for EPT PTEs */
	if (attributes & INTEL_PTE_NCACHE)
		ept_attributes = INTEL_EPT_NCACHE;
	else
		ept_attributes = INTEL_EPT_WB;

	pv_h = pai_to_pvh(pn);
	/* TODO: translate the PHYS_* bits to PTE bits, while they're
	 * currently identical, they may not remain so
	 * Potential optimization (here and in page_protect),
	 * parallel shootdowns, check for redundant
	 * attribute modifications.
	 */
	
	/*
	 * Alter attributes on all mappings
	 */
	if (pv_h->pmap != PMAP_NULL) {
		pv_e = pv_h;
		pvh_e = (pv_hashed_entry_t)pv_e;

		do {
			pmap = pv_e->pmap;
			vaddr = PVE_VA(pv_e);
			ptep = pmap_pte(pmap, vaddr);
			
			if (0 == ptep)
				panic("pmap_update_cache_attributes_locked: Missing PTE, pmap: %p, pn: 0x%x vaddr: 0x%llx kernel_pmap: %p", pmap, pn, vaddr, kernel_pmap);

			is_ept = is_ept_pmap(pmap);

			nexth = (pv_hashed_entry_t)queue_next(&pvh_e->qlink);
			if (!is_ept) {
				pmap_update_pte(ptep, PHYS_CACHEABILITY_MASK, attributes);
			} else {
				pmap_update_pte(ptep, INTEL_EPT_CACHE_MASK, ept_attributes);
			}
			PMAP_UPDATE_TLBS(pmap, vaddr, vaddr + PAGE_SIZE);
			pvh_e = nexth;
		} while ((pv_e = (pv_rooted_entry_t)nexth) != pv_h);
	}
}