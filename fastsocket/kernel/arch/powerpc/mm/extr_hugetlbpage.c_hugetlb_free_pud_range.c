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
struct mmu_gather {int /*<<< orphan*/  mm; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pgd_t ;
typedef  int /*<<< orphan*/  hugepd_t ;

/* Variables and functions */
 unsigned long PGDIR_MASK ; 
 unsigned int PMD_SHIFT ; 
 int /*<<< orphan*/  free_hugepte_range (struct mmu_gather*,int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int get_slice_psize (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  hugetlb_free_pmd_range (struct mmu_gather*,int /*<<< orphan*/ *,unsigned long,unsigned long,unsigned long,unsigned long,unsigned int) ; 
 unsigned int mmu_psize_to_shift (unsigned int) ; 
 int /*<<< orphan*/  pgd_clear (int /*<<< orphan*/ *) ; 
 unsigned long pud_addr_end (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  pud_free_tlb (struct mmu_gather*,int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pud_none (int /*<<< orphan*/ ) ; 
 scalar_t__ pud_none_or_clear_bad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void hugetlb_free_pud_range(struct mmu_gather *tlb, pgd_t *pgd,
				   unsigned long addr, unsigned long end,
				   unsigned long floor, unsigned long ceiling)
{
	pud_t *pud;
	unsigned long next;
	unsigned long start;
	unsigned int shift;
	unsigned int psize = get_slice_psize(tlb->mm, addr);
	shift = mmu_psize_to_shift(psize);

	start = addr;
	pud = pud_offset(pgd, addr);
	do {
		next = pud_addr_end(addr, end);
		if (shift < PMD_SHIFT) {
			if (pud_none_or_clear_bad(pud))
				continue;
			hugetlb_free_pmd_range(tlb, pud, addr, next, floor,
					       ceiling, psize);
		} else {
			if (pud_none(*pud))
				continue;
			free_hugepte_range(tlb, (hugepd_t *)pud, psize);
		}
	} while (pud++, addr = next, addr != end);

	start &= PGDIR_MASK;
	if (start < floor)
		return;
	if (ceiling) {
		ceiling &= PGDIR_MASK;
		if (!ceiling)
			return;
	}
	if (end - 1 > ceiling - 1)
		return;

	pud = pud_offset(pgd, start);
	pgd_clear(pgd);
	pud_free_tlb(tlb, pud, start);
}