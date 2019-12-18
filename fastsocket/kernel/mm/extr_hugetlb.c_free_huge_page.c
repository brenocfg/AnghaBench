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
struct page {int /*<<< orphan*/  lru; int /*<<< orphan*/ * mapping; } ;
struct hugepage_subpool {int dummy; } ;
struct hstate {scalar_t__* surplus_huge_pages_node; int /*<<< orphan*/  surplus_huge_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ MAX_ORDER ; 
 int /*<<< orphan*/  enqueue_huge_page (struct hstate*,struct page*) ; 
 scalar_t__ huge_page_order (struct hstate*) ; 
 int /*<<< orphan*/  hugepage_subpool_put_pages (struct hugepage_subpool*,int) ; 
 int /*<<< orphan*/  hugetlb_lock ; 
 int /*<<< orphan*/  page_count (struct page*) ; 
 struct hstate* page_hstate (struct page*) ; 
 int /*<<< orphan*/  page_mapcount (struct page*) ; 
 scalar_t__ page_private (struct page*) ; 
 int page_to_nid (struct page*) ; 
 int /*<<< orphan*/  set_page_private (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_and_free_page (struct hstate*,struct page*) ; 

__attribute__((used)) static void free_huge_page(struct page *page)
{
	/*
	 * Can't pass hstate in here because it is called from the
	 * compound page destructor.
	 */
	struct hstate *h = page_hstate(page);
	int nid = page_to_nid(page);
	struct hugepage_subpool *spool =
		(struct hugepage_subpool *)page_private(page);

	set_page_private(page, 0);
	page->mapping = NULL;
	BUG_ON(page_count(page));
	BUG_ON(page_mapcount(page));
	INIT_LIST_HEAD(&page->lru);

	spin_lock(&hugetlb_lock);
	if (h->surplus_huge_pages_node[nid] && huge_page_order(h) < MAX_ORDER) {
		update_and_free_page(h, page);
		h->surplus_huge_pages--;
		h->surplus_huge_pages_node[nid]--;
	} else {
		enqueue_huge_page(h, page);
	}
	spin_unlock(&hugetlb_lock);
	hugepage_subpool_put_pages(spool, 1);
}