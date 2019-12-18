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
struct hstate {scalar_t__ order; } ;

/* Variables and functions */
 scalar_t__ MAX_ORDER ; 
 int __GFP_COMP ; 
 int __GFP_NOWARN ; 
 int __GFP_REPEAT ; 
 int __GFP_THISNODE ; 
 int /*<<< orphan*/  __free_pages (struct page*,int /*<<< orphan*/ ) ; 
 struct page* alloc_pages_exact_node (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ arch_prepare_hugepage (struct page*) ; 
 int htlb_alloc_mask ; 
 int /*<<< orphan*/  huge_page_order (struct hstate*) ; 
 int /*<<< orphan*/  prep_new_huge_page (struct hstate*,struct page*,int) ; 

__attribute__((used)) static struct page *alloc_fresh_huge_page_node(struct hstate *h, int nid)
{
	struct page *page;

	if (h->order >= MAX_ORDER)
		return NULL;

	page = alloc_pages_exact_node(nid,
		htlb_alloc_mask|__GFP_COMP|__GFP_THISNODE|
						__GFP_REPEAT|__GFP_NOWARN,
		huge_page_order(h));
	if (page) {
		if (arch_prepare_hugepage(page)) {
			__free_pages(page, huge_page_order(h));
			return NULL;
		}
		prep_new_huge_page(h, page, nid);
	}

	return page;
}