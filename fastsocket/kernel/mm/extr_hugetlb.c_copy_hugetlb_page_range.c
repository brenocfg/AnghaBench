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
struct vm_area_struct {int vm_flags; unsigned long vm_start; unsigned long vm_end; } ;
struct page {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  page_table_lock; } ;
struct hstate {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int VM_MAYWRITE ; 
 int VM_SHARED ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 struct hstate* hstate_vma (struct vm_area_struct*) ; 
 unsigned long huge_page_size (struct hstate*) ; 
 int /*<<< orphan*/ * huge_pte_alloc (struct mm_struct*,unsigned long,unsigned long,int*) ; 
 int /*<<< orphan*/  huge_pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * huge_pte_offset (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  huge_ptep_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  huge_ptep_set_wrprotect (struct mm_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  page_dup_rmap (struct page*) ; 
 struct page* pte_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_huge_pte_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int copy_hugetlb_page_range(struct mm_struct *dst, struct mm_struct *src,
			    struct vm_area_struct *vma)
{
	pte_t *src_pte, *dst_pte, entry;
	struct page *ptepage;
	unsigned long addr;
	int cow;
	struct hstate *h = hstate_vma(vma);
	unsigned long sz = huge_page_size(h);
	bool shared = false;

	cow = (vma->vm_flags & (VM_SHARED | VM_MAYWRITE)) == VM_MAYWRITE;

	for (addr = vma->vm_start; addr < vma->vm_end; addr += sz) {
		src_pte = huge_pte_offset(src, addr);
		if (!src_pte)
			continue;
		dst_pte = huge_pte_alloc(dst, addr, sz, &shared);
		if (!dst_pte)
			goto nomem;

		/* If the pagetables are shared don't copy or take references */
		if (shared)
			continue;

		spin_lock(&dst->page_table_lock);
		spin_lock_nested(&src->page_table_lock, SINGLE_DEPTH_NESTING);
		if (!huge_pte_none(huge_ptep_get(src_pte))) {
			if (cow)
				huge_ptep_set_wrprotect(src, addr, src_pte);
			entry = huge_ptep_get(src_pte);
			ptepage = pte_page(entry);
			get_page(ptepage);
			page_dup_rmap(ptepage);
			set_huge_pte_at(dst, addr, dst_pte, entry);
		}
		spin_unlock(&src->page_table_lock);
		spin_unlock(&dst->page_table_lock);
	}
	return 0;

nomem:
	return -ENOMEM;
}