#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int /*<<< orphan*/  vm_page_prot; } ;
struct page {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  page_table_lock; } ;
typedef  int /*<<< orphan*/  pte_t ;
struct TYPE_9__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ pmd_t ;
typedef  int /*<<< orphan*/  pgtable_t ;

/* Variables and functions */
 int GFP_HIGHUSER_MOVABLE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HPAGE_PMD_NR ; 
 int PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PageHead (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int VM_FAULT_OOM ; 
 int VM_FAULT_WRITE ; 
 int __GFP_OTHER_NODE ; 
 int /*<<< orphan*/  __SetPageUptodate (struct page*) ; 
 struct page* alloc_page_vma_node (int,struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  copy_user_highpage (struct page*,struct page*,unsigned long,struct vm_area_struct*) ; 
 int /*<<< orphan*/  get_pmd_huge_pte (struct mm_struct*) ; 
 int /*<<< orphan*/  kfree (struct page**) ; 
 struct page** kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maybe_mkwrite (int /*<<< orphan*/ ,struct vm_area_struct*) ; 
 scalar_t__ mem_cgroup_newpage_charge (struct page*,struct mm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_cgroup_uncharge_page (struct page*) ; 
 int /*<<< orphan*/  mk_pte (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_add_new_anon_rmap (struct page*,struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/  page_remove_rmap (struct page*) ; 
 int /*<<< orphan*/  page_to_nid (struct page*) ; 
 int /*<<< orphan*/  pmd_populate (struct mm_struct*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_same (TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  pmdp_clear_flush_notify (struct vm_area_struct*,unsigned long,TYPE_1__*) ; 
 int /*<<< orphan*/  pte_mkdirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_map (TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  pte_unmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_pte_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int do_huge_pmd_wp_page_fallback(struct mm_struct *mm,
					struct vm_area_struct *vma,
					unsigned long address,
					pmd_t *pmd, pmd_t orig_pmd,
					struct page *page,
					unsigned long haddr)
{
	pgtable_t pgtable;
	pmd_t _pmd = {0};
	int ret = 0, i;
	struct page **pages;

	pages = kmalloc(sizeof(struct page *) * HPAGE_PMD_NR,
			GFP_KERNEL);
	if (unlikely(!pages)) {
		ret |= VM_FAULT_OOM;
		goto out;
	}

	for (i = 0; i < HPAGE_PMD_NR; i++) {
		pages[i] = alloc_page_vma_node(GFP_HIGHUSER_MOVABLE |
					       __GFP_OTHER_NODE,
					       vma, address, page_to_nid(page));
		if (unlikely(!pages[i] ||
			     mem_cgroup_newpage_charge(pages[i], mm,
						       GFP_KERNEL))) {
			if (pages[i])
				put_page(pages[i]);
			while (--i >= 0) {
				mem_cgroup_uncharge_page(pages[i]);
				put_page(pages[i]);
			}
			kfree(pages);
			ret |= VM_FAULT_OOM;
			goto out;
		}
	}

	for (i = 0; i < HPAGE_PMD_NR; i++) {
		copy_user_highpage(pages[i], page + i,
				   haddr + PAGE_SHIFT*i, vma);
		__SetPageUptodate(pages[i]);
		cond_resched();
	}

	spin_lock(&mm->page_table_lock);
	if (unlikely(!pmd_same(*pmd, orig_pmd)))
		goto out_free_pages;
	VM_BUG_ON(!PageHead(page));

	pmdp_clear_flush_notify(vma, haddr, pmd);
	/* leave pmd empty until pte is filled */

	pgtable = get_pmd_huge_pte(mm);
	pmd_populate(mm, &_pmd, pgtable);

	for (i = 0; i < HPAGE_PMD_NR; i++, haddr += PAGE_SIZE) {
		pte_t *pte, entry;
		entry = mk_pte(pages[i], vma->vm_page_prot);
		entry = maybe_mkwrite(pte_mkdirty(entry), vma);
		page_add_new_anon_rmap(pages[i], vma, haddr);
		pte = pte_offset_map(&_pmd, haddr);
		VM_BUG_ON(!pte_none(*pte));
		set_pte_at(mm, haddr, pte, entry);
		pte_unmap(pte);
	}
	kfree(pages);

	smp_wmb(); /* make pte visible before pmd */
	pmd_populate(mm, pmd, pgtable);
	page_remove_rmap(page);
	spin_unlock(&mm->page_table_lock);

	ret |= VM_FAULT_WRITE;
	put_page(page);

out:
	return ret;

out_free_pages:
	spin_unlock(&mm->page_table_lock);
	for (i = 0; i < HPAGE_PMD_NR; i++) {
		mem_cgroup_uncharge_page(pages[i]);
		put_page(pages[i]);
	}
	kfree(pages);
	goto out;
}