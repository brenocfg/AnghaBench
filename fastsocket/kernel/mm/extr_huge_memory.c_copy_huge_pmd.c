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
struct vm_area_struct {int /*<<< orphan*/  anon_vma; } ;
struct page {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  page_table_lock; int /*<<< orphan*/  nr_ptes; } ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgtable_t ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HPAGE_PMD_NR ; 
 int /*<<< orphan*/  PageHead (struct page*) ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  add_mm_counter (struct mm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  anon_rss ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  page_dup_rmap (struct page*) ; 
 int /*<<< orphan*/  pmd_mkold (int /*<<< orphan*/ ) ; 
 struct page* pmd_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_trans_huge (int /*<<< orphan*/ ) ; 
 int pmd_trans_splitting (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_wrprotect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmdp_set_wrprotect (struct mm_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_pmd_huge_pte (int /*<<< orphan*/ ,struct mm_struct*) ; 
 int /*<<< orphan*/  pte_alloc_one (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  pte_free (struct mm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pmd_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait_split_huge_page (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int copy_huge_pmd(struct mm_struct *dst_mm, struct mm_struct *src_mm,
		  pmd_t *dst_pmd, pmd_t *src_pmd, unsigned long addr,
		  struct vm_area_struct *vma)
{
	struct page *src_page;
	pmd_t pmd;
	pgtable_t pgtable;
	int ret;

	ret = -ENOMEM;
	pgtable = pte_alloc_one(dst_mm, addr);
	if (unlikely(!pgtable))
		goto out;

	spin_lock(&dst_mm->page_table_lock);
	spin_lock_nested(&src_mm->page_table_lock, SINGLE_DEPTH_NESTING);

	ret = -EAGAIN;
	pmd = *src_pmd;
	if (unlikely(!pmd_trans_huge(pmd))) {
		pte_free(dst_mm, pgtable);
		goto out_unlock;
	}
	if (unlikely(pmd_trans_splitting(pmd))) {
		/* split huge page running from under us */
		spin_unlock(&src_mm->page_table_lock);
		spin_unlock(&dst_mm->page_table_lock);
		pte_free(dst_mm, pgtable);

		wait_split_huge_page(vma->anon_vma, src_pmd); /* src_vma */
		goto out;
	}
	src_page = pmd_page(pmd);
	VM_BUG_ON(!PageHead(src_page));
	get_page(src_page);
	page_dup_rmap(src_page);
	add_mm_counter(dst_mm, anon_rss, HPAGE_PMD_NR);

	pmdp_set_wrprotect(src_mm, addr, src_pmd);
	pmd = pmd_mkold(pmd_wrprotect(pmd));
	set_pmd_at(dst_mm, addr, dst_pmd, pmd);
	prepare_pmd_huge_pte(pgtable, dst_mm);
	dst_mm->nr_ptes++;

	ret = 0;
out_unlock:
	spin_unlock(&src_mm->page_table_lock);
	spin_unlock(&dst_mm->page_table_lock);
out:
	return ret;
}