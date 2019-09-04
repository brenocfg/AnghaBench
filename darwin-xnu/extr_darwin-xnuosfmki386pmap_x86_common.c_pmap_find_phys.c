#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int pt_entry_t ;
typedef  scalar_t__ ppnum_t ;
typedef  TYPE_1__* pmap_t ;
typedef  int pd_entry_t ;
typedef  int /*<<< orphan*/  boolean_t ;
typedef  int /*<<< orphan*/  addr64_t ;
struct TYPE_6__ {int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int* PD_ENTRY_NULL ; 
 int PTE_PS ; 
 int PTE_VALID_MASK (int /*<<< orphan*/ ) ; 
 int* PT_ENTRY_NULL ; 
 scalar_t__ i386_btop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_ept_pmap (TYPE_1__*) ; 
 int /*<<< orphan*/  mp_disable_preemption () ; 
 int /*<<< orphan*/  mp_enable_preemption () ; 
 int* pmap_pde (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int* pmap_pte (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_to_pa (int) ; 
 scalar_t__ ptenum (int /*<<< orphan*/ ) ; 

ppnum_t
pmap_find_phys(pmap_t pmap, addr64_t va)
{
	pt_entry_t	*ptp;
	pd_entry_t	*pdep;
	ppnum_t		ppn = 0;
	pd_entry_t	pde;
	pt_entry_t	pte;
	boolean_t	is_ept;

	is_ept = is_ept_pmap(pmap);

	mp_disable_preemption();

	/* This refcount test is a band-aid--several infrastructural changes
	 * are necessary to eliminate invocation of this routine from arbitrary
	 * contexts.
	 */
	
	if (!pmap->ref_count)
		goto pfp_exit;

	pdep = pmap_pde(pmap, va);

	if ((pdep != PD_ENTRY_NULL) && ((pde = *pdep) & PTE_VALID_MASK(is_ept))) {
		if (pde & PTE_PS) {
			ppn = (ppnum_t) i386_btop(pte_to_pa(pde));
			ppn += (ppnum_t) ptenum(va);
		}
		else {
			ptp = pmap_pte(pmap, va);
			if ((PT_ENTRY_NULL != ptp) && (((pte = *ptp) & PTE_VALID_MASK(is_ept)) != 0)) {
				ppn = (ppnum_t) i386_btop(pte_to_pa(pte));
			}
		}
	}
pfp_exit:	
	mp_enable_preemption();

        return ppn;
}