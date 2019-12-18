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
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 unsigned long LARGE_PMD_SIZE ; 
 unsigned long PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 int PTRS_PER_PTE ; 
 int _PAGE_DIRTY ; 
 int /*<<< orphan*/  do_mm_track_phys (void*) ; 
 int /*<<< orphan*/  do_mm_track_pte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmd_large (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long pte_pfn (int /*<<< orphan*/ ) ; 
 int pte_val (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void do_mm_track_pmd(void *val)
{
	int i;
	pte_t *pte;
	pmd_t *pmd = (pmd_t *)val;

	if (!pmd_present(*pmd))
		return;

	if (unlikely(pmd_large(*pmd))) {
		unsigned long addr, end;

		if (!(pte_val(*(pte_t *)val) & _PAGE_DIRTY))
			return;

		addr = pte_pfn(*(pte_t *)val) << PAGE_SHIFT;
		end = addr + LARGE_PMD_SIZE;

		while (addr < end) {
			do_mm_track_phys((void *)addr);
			addr +=  PAGE_SIZE;
		}
		return;
	}

	pte = pte_offset_kernel(pmd, 0);

	for (i = 0; i < PTRS_PER_PTE; i++, pte++)
		do_mm_track_pte(pte);
}