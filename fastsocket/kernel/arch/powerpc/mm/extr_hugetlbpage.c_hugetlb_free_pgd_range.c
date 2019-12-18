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
typedef  int /*<<< orphan*/  pgd_t ;
typedef  int /*<<< orphan*/  hugepd_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long HUGEPD_MASK (unsigned int) ; 
 scalar_t__ HUGEPD_SIZE (unsigned int) ; 
 scalar_t__ PUD_SHIFT ; 
 int /*<<< orphan*/  free_hugepte_range (struct mmu_gather*,int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int get_slice_psize (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  hugetlb_free_pud_range (struct mmu_gather*,int /*<<< orphan*/ *,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/ * mmu_huge_psizes ; 
 scalar_t__ mmu_psize_to_shift (unsigned int) ; 
 unsigned long pgd_addr_end (unsigned long,unsigned long) ; 
 scalar_t__ pgd_none (int /*<<< orphan*/ ) ; 
 scalar_t__ pgd_none_or_clear_bad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pgd_offset (int /*<<< orphan*/ ,unsigned long) ; 

void hugetlb_free_pgd_range(struct mmu_gather *tlb,
			    unsigned long addr, unsigned long end,
			    unsigned long floor, unsigned long ceiling)
{
	pgd_t *pgd;
	unsigned long next;
	unsigned long start;

	/*
	 * Comments below take from the normal free_pgd_range().  They
	 * apply here too.  The tests against HUGEPD_MASK below are
	 * essential, because we *don't* test for this at the bottom
	 * level.  Without them we'll attempt to free a hugepte table
	 * when we unmap just part of it, even if there are other
	 * active mappings using it.
	 *
	 * The next few lines have given us lots of grief...
	 *
	 * Why are we testing HUGEPD* at this top level?  Because
	 * often there will be no work to do at all, and we'd prefer
	 * not to go all the way down to the bottom just to discover
	 * that.
	 *
	 * Why all these "- 1"s?  Because 0 represents both the bottom
	 * of the address space and the top of it (using -1 for the
	 * top wouldn't help much: the masks would do the wrong thing).
	 * The rule is that addr 0 and floor 0 refer to the bottom of
	 * the address space, but end 0 and ceiling 0 refer to the top
	 * Comparisons need to use "end - 1" and "ceiling - 1" (though
	 * that end 0 case should be mythical).
	 *
	 * Wherever addr is brought up or ceiling brought down, we
	 * must be careful to reject "the opposite 0" before it
	 * confuses the subsequent tests.  But what about where end is
	 * brought down by HUGEPD_SIZE below? no, end can't go down to
	 * 0 there.
	 *
	 * Whereas we round start (addr) and ceiling down, by different
	 * masks at different levels, in order to test whether a table
	 * now has no other vmas using it, so can be freed, we don't
	 * bother to round floor or end up - the tests don't need that.
	 */
	unsigned int psize = get_slice_psize(tlb->mm, addr);

	addr &= HUGEPD_MASK(psize);
	if (addr < floor) {
		addr += HUGEPD_SIZE(psize);
		if (!addr)
			return;
	}
	if (ceiling) {
		ceiling &= HUGEPD_MASK(psize);
		if (!ceiling)
			return;
	}
	if (end - 1 > ceiling - 1)
		end -= HUGEPD_SIZE(psize);
	if (addr > end - 1)
		return;

	start = addr;
	pgd = pgd_offset(tlb->mm, addr);
	do {
		psize = get_slice_psize(tlb->mm, addr);
		BUG_ON(!mmu_huge_psizes[psize]);
		next = pgd_addr_end(addr, end);
		if (mmu_psize_to_shift(psize) < PUD_SHIFT) {
			if (pgd_none_or_clear_bad(pgd))
				continue;
			hugetlb_free_pud_range(tlb, pgd, addr, next, floor, ceiling);
		} else {
			if (pgd_none(*pgd))
				continue;
			free_hugepte_range(tlb, (hugepd_t *)pgd, psize);
		}
	} while (pgd++, addr = next, addr != end);
}