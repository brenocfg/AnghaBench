#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int /*<<< orphan*/  anon_vma; } ;
struct page {int dummy; } ;
struct mmu_gather {TYPE_1__* mm; } ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgtable_t ;
struct TYPE_4__ {int /*<<< orphan*/  page_table_lock; int /*<<< orphan*/  nr_ptes; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPAGE_PMD_NR ; 
 int /*<<< orphan*/  PageHead (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  add_mm_counter (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  anon_rss ; 
 int /*<<< orphan*/  get_pmd_huge_pte (TYPE_1__*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 scalar_t__ page_mapcount (struct page*) ; 
 int /*<<< orphan*/  page_remove_rmap (struct page*) ; 
 int /*<<< orphan*/  pmd_clear (int /*<<< orphan*/ *) ; 
 struct page* pmd_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_trans_huge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_trans_splitting (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tlb_remove_page (struct mmu_gather*,struct page*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_split_huge_page (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int zap_huge_pmd(struct mmu_gather *tlb, struct vm_area_struct *vma,
		 pmd_t *pmd)
{
	int ret = 0;

	spin_lock(&tlb->mm->page_table_lock);
	if (likely(pmd_trans_huge(*pmd))) {
		if (unlikely(pmd_trans_splitting(*pmd))) {
			spin_unlock(&tlb->mm->page_table_lock);
			wait_split_huge_page(vma->anon_vma,
					     pmd);
		} else {
			struct page *page;
			pgtable_t pgtable;
			pgtable = get_pmd_huge_pte(tlb->mm);
			page = pmd_page(*pmd);
			pmd_clear(pmd);
			page_remove_rmap(page);
			VM_BUG_ON(page_mapcount(page) < 0);
			add_mm_counter(tlb->mm, anon_rss, -HPAGE_PMD_NR);
			VM_BUG_ON(!PageHead(page));
			tlb->mm->nr_ptes--;
			spin_unlock(&tlb->mm->page_table_lock);
			tlb_remove_page(tlb, page);
			pte_free(tlb->mm, pgtable);
			ret = 1;
		}
	} else
		spin_unlock(&tlb->mm->page_table_lock);

	return ret;
}