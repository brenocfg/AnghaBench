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
 unsigned int get_slice_psize (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/ * hpmd_offset (int /*<<< orphan*/ *,unsigned long,struct hstate*) ; 
 int /*<<< orphan*/ * hpud_offset (int /*<<< orphan*/ *,unsigned long,struct hstate*) ; 
 int /*<<< orphan*/ * hugepte_offset (int /*<<< orphan*/ *,unsigned long,struct hstate*) ; 
 unsigned int mmu_psize_to_shift (unsigned int) ; 
 int /*<<< orphan*/  pgd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pgd_offset (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pud_none (int /*<<< orphan*/ ) ; 
 struct hstate* size_to_hstate (unsigned long) ; 

pte_t *huge_pte_offset(struct mm_struct *mm, unsigned long addr)
{
	pgd_t *pg;
	pud_t *pu;
	pmd_t *pm;

	unsigned int psize;
	unsigned int shift;
	unsigned long sz;
	struct hstate *hstate;
	psize = get_slice_psize(mm, addr);
	shift = mmu_psize_to_shift(psize);
	sz = ((1UL) << shift);
	hstate = size_to_hstate(sz);

	addr &= hstate->mask;

	pg = pgd_offset(mm, addr);
	if (!pgd_none(*pg)) {
		pu = hpud_offset(pg, addr, hstate);
		if (!pud_none(*pu)) {
			pm = hpmd_offset(pu, addr, hstate);
			if (!pmd_none(*pm))
				return hugepte_offset((hugepd_t *)pm, addr,
						      hstate);
		}
	}

	return NULL;
}