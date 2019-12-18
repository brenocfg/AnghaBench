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
struct vm_area_struct {struct mm_struct* vm_mm; int /*<<< orphan*/  anon_vma; } ;
struct mm_struct {int /*<<< orphan*/  page_table_lock; } ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_modify (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_trans_huge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_trans_splitting (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmdp_get_and_clear (struct mm_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_pmd_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_split_huge_page (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int change_huge_pmd(struct vm_area_struct *vma, pmd_t *pmd,
		unsigned long addr, pgprot_t newprot)
{
	struct mm_struct *mm = vma->vm_mm;
	int ret = 0;

	spin_lock(&mm->page_table_lock);
	if (likely(pmd_trans_huge(*pmd))) {
		if (unlikely(pmd_trans_splitting(*pmd))) {
			spin_unlock(&mm->page_table_lock);
			wait_split_huge_page(vma->anon_vma, pmd);
		} else {
			pmd_t entry;

			entry = pmdp_get_and_clear(mm, addr, pmd);
			entry = pmd_modify(entry, newprot);
			set_pmd_at(mm, addr, pmd, entry);
			spin_unlock(&vma->vm_mm->page_table_lock);
			ret = 1;
		}
	} else
		spin_unlock(&vma->vm_mm->page_table_lock);

	return ret;
}