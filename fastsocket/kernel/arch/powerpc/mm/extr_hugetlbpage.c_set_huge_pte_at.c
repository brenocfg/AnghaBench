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
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int _PAGE_HPTEFLAGS ; 
 int /*<<< orphan*/  __pte (int) ; 
 unsigned int get_slice_psize (struct mm_struct*,unsigned long) ; 
 unsigned int mmu_psize_to_shift (unsigned int) ; 
 scalar_t__ pte_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_update (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,unsigned long,int) ; 
 int pte_val (int /*<<< orphan*/ ) ; 
 struct hstate* size_to_hstate (unsigned long) ; 

void set_huge_pte_at(struct mm_struct *mm, unsigned long addr,
		     pte_t *ptep, pte_t pte)
{
	if (pte_present(*ptep)) {
		/* We open-code pte_clear because we need to pass the right
		 * argument to hpte_need_flush (huge / !huge). Might not be
		 * necessary anymore if we make hpte_need_flush() get the
		 * page size from the slices
		 */
		unsigned int psize = get_slice_psize(mm, addr);
		unsigned int shift = mmu_psize_to_shift(psize);
		unsigned long sz = ((1UL) << shift);
		struct hstate *hstate = size_to_hstate(sz);
		pte_update(mm, addr & hstate->mask, ptep, ~0UL, 1);
	}
	*ptep = __pte(pte_val(pte) & ~_PAGE_HPTEFLAGS);
}