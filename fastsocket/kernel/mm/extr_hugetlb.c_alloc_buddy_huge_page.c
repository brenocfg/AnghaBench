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
struct page {int dummy; } ;
struct hstate {scalar_t__ order; scalar_t__ surplus_huge_pages; scalar_t__ nr_overcommit_huge_pages; int /*<<< orphan*/  nr_huge_pages; int /*<<< orphan*/ * surplus_huge_pages_node; int /*<<< orphan*/ * nr_huge_pages_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  HTLB_BUDDY_PGALLOC ; 
 int /*<<< orphan*/  HTLB_BUDDY_PGALLOC_FAIL ; 
 scalar_t__ MAX_ORDER ; 
 int NUMA_NO_NODE ; 
 int __GFP_COMP ; 
 int __GFP_NOWARN ; 
 int __GFP_REPEAT ; 
 int __GFP_THISNODE ; 
 int /*<<< orphan*/  __count_vm_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __free_pages (struct page*,int /*<<< orphan*/ ) ; 
 struct page* alloc_pages (int,int /*<<< orphan*/ ) ; 
 struct page* alloc_pages_exact_node (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ arch_prepare_hugepage (struct page*) ; 
 int /*<<< orphan*/  free_huge_page ; 
 int htlb_alloc_mask ; 
 int /*<<< orphan*/  huge_page_order (struct hstate*) ; 
 int /*<<< orphan*/  hugetlb_lock ; 
 unsigned int page_to_nid (struct page*) ; 
 int /*<<< orphan*/  set_compound_page_dtor (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct page *alloc_buddy_huge_page(struct hstate *h, int nid)
{
	struct page *page;
	unsigned int r_nid;

	if (h->order >= MAX_ORDER)
		return NULL;

	/*
	 * Assume we will successfully allocate the surplus page to
	 * prevent racing processes from causing the surplus to exceed
	 * overcommit
	 *
	 * This however introduces a different race, where a process B
	 * tries to grow the static hugepage pool while alloc_pages() is
	 * called by process A. B will only examine the per-node
	 * counters in determining if surplus huge pages can be
	 * converted to normal huge pages in adjust_pool_surplus(). A
	 * won't be able to increment the per-node counter, until the
	 * lock is dropped by B, but B doesn't drop hugetlb_lock until
	 * no more huge pages can be converted from surplus to normal
	 * state (and doesn't try to convert again). Thus, we have a
	 * case where a surplus huge page exists, the pool is grown, and
	 * the surplus huge page still exists after, even though it
	 * should just have been converted to a normal huge page. This
	 * does not leak memory, though, as the hugepage will be freed
	 * once it is out of use. It also does not allow the counters to
	 * go out of whack in adjust_pool_surplus() as we don't modify
	 * the node values until we've gotten the hugepage and only the
	 * per-node value is checked there.
	 */
	spin_lock(&hugetlb_lock);
	if (h->surplus_huge_pages >= h->nr_overcommit_huge_pages) {
		spin_unlock(&hugetlb_lock);
		return NULL;
	} else {
		h->nr_huge_pages++;
		h->surplus_huge_pages++;
	}
	spin_unlock(&hugetlb_lock);

	if (nid == NUMA_NO_NODE)
		page = alloc_pages(htlb_alloc_mask|__GFP_COMP|
				   __GFP_REPEAT|__GFP_NOWARN,
				   huge_page_order(h));
	else
		page = alloc_pages_exact_node(nid,
			htlb_alloc_mask|__GFP_COMP|__GFP_THISNODE|
			__GFP_REPEAT|__GFP_NOWARN, huge_page_order(h));

	if (page && arch_prepare_hugepage(page)) {
		__free_pages(page, huge_page_order(h));
		return NULL;
	}

	spin_lock(&hugetlb_lock);
	if (page) {
		r_nid = page_to_nid(page);
		set_compound_page_dtor(page, free_huge_page);
		/*
		 * We incremented the global counters already
		 */
		h->nr_huge_pages_node[r_nid]++;
		h->surplus_huge_pages_node[r_nid]++;
		__count_vm_event(HTLB_BUDDY_PGALLOC);
	} else {
		h->nr_huge_pages--;
		h->surplus_huge_pages--;
		__count_vm_event(HTLB_BUDDY_PGALLOC_FAIL);
	}
	spin_unlock(&hugetlb_lock);

	return page;
}