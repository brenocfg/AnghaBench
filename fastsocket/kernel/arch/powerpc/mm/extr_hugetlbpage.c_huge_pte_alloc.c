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
struct mm_struct {int dummy; } ;
struct hstate {unsigned long mask; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;
typedef  int /*<<< orphan*/  hugepd_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ __hugepte_alloc (struct mm_struct*,int /*<<< orphan*/ *,unsigned long,unsigned int) ; 
 unsigned int get_slice_psize (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/ * hpmd_alloc (struct mm_struct*,int /*<<< orphan*/ *,unsigned long,struct hstate*) ; 
 int /*<<< orphan*/ * hpud_alloc (struct mm_struct*,int /*<<< orphan*/ *,unsigned long,struct hstate*) ; 
 scalar_t__ hugepd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hugepte_offset (int /*<<< orphan*/ *,unsigned long,struct hstate*) ; 
 int /*<<< orphan*/ * mmu_huge_psizes ; 
 int /*<<< orphan*/ * pgd_offset (struct mm_struct*,unsigned long) ; 
 struct hstate* size_to_hstate (unsigned long) ; 

pte_t *huge_pte_alloc(struct mm_struct *mm,
			unsigned long addr, unsigned long sz, bool *shared)
{
	pgd_t *pg;
	pud_t *pu;
	pmd_t *pm;
	hugepd_t *hpdp = NULL;
	struct hstate *hstate;
	unsigned int psize;
	hstate = size_to_hstate(sz);

	psize = get_slice_psize(mm, addr);
	BUG_ON(!mmu_huge_psizes[psize]);

	addr &= hstate->mask;

	pg = pgd_offset(mm, addr);
	pu = hpud_alloc(mm, pg, addr, hstate);

	if (pu) {
		pm = hpmd_alloc(mm, pu, addr, hstate);
		if (pm)
			hpdp = (hugepd_t *)pm;
	}

	if (! hpdp)
		return NULL;

	if (hugepd_none(*hpdp) && __hugepte_alloc(mm, hpdp, addr, psize))
		return NULL;

	return hugepte_offset(hpdp, addr, hstate);
}