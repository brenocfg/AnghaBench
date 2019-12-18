#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  swp_entry_t ;
struct vm_area_struct {int vm_flags; TYPE_1__* vm_ops; int /*<<< orphan*/  anon_vma; struct mm_struct* vm_mm; } ;
struct page {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  page_table_lock; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;
struct TYPE_2__ {int /*<<< orphan*/  fault; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (unsigned int) ; 
 int /*<<< orphan*/  EFAULT ; 
 struct page* ERR_PTR (int /*<<< orphan*/ ) ; 
 unsigned int FOLL_DUMP ; 
 unsigned int FOLL_GET ; 
 unsigned int FOLL_MIGRATION ; 
 unsigned int FOLL_SPLIT ; 
 unsigned int FOLL_TOUCH ; 
 unsigned int FOLL_WRITE ; 
 int /*<<< orphan*/  IS_ERR (struct page*) ; 
 int /*<<< orphan*/  PageDirty (struct page*) ; 
 int VM_HUGETLB ; 
 struct page* follow_huge_addr (struct mm_struct*,unsigned long,unsigned int) ; 
 struct page* follow_huge_pmd (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,unsigned int) ; 
 struct page* follow_huge_pud (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,unsigned int) ; 
 struct page* follow_trans_huge_pmd (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  get_page_foll (struct page*) ; 
 int /*<<< orphan*/  is_migration_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_zero_pfn (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mark_page_accessed (struct page*) ; 
 int /*<<< orphan*/  migration_entry_wait (struct mm_struct*,int /*<<< orphan*/ *,unsigned long) ; 
 int pgd_bad (int /*<<< orphan*/ ) ; 
 scalar_t__ pgd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pgd_offset (struct mm_struct*,unsigned long) ; 
 int pmd_bad (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_huge (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int pmd_trans_huge (int /*<<< orphan*/ ) ; 
 int pmd_trans_splitting (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_dirty (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_file (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_map_lock (struct mm_struct*,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ **) ; 
 struct page* pte_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_to_swp_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_unmap_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_write (int /*<<< orphan*/ ) ; 
 int pud_bad (int /*<<< orphan*/ ) ; 
 scalar_t__ pud_huge (int /*<<< orphan*/ ) ; 
 scalar_t__ pud_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  split_huge_page_pmd (struct mm_struct*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 struct page* vm_normal_page (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_split_huge_page (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct page *follow_page(struct vm_area_struct *vma, unsigned long address,
			unsigned int flags)
{
	pgd_t *pgd;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *ptep, pte;
	spinlock_t *ptl;
	struct page *page;
	struct mm_struct *mm = vma->vm_mm;

	page = follow_huge_addr(mm, address, flags & FOLL_WRITE);
	if (!IS_ERR(page)) {
		BUG_ON(flags & FOLL_GET);
		goto out;
	}

	page = NULL;
	pgd = pgd_offset(mm, address);
	if (pgd_none(*pgd) || unlikely(pgd_bad(*pgd)))
		goto no_page_table;

	pud = pud_offset(pgd, address);
	if (pud_none(*pud))
		goto no_page_table;
	if (pud_huge(*pud)) {
		BUG_ON(flags & FOLL_GET);
		page = follow_huge_pud(mm, address, pud, flags & FOLL_WRITE);
		goto out;
	}
	if (unlikely(pud_bad(*pud)))
		goto no_page_table;

	pmd = pmd_offset(pud, address);
	if (pmd_none(*pmd))
		goto no_page_table;
	if (pmd_huge(*pmd) && vma->vm_flags & VM_HUGETLB) {
		BUG_ON(flags & FOLL_GET);
		page = follow_huge_pmd(mm, address, pmd, flags & FOLL_WRITE);
		goto out;
	}
	if (pmd_trans_huge(*pmd)) {
		if (flags & FOLL_SPLIT) {
			split_huge_page_pmd(mm, pmd);
			goto split_fallthrough;
		}
		spin_lock(&mm->page_table_lock);
		if (likely(pmd_trans_huge(*pmd))) {
			if (unlikely(pmd_trans_splitting(*pmd))) {
				spin_unlock(&mm->page_table_lock);
				wait_split_huge_page(vma->anon_vma, pmd);
			} else {
				page = follow_trans_huge_pmd(mm, address,
							     pmd, flags);
				spin_unlock(&mm->page_table_lock);
				goto out;
			}
		} else
			spin_unlock(&mm->page_table_lock);
		/* fall through */
	}
split_fallthrough:
	if (unlikely(pmd_bad(*pmd)))
		goto no_page_table;

	ptep = pte_offset_map_lock(mm, pmd, address, &ptl);

	pte = *ptep;
	if (!pte_present(pte)) {
		swp_entry_t entry;
		/*
		 * KSM's break_ksm() relies upon recognizing a ksm page
		 * even while it is being migrated, so for that case we
		 * need migration_entry_wait().
		 */
		if (likely(!(flags & FOLL_MIGRATION)))
			goto no_page;
		if (pte_none(pte) || pte_file(pte))
			goto no_page;
		entry = pte_to_swp_entry(pte);
		if (!is_migration_entry(entry))
			goto no_page;
		pte_unmap_unlock(ptep, ptl);
		migration_entry_wait(mm, pmd, address);
		goto split_fallthrough;
	}
	if ((flags & FOLL_WRITE) && !pte_write(pte))
		goto unlock;

	page = vm_normal_page(vma, address, pte);
	if (unlikely(!page)) {
		if ((flags & FOLL_DUMP) ||
		    !is_zero_pfn(pte_pfn(pte)))
			goto bad_page;
		page = pte_page(pte);
	}

	if (flags & FOLL_GET)
		get_page_foll(page);
	if (flags & FOLL_TOUCH) {
		if ((flags & FOLL_WRITE) &&
		    !pte_dirty(pte) && !PageDirty(page))
			set_page_dirty(page);
		/*
		 * pte_mkyoung() would be more correct here, but atomic care
		 * is needed to avoid losing the dirty bit: it is easier to use
		 * mark_page_accessed().
		 */
		mark_page_accessed(page);
	}
unlock:
	pte_unmap_unlock(ptep, ptl);
out:
	return page;

bad_page:
	pte_unmap_unlock(ptep, ptl);
	return ERR_PTR(-EFAULT);

no_page:
	pte_unmap_unlock(ptep, ptl);
	if (!pte_none(pte))
		return page;

no_page_table:
	/*
	 * When core dumping an enormous anonymous area that nobody
	 * has touched so far, we don't want to allocate unnecessary pages or
	 * page tables.  Return error instead of NULL to skip handle_mm_fault,
	 * then get_dump_page() will return NULL to leave a hole in the dump.
	 * But we can only make this optimization where a hole would surely
	 * be zero-filled if handle_mm_fault() actually did handle it.
	 */
	if ((flags & FOLL_DUMP) &&
	    (!vma->vm_ops || !vma->vm_ops->fault))
		return ERR_PTR(-EFAULT);
	return page;
}