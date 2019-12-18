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
struct vm_area_struct {int /*<<< orphan*/  anon_vma; struct mm_struct* vm_mm; } ;
struct mm_struct {int /*<<< orphan*/  page_table_lock; } ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 unsigned long HPAGE_PMD_MASK ; 
 unsigned long HPAGE_PMD_SIZE ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  pmd_none (int /*<<< orphan*/ ) ; 
 int pmd_trans_huge (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_trans_splitting (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmdp_get_and_clear (struct mm_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_pmd_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_split_huge_page (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int move_huge_pmd(struct vm_area_struct *vma, unsigned long old_addr,
		  unsigned long new_addr, unsigned long old_end,
		  pmd_t *old_pmd, pmd_t *new_pmd)
{
	int ret = 0;
	pmd_t pmd;

	struct mm_struct *mm = vma->vm_mm;

	if ((old_addr & ~HPAGE_PMD_MASK) ||
	    (new_addr & ~HPAGE_PMD_MASK) ||
	    (old_addr + HPAGE_PMD_SIZE) > old_end)
		goto out;

	/*
	 * The destination pmd shouldn't be established, free_pgtables()
	 * should have release it.
	 */
	if (!pmd_none(*new_pmd)) {
		WARN_ON(1);
		VM_BUG_ON(pmd_trans_huge(*new_pmd));
		goto out;
	}

	spin_lock(&mm->page_table_lock);
	if (likely(pmd_trans_huge(*old_pmd))) {
		if (pmd_trans_splitting(*old_pmd)) {
			spin_unlock(&mm->page_table_lock);
			wait_split_huge_page(vma->anon_vma, old_pmd);
			ret = -1;
		} else {
			pmd = pmdp_get_and_clear(mm, old_addr, old_pmd);
			VM_BUG_ON(!pmd_none(*new_pmd));
			set_pmd_at(mm, new_addr, new_pmd, pmd);
			spin_unlock(&mm->page_table_lock);
			ret = 1;
		}
	} else
		spin_unlock(&mm->page_table_lock);

out:
	return ret;
}