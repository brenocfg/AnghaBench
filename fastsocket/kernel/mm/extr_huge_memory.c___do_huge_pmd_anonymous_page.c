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
struct vm_area_struct {int /*<<< orphan*/  vm_page_prot; } ;
struct page {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  page_table_lock; int /*<<< orphan*/  nr_ptes; } ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgtable_t ;

/* Variables and functions */
 int /*<<< orphan*/  HPAGE_PMD_NR ; 
 int /*<<< orphan*/  PageCompound (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int VM_FAULT_OOM ; 
 int /*<<< orphan*/  __SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  add_mm_counter (struct mm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  anon_rss ; 
 int /*<<< orphan*/  clear_huge_page (struct page*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maybe_pmd_mkwrite (int /*<<< orphan*/ ,struct vm_area_struct*) ; 
 int /*<<< orphan*/  mem_cgroup_uncharge_page (struct page*) ; 
 int /*<<< orphan*/  mk_pmd (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_add_new_anon_rmap (struct page*,struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/  pmd_mkdirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_mkhuge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_pmd_huge_pte (int /*<<< orphan*/ ,struct mm_struct*) ; 
 int /*<<< orphan*/  pte_alloc_one (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  pte_free (struct mm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_pmd_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int __do_huge_pmd_anonymous_page(struct mm_struct *mm,
					struct vm_area_struct *vma,
					unsigned long haddr, pmd_t *pmd,
					struct page *page)
{
	int ret = 0;
	pgtable_t pgtable;

	VM_BUG_ON(!PageCompound(page));
	pgtable = pte_alloc_one(mm, haddr);
	if (unlikely(!pgtable)) {
		mem_cgroup_uncharge_page(page);
		put_page(page);
		return VM_FAULT_OOM;
	}

	clear_huge_page(page, haddr, HPAGE_PMD_NR);
	__SetPageUptodate(page);

	spin_lock(&mm->page_table_lock);
	if (unlikely(!pmd_none(*pmd))) {
		spin_unlock(&mm->page_table_lock);
		mem_cgroup_uncharge_page(page);
		put_page(page);
		pte_free(mm, pgtable);
	} else {
		pmd_t entry;
		entry = mk_pmd(page, vma->vm_page_prot);
		entry = maybe_pmd_mkwrite(pmd_mkdirty(entry), vma);
		entry = pmd_mkhuge(entry);
		/*
		 * The spinlocking to take the lru_lock inside
		 * page_add_new_anon_rmap() acts as a full memory
		 * barrier to be sure clear_huge_page writes become
		 * visible after the set_pmd_at() write.
		 */
		page_add_new_anon_rmap(page, vma, haddr);
		set_pmd_at(mm, haddr, pmd, entry);
		prepare_pmd_huge_pte(pgtable, mm);
		add_mm_counter(mm, anon_rss, HPAGE_PMD_NR);
		mm->nr_ptes++;
		spin_unlock(&mm->page_table_lock);
	}

	return ret;
}