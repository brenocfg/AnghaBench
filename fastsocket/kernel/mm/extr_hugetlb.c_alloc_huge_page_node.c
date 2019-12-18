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
struct hstate {int dummy; } ;

/* Variables and functions */
 struct page* alloc_buddy_huge_page (struct hstate*,int) ; 
 struct page* dequeue_huge_page_node (struct hstate*,int) ; 
 int /*<<< orphan*/  hugetlb_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct page *alloc_huge_page_node(struct hstate *h, int nid)
{
	struct page *page;

	spin_lock(&hugetlb_lock);
	page = dequeue_huge_page_node(h, nid);
	spin_unlock(&hugetlb_lock);

	if (!page)
		page = alloc_buddy_huge_page(h, nid);

	return page;
}