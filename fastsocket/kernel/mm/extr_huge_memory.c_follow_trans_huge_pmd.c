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
struct mm_struct {int /*<<< orphan*/  page_table_lock; } ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 unsigned int FOLL_GET ; 
 unsigned int FOLL_TOUCH ; 
 unsigned int FOLL_WRITE ; 
 unsigned long HPAGE_PMD_MASK ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  PageCompound (struct page*) ; 
 int /*<<< orphan*/  PageHead (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  get_page_foll (struct page*) ; 
 int /*<<< orphan*/  pmd_mkdirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_mkyoung (int /*<<< orphan*/ ) ; 
 struct page* pmd_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pmd_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int spin_can_lock (int /*<<< orphan*/ *) ; 

struct page *follow_trans_huge_pmd(struct mm_struct *mm,
				   unsigned long addr,
				   pmd_t *pmd,
				   unsigned int flags)
{
	struct page *page = NULL;

	VM_BUG_ON(spin_can_lock(&mm->page_table_lock));

	if (flags & FOLL_WRITE && !pmd_write(*pmd))
		goto out;

	page = pmd_page(*pmd);
	VM_BUG_ON(!PageHead(page));
	if (flags & FOLL_TOUCH) {
		pmd_t _pmd;
		/*
		 * We should set the dirty bit only for FOLL_WRITE but
		 * for now the dirty bit in the pmd is meaningless.
		 * And if the dirty bit will become meaningful and
		 * we'll only set it with FOLL_WRITE, an atomic
		 * set_bit will be required on the pmd to set the
		 * young bit, instead of the current set_pmd_at.
		 */
		_pmd = pmd_mkyoung(pmd_mkdirty(*pmd));
		set_pmd_at(mm, addr & HPAGE_PMD_MASK, pmd, _pmd);
	}
	page += (addr & ~HPAGE_PMD_MASK) >> PAGE_SHIFT;
	VM_BUG_ON(!PageCompound(page));
	if (flags & FOLL_GET)
		get_page_foll(page);

out:
	return page;
}