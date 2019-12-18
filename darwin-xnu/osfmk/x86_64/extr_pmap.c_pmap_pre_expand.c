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
typedef  int /*<<< orphan*/  pt_entry_t ;
typedef  int /*<<< orphan*/  ppnum_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int INTEL_EPT_EX ; 
 int INTEL_PTE_USER ; 
 int /*<<< orphan*/ * PDPT_ENTRY_NULL ; 
 int /*<<< orphan*/ * PD_ENTRY_NULL ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int PTE_READ (scalar_t__) ; 
 int PTE_WRITE (scalar_t__) ; 
 scalar_t__ PT_ENTRY_NULL ; 
 int /*<<< orphan*/  i386_ptob (int /*<<< orphan*/ ) ; 
 scalar_t__ is_ept_pmap (int /*<<< orphan*/ ) ; 
 int pa_to_pte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/ * pmap64_pde (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmap64_pdpt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmap64_pml4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmap64_user_pml4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_next_page_hi (int /*<<< orphan*/ *) ; 
 scalar_t__ pmap_pte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_store_pte (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pmap_zero_page (int /*<<< orphan*/ ) ; 

void
pmap_pre_expand(pmap_t pmap, vm_map_offset_t vaddr)
{
	ppnum_t pn;
	pt_entry_t		*pte;
	boolean_t		is_ept = is_ept_pmap(pmap);

	PMAP_LOCK(pmap);

	if(pmap64_pdpt(pmap, vaddr) == PDPT_ENTRY_NULL) {
		if (!pmap_next_page_hi(&pn))
			panic("pmap_pre_expand");

		pmap_zero_page(pn);

		pte = pmap64_pml4(pmap, vaddr);

		pmap_store_pte(pte, pa_to_pte(i386_ptob(pn))
				| PTE_READ(is_ept)
				| (is_ept ? INTEL_EPT_EX : INTEL_PTE_USER)
				| PTE_WRITE(is_ept));

		pte = pmap64_user_pml4(pmap, vaddr);

		pmap_store_pte(pte, pa_to_pte(i386_ptob(pn))
				| PTE_READ(is_ept)
				| (is_ept ? INTEL_EPT_EX : INTEL_PTE_USER)
				| PTE_WRITE(is_ept));

	}

	if(pmap64_pde(pmap, vaddr) == PD_ENTRY_NULL) {
		if (!pmap_next_page_hi(&pn))
			panic("pmap_pre_expand");

		pmap_zero_page(pn);

		pte = pmap64_pdpt(pmap, vaddr);

		pmap_store_pte(pte, pa_to_pte(i386_ptob(pn))
				| PTE_READ(is_ept)
				| (is_ept ? INTEL_EPT_EX : INTEL_PTE_USER)
				| PTE_WRITE(is_ept));
	}

	if(pmap_pte(pmap, vaddr) == PT_ENTRY_NULL) {
		if (!pmap_next_page_hi(&pn))
			panic("pmap_pre_expand");

		pmap_zero_page(pn);

		pte = pmap64_pde(pmap, vaddr);

		pmap_store_pte(pte, pa_to_pte(i386_ptob(pn))
				| PTE_READ(is_ept)
				| (is_ept ? INTEL_EPT_EX : INTEL_PTE_USER)
				| PTE_WRITE(is_ept));
	}

	PMAP_UNLOCK(pmap);
}