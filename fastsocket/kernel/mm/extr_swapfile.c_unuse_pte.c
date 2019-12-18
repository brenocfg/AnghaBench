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
struct vm_area_struct {int /*<<< orphan*/  vm_page_prot; int /*<<< orphan*/  vm_mm; } ;
struct page {int dummy; } ;
struct mem_cgroup {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  activate_page (struct page*) ; 
 int /*<<< orphan*/  anon_rss ; 
 int /*<<< orphan*/  dec_mm_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  inc_mm_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct page* ksm_might_need_to_copy (struct page*,struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/  mem_cgroup_cancel_charge_swapin (struct mem_cgroup*) ; 
 int /*<<< orphan*/  mem_cgroup_commit_charge_swapin (struct page*,struct mem_cgroup*) ; 
 scalar_t__ mem_cgroup_try_charge_swapin (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ,struct mem_cgroup**) ; 
 int /*<<< orphan*/  mk_pte (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_add_anon_rmap (struct page*,struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/  page_add_new_anon_rmap (struct page*,struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/  pte_mkold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_map_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pte_same (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_unmap_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_pte_at (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap_usage ; 
 int /*<<< orphan*/  swp_entry_to_pte (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int unuse_pte(struct vm_area_struct *vma, pmd_t *pmd,
		unsigned long addr, swp_entry_t entry, struct page *page)
{
	struct mem_cgroup *ptr = NULL;
	struct page *swapcache;
	spinlock_t *ptl;
	pte_t *pte;
	int ret = 1;

	swapcache = page;
	page = ksm_might_need_to_copy(page, vma, addr);
	if (unlikely(!page))
		return -ENOMEM;

	if (mem_cgroup_try_charge_swapin(vma->vm_mm, page, GFP_KERNEL, &ptr)) {
		ret = -ENOMEM;
		goto out_nolock;
	}

	pte = pte_offset_map_lock(vma->vm_mm, pmd, addr, &ptl);
	if (unlikely(!pte_same(*pte, swp_entry_to_pte(entry)))) {
		if (ret > 0)
			mem_cgroup_cancel_charge_swapin(ptr);
		ret = 0;
		goto out;
	}

	inc_mm_counter(vma->vm_mm, anon_rss);
	dec_mm_counter(vma->vm_mm, swap_usage);
	get_page(page);
	set_pte_at(vma->vm_mm, addr, pte,
		   pte_mkold(mk_pte(page, vma->vm_page_prot)));

	if (page == swapcache)
		page_add_anon_rmap(page, vma, addr);
	else /* ksm created a completely new copy */
		page_add_new_anon_rmap(page, vma, addr);

	mem_cgroup_commit_charge_swapin(page, ptr);
	swap_free(entry);
	/*
	 * Move the page to the active list so it is not
	 * immediately swapped out again after swapon.
	 */
	activate_page(page);
out:
	pte_unmap_unlock(pte, ptl);
out_nolock:
	if (page != swapcache) {
		unlock_page(page);
		put_page(page);
	}
	return ret;
}