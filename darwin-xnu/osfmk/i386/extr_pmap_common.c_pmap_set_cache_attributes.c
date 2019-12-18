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
typedef  scalar_t__ ppnum_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_MANAGED_PAGE (int) ; 
 int /*<<< orphan*/  LOCK_PVH (int) ; 
 unsigned int PHYS_CACHEABILITY_MASK ; 
 unsigned int PHYS_NCACHE ; 
 unsigned int PHYS_PTA ; 
 int /*<<< orphan*/  UNLOCK_PVH (int) ; 
 unsigned int VM_MEM_GUARDED ; 
 unsigned int VM_MEM_NOT_CACHEABLE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pmap_intr_assert () ; 
 unsigned int* pmap_phys_attributes ; 
 int /*<<< orphan*/  pmap_sync_page_attributes_phys (scalar_t__) ; 
 int /*<<< orphan*/  pmap_update_cache_attributes_locked (scalar_t__,unsigned int) ; 
 int ppn_to_pai (scalar_t__) ; 
 scalar_t__ vm_page_fictitious_addr ; 
 scalar_t__ vm_page_guard_addr ; 

void	pmap_set_cache_attributes(ppnum_t pn, unsigned int cacheattr) {
	unsigned int current, template = 0;
	int pai;

	if (cacheattr & VM_MEM_NOT_CACHEABLE) {
		if(!(cacheattr & VM_MEM_GUARDED))
			template |= PHYS_PTA;
		template |= PHYS_NCACHE;
	}

	pmap_intr_assert();

	assert((pn != vm_page_fictitious_addr) && (pn != vm_page_guard_addr));

	pai = ppn_to_pai(pn);

	if (!IS_MANAGED_PAGE(pai)) {
		return;
	}

	/* override cache attributes for this phys page
	 * Does not walk through existing mappings to adjust,
	 * assumes page is disconnected
	 */

	LOCK_PVH(pai);

	pmap_update_cache_attributes_locked(pn, template);

	current = pmap_phys_attributes[pai] & PHYS_CACHEABILITY_MASK;
	pmap_phys_attributes[pai] &= ~PHYS_CACHEABILITY_MASK;
	pmap_phys_attributes[pai] |= template;

	UNLOCK_PVH(pai);

	if ((template & PHYS_NCACHE) && !(current & PHYS_NCACHE)) {
		pmap_sync_page_attributes_phys(pn);
	}
}