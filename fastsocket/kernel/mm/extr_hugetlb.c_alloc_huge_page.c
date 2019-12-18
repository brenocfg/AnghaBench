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
struct vm_area_struct {int dummy; } ;
struct page {int dummy; } ;
struct hugepage_subpool {int dummy; } ;
struct hstate {int dummy; } ;

/* Variables and functions */
 struct page* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 int /*<<< orphan*/  VM_FAULT_OOM ; 
 int /*<<< orphan*/  VM_FAULT_SIGBUS ; 
 struct page* alloc_buddy_huge_page (struct hstate*,int /*<<< orphan*/ ) ; 
 struct page* dequeue_huge_page_vma (struct hstate*,struct vm_area_struct*,unsigned long,int) ; 
 struct hstate* hstate_vma (struct vm_area_struct*) ; 
 scalar_t__ hugepage_subpool_get_pages (struct hugepage_subpool*,long) ; 
 int /*<<< orphan*/  hugepage_subpool_put_pages (struct hugepage_subpool*,long) ; 
 int /*<<< orphan*/  hugetlb_lock ; 
 int /*<<< orphan*/  set_page_private (struct page*,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct hugepage_subpool* subpool_vma (struct vm_area_struct*) ; 
 int /*<<< orphan*/  vma_commit_reservation (struct hstate*,struct vm_area_struct*,unsigned long) ; 
 long vma_needs_reservation (struct hstate*,struct vm_area_struct*,unsigned long) ; 

__attribute__((used)) static struct page *alloc_huge_page(struct vm_area_struct *vma,
				    unsigned long addr, int avoid_reserve)
{
	struct hugepage_subpool *spool = subpool_vma(vma);
	struct hstate *h = hstate_vma(vma);
	struct page *page;
	long chg;

	/*
	 * Processes that did not create the mapping will have no
	 * reserves and will not have accounted against subpool
	 * limit. Check that the subpool limit can be made before
	 * satisfying the allocation MAP_NORESERVE mappings may also
	 * need pages and subpool limit allocated allocated if no reserve
	 * mapping overlaps.
	 */
	chg = vma_needs_reservation(h, vma, addr);
	if (chg < 0)
		return ERR_PTR(-VM_FAULT_OOM);
	if (chg)
		if (hugepage_subpool_get_pages(spool, chg))
			return ERR_PTR(-VM_FAULT_SIGBUS);

	spin_lock(&hugetlb_lock);
	page = dequeue_huge_page_vma(h, vma, addr, avoid_reserve);
	spin_unlock(&hugetlb_lock);

	if (!page) {
		page = alloc_buddy_huge_page(h, NUMA_NO_NODE);
		if (!page) {
			hugepage_subpool_put_pages(spool, chg);
			return ERR_PTR(-VM_FAULT_SIGBUS);
		}
	}

	set_page_private(page, (unsigned long)spool);

	vma_commit_reservation(h, vma, addr);

	return page;
}