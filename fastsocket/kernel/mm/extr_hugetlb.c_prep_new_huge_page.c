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
struct hstate {int /*<<< orphan*/ * nr_huge_pages_node; int /*<<< orphan*/  nr_huge_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_huge_page ; 
 int /*<<< orphan*/  hugetlb_lock ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_compound_page_dtor (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void prep_new_huge_page(struct hstate *h, struct page *page, int nid)
{
	set_compound_page_dtor(page, free_huge_page);
	spin_lock(&hugetlb_lock);
	h->nr_huge_pages++;
	h->nr_huge_pages_node[nid]++;
	spin_unlock(&hugetlb_lock);
	put_page(page); /* free it into the hugepage allocator */
}