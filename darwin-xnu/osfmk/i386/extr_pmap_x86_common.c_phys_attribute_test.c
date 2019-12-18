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
typedef  int /*<<< orphan*/  vm_map_offset_t ;
typedef  TYPE_1__* pv_rooted_entry_t ;
typedef  TYPE_2__* pv_hashed_entry_t ;
typedef  int pt_entry_t ;
typedef  scalar_t__ ppnum_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_6__ {int /*<<< orphan*/  qlink; int /*<<< orphan*/  pmap; } ;
struct TYPE_5__ {scalar_t__ pmap; } ;

/* Variables and functions */
 int INTEL_EPT_MOD ; 
 int INTEL_EPT_REF ; 
 int /*<<< orphan*/  IS_MANAGED_PAGE (int) ; 
 int /*<<< orphan*/  LOCK_PVH (int) ; 
 int PHYS_MODIFIED ; 
 int PHYS_REFERENCED ; 
 scalar_t__ PMAP_NULL ; 
 int /*<<< orphan*/  PVE_VA (TYPE_2__*) ; 
 int /*<<< orphan*/  UNLOCK_PVH (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int ept_refmod_to_physmap (int) ; 
 int /*<<< orphan*/  is_ept_pmap (int /*<<< orphan*/ ) ; 
 TYPE_1__* pai_to_pvh (int) ; 
 int /*<<< orphan*/  pmap_intr_assert () ; 
 int* pmap_phys_attributes ; 
 int* pmap_pte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ppn_to_pai (scalar_t__) ; 
 scalar_t__ queue_next (int /*<<< orphan*/ *) ; 
 scalar_t__ vm_page_fictitious_addr ; 
 scalar_t__ vm_page_guard_addr ; 

int
phys_attribute_test(
	ppnum_t		pn,
	int		bits)
{
	pv_rooted_entry_t	pv_h;
	pv_hashed_entry_t	pv_e;
	pt_entry_t		*pte;
	int			pai;
	pmap_t			pmap;
	int			attributes = 0;
	boolean_t		is_ept;

	pmap_intr_assert();
	assert(pn != vm_page_fictitious_addr);
	assert((bits & ~(PHYS_MODIFIED | PHYS_REFERENCED)) == 0);
	if (pn == vm_page_guard_addr)
		return 0;

	pai = ppn_to_pai(pn);

	if (!IS_MANAGED_PAGE(pai)) {
		/*
		 *	Not a managed page.
		 */
		return 0;
	}

	/*
	 * Fast check...  if bits already collected
	 * no need to take any locks...
	 * if not set, we need to recheck after taking
	 * the lock in case they got pulled in while
	 * we were waiting for the lock
	 */
	if ((pmap_phys_attributes[pai] & bits) == bits)
		return bits;

	pv_h = pai_to_pvh(pai);

	LOCK_PVH(pai);

	attributes = pmap_phys_attributes[pai] & bits;


	/*
	 * Walk down PV list, checking the mappings until we
	 * reach the end or we've found the desired attributes.
	 */
	if (attributes != bits &&
	    pv_h->pmap != PMAP_NULL) {
		/*
		 * There are some mappings.
		 */
		pv_e = (pv_hashed_entry_t)pv_h;
		do {
			vm_map_offset_t va;

			pmap = pv_e->pmap;
			is_ept = is_ept_pmap(pmap);
			va = PVE_VA(pv_e);
			/*
	 		 * pick up modify and/or reference bits from mapping
			 */

			pte = pmap_pte(pmap, va);
			if (!is_ept) {
				attributes |= (int)(*pte & bits);
			} else {
				attributes |= (int)(ept_refmod_to_physmap((*pte & (INTEL_EPT_REF | INTEL_EPT_MOD))) & (PHYS_MODIFIED | PHYS_REFERENCED));

			}

			pv_e = (pv_hashed_entry_t)queue_next(&pv_e->qlink);

		} while ((attributes != bits) &&
			 (pv_e != (pv_hashed_entry_t)pv_h));
	}
	pmap_phys_attributes[pai] |= attributes;

	UNLOCK_PVH(pai);
	return (attributes);
}