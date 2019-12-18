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
typedef  int /*<<< orphan*/  swp_entry_t ;
struct vm_area_struct {int /*<<< orphan*/  vm_page_prot; struct mm_struct* vm_mm; } ;
struct page {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  page_table_lock; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 scalar_t__ PageAnon (struct page*) ; 
 scalar_t__ PageHuge (struct page*) ; 
 int SWAP_AGAIN ; 
 int /*<<< orphan*/  flush_cache_page (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/ * huge_pte_offset (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  hugepage_add_anon_rmap (struct page*,struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/  is_migration_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_swap_pte (int /*<<< orphan*/ ) ; 
 scalar_t__ is_write_migration_entry (int /*<<< orphan*/ ) ; 
 void* migration_entry_to_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mk_pte (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_add_anon_rmap (struct page*,struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/  page_add_file_rmap (struct page*) ; 
 int /*<<< orphan*/  page_dup_rmap (struct page*) ; 
 int /*<<< orphan*/ * pgd_offset (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  pgd_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pmd_present (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_trans_huge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_lockptr (struct mm_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_mkhuge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_map (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pte_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_to_swp_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_unmap_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pud_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pte_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (scalar_t__) ; 
 int /*<<< orphan*/  update_mmu_cache (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int remove_migration_pte(struct page *new, struct vm_area_struct *vma,
				 unsigned long addr, void *old)
{
	struct mm_struct *mm = vma->vm_mm;
	swp_entry_t entry;
 	pgd_t *pgd;
 	pud_t *pud;
 	pmd_t *pmd;
	pte_t *ptep, pte;
 	spinlock_t *ptl;

	if (unlikely(PageHuge(new))) {
		ptep = huge_pte_offset(mm, addr);
		if (!ptep)
			goto out;
		ptl = &mm->page_table_lock;
	} else {
		pgd = pgd_offset(mm, addr);
		if (!pgd_present(*pgd))
			goto out;

		pud = pud_offset(pgd, addr);
		if (!pud_present(*pud))
			goto out;

		pmd = pmd_offset(pud, addr);
		if (pmd_trans_huge(*pmd))
			goto out;
		if (!pmd_present(*pmd))
			goto out;

		ptep = pte_offset_map(pmd, addr);

		/*
		 * Peek to check is_swap_pte() before taking ptlock?  No, we
		 * can race mremap's move_ptes(), which skips anon_vma lock.
		 */

		ptl = pte_lockptr(mm, pmd);
	}

 	spin_lock(ptl);
	pte = *ptep;
	if (!is_swap_pte(pte))
		goto unlock;

	entry = pte_to_swp_entry(pte);

	if (!is_migration_entry(entry) ||
	    migration_entry_to_page(entry) != old)
		goto unlock;

	get_page(new);
	pte = pte_mkold(mk_pte(new, vma->vm_page_prot));
	if (is_write_migration_entry(entry))
		pte = pte_mkwrite(pte);
#ifdef CONFIG_HUGETLB_PAGE
	if (PageHuge(new))
		pte = pte_mkhuge(pte);
#endif
	flush_cache_page(vma, addr, pte_pfn(pte));
	set_pte_at(mm, addr, ptep, pte);

	if (PageHuge(new)) {
		if (PageAnon(new))
			hugepage_add_anon_rmap(new, vma, addr);
		else
			page_dup_rmap(new);
	} else if (PageAnon(new))
		page_add_anon_rmap(new, vma, addr);
	else
		page_add_file_rmap(new);

	/* No need to invalidate - it was non-present before */
	update_mmu_cache(vma, addr, pte);
unlock:
	pte_unmap_unlock(ptep, ptl);
out:
	return SWAP_AGAIN;
}