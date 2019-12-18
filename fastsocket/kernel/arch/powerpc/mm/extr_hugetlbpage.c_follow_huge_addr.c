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
struct page {int dummy; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct page* ERR_PTR (int /*<<< orphan*/ ) ; 
 unsigned long PAGE_SIZE ; 
 unsigned int get_slice_psize (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/ * huge_pte_offset (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/ * mmu_huge_psizes ; 
 unsigned int mmu_psize_to_shift (unsigned int) ; 
 struct page* pte_page (int /*<<< orphan*/ ) ; 

struct page *
follow_huge_addr(struct mm_struct *mm, unsigned long address, int write)
{
	pte_t *ptep;
	struct page *page;
	unsigned int mmu_psize = get_slice_psize(mm, address);

	/* Verify it is a huge page else bail. */
	if (!mmu_huge_psizes[mmu_psize])
		return ERR_PTR(-EINVAL);

	ptep = huge_pte_offset(mm, address);
	page = pte_page(*ptep);
	if (page) {
		unsigned int shift = mmu_psize_to_shift(mmu_psize);
		unsigned long sz = ((1UL) << shift);
		page += (address % sz) / PAGE_SIZE;
	}

	return page;
}