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
struct vm_area_struct {int /*<<< orphan*/  vm_page_prot; int /*<<< orphan*/  anon_vma; } ;
struct page {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  page_table_lock; } ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long HPAGE_PMD_MASK ; 
 int /*<<< orphan*/  HPAGE_PMD_NR ; 
 int /*<<< orphan*/  PageCompound (struct page*) ; 
 int /*<<< orphan*/  PageHead (struct page*) ; 
 int /*<<< orphan*/  THP_FAULT_ALLOC ; 
 int /*<<< orphan*/  THP_FAULT_FALLBACK ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int VM_FAULT_OOM ; 
 int VM_FAULT_WRITE ; 
 int /*<<< orphan*/  __SetPageUptodate (struct page*) ; 
 struct page* alloc_hugepage_vma (int /*<<< orphan*/ ,struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_user_huge_page (struct page*,struct page*,unsigned long,struct vm_area_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 int do_huge_pmd_wp_page_fallback (struct mm_struct*,struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct page*,unsigned long) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  maybe_pmd_mkwrite (int /*<<< orphan*/ ,struct vm_area_struct*) ; 
 int mem_cgroup_newpage_charge (struct page*,struct mm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_cgroup_uncharge_page (struct page*) ; 
 int /*<<< orphan*/  mk_pmd (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  numa_node_id () ; 
 int /*<<< orphan*/  page_add_new_anon_rmap (struct page*,struct vm_area_struct*,unsigned long) ; 
 int page_mapcount (struct page*) ; 
 int /*<<< orphan*/  page_remove_rmap (struct page*) ; 
 int /*<<< orphan*/  pmd_mkdirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_mkhuge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_mkyoung (int /*<<< orphan*/ ) ; 
 struct page* pmd_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_same (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmdp_clear_flush_notify (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 scalar_t__ pmdp_set_access_flags (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_pmd_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  split_huge_page (struct page*) ; 
 int /*<<< orphan*/  transparent_hugepage_debug_cow () ; 
 int /*<<< orphan*/  transparent_hugepage_defrag (struct vm_area_struct*) ; 
 scalar_t__ transparent_hugepage_enabled (struct vm_area_struct*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  update_mmu_cache (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 

int do_huge_pmd_wp_page(struct mm_struct *mm, struct vm_area_struct *vma,
			unsigned long address, pmd_t *pmd, pmd_t orig_pmd)
{
	int ret = 0;
	struct page *page, *new_page;
	unsigned long haddr;

	VM_BUG_ON(!vma->anon_vma);
	spin_lock(&mm->page_table_lock);
	if (unlikely(!pmd_same(*pmd, orig_pmd)))
		goto out_unlock;

	page = pmd_page(orig_pmd);
	VM_BUG_ON(!PageCompound(page) || !PageHead(page));
	haddr = address & HPAGE_PMD_MASK;
	if (page_mapcount(page) == 1) {
		pmd_t entry;
		entry = pmd_mkyoung(orig_pmd);
		entry = maybe_pmd_mkwrite(pmd_mkdirty(entry), vma);
		if (pmdp_set_access_flags(vma, haddr, pmd, entry,  1))
			update_mmu_cache(vma, address, entry);
		ret |= VM_FAULT_WRITE;
		goto out_unlock;
	}
	get_page(page);
	spin_unlock(&mm->page_table_lock);

	if (transparent_hugepage_enabled(vma) &&
	    !transparent_hugepage_debug_cow())
		new_page = alloc_hugepage_vma(transparent_hugepage_defrag(vma),
					      vma, haddr, numa_node_id(), 0);
	else
		new_page = NULL;

	if (unlikely(!new_page)) {
		count_vm_event(THP_FAULT_FALLBACK);
		ret = do_huge_pmd_wp_page_fallback(mm, vma, address,
						   pmd, orig_pmd, page, haddr);
		if (ret & VM_FAULT_OOM)
			split_huge_page(page);
		put_page(page);
		goto out;
	}
	count_vm_event(THP_FAULT_ALLOC);

	if (unlikely(mem_cgroup_newpage_charge(new_page, mm, GFP_KERNEL))) {
		put_page(new_page);
		split_huge_page(page);
		put_page(page);
		ret |= VM_FAULT_OOM;
		goto out;
	}

	copy_user_huge_page(new_page, page, haddr, vma, HPAGE_PMD_NR);
	__SetPageUptodate(new_page);

	spin_lock(&mm->page_table_lock);
	put_page(page);
	if (unlikely(!pmd_same(*pmd, orig_pmd))) {
		mem_cgroup_uncharge_page(new_page);
		put_page(new_page);
	} else {
		pmd_t entry;
		VM_BUG_ON(!PageHead(page));
		entry = mk_pmd(new_page, vma->vm_page_prot);
		entry = maybe_pmd_mkwrite(pmd_mkdirty(entry), vma);
		entry = pmd_mkhuge(entry);
		pmdp_clear_flush_notify(vma, haddr, pmd);
		page_add_new_anon_rmap(new_page, vma, haddr);
		set_pmd_at(mm, haddr, pmd, entry);
		update_mmu_cache(vma, address, entry);
		page_remove_rmap(page);
		put_page(page);
		ret |= VM_FAULT_WRITE;
	}
out_unlock:
	spin_unlock(&mm->page_table_lock);
out:
	return ret;
}