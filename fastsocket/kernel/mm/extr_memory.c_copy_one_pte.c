#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned long val; } ;
typedef  TYPE_1__ swp_entry_t ;
struct vm_area_struct {unsigned long vm_flags; } ;
struct page {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  mmlist; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 size_t PageAnon (struct page*) ; 
 unsigned long VM_SHARED ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 scalar_t__ is_cow_mapping (unsigned long) ; 
 int /*<<< orphan*/  is_migration_entry (TYPE_1__) ; 
 scalar_t__ is_write_migration_entry (TYPE_1__) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_migration_entry_read (TYPE_1__*) ; 
 int /*<<< orphan*/  mmlist_lock ; 
 int /*<<< orphan*/  page_dup_rmap (struct page*) ; 
 int /*<<< orphan*/  pte_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkclean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_present (int /*<<< orphan*/ ) ; 
 TYPE_1__ pte_to_swp_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_wrprotect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptep_set_wrprotect (struct mm_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_pte_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ swap_duplicate (TYPE_1__) ; 
 int /*<<< orphan*/  swp_entry_to_pte (TYPE_1__) ; 
 scalar_t__ unlikely (int) ; 
 struct page* vm_normal_page (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned long
copy_one_pte(struct mm_struct *dst_mm, struct mm_struct *src_mm,
		pte_t *dst_pte, pte_t *src_pte, struct vm_area_struct *vma,
		unsigned long addr, int *rss)
{
	unsigned long vm_flags = vma->vm_flags;
	pte_t pte = *src_pte;
	struct page *page;

	/* pte contains position in swap or file, so copy. */
	if (unlikely(!pte_present(pte))) {
		if (!pte_file(pte)) {
			swp_entry_t entry = pte_to_swp_entry(pte);

			if (swap_duplicate(entry) < 0)
				return entry.val;

			/* make sure dst_mm is on swapoff's mmlist. */
			if (unlikely(list_empty(&dst_mm->mmlist))) {
				spin_lock(&mmlist_lock);
				if (list_empty(&dst_mm->mmlist))
					list_add(&dst_mm->mmlist,
						 &src_mm->mmlist);
				spin_unlock(&mmlist_lock);
			}
			if (!is_migration_entry(entry))
				rss[2]++;
			else if (is_write_migration_entry(entry) &&
					is_cow_mapping(vm_flags)) {
				/*
				 * COW mappings require pages in both parent
				 * and child to be set to read.
				 */
				make_migration_entry_read(&entry);
				pte = swp_entry_to_pte(entry);
				set_pte_at(src_mm, addr, src_pte, pte);
			}
		}
		goto out_set_pte;
	}

	/*
	 * If it's a COW mapping, write protect it both
	 * in the parent and the child
	 */
	if (is_cow_mapping(vm_flags)) {
		ptep_set_wrprotect(src_mm, addr, src_pte);
		pte = pte_wrprotect(pte);
	}

	/*
	 * If it's a shared mapping, mark it clean in
	 * the child
	 */
	if (vm_flags & VM_SHARED)
		pte = pte_mkclean(pte);
	pte = pte_mkold(pte);

	page = vm_normal_page(vma, addr, pte);
	if (page) {
		get_page(page);
		page_dup_rmap(page);
		rss[PageAnon(page)]++;
	}

out_set_pte:
	set_pte_at(dst_mm, addr, dst_pte, pte);
	return 0;
}