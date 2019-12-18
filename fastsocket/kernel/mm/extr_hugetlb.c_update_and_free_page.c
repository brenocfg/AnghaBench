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
struct page {int flags; } ;
struct hstate {scalar_t__ order; int /*<<< orphan*/ * nr_huge_pages_node; int /*<<< orphan*/  nr_huge_pages; } ;

/* Variables and functions */
 scalar_t__ MAX_ORDER ; 
 int PG_active ; 
 int PG_dirty ; 
 int PG_error ; 
 int PG_locked ; 
 int PG_private ; 
 int PG_referenced ; 
 int PG_reserved ; 
 int PG_writeback ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  __free_pages (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_release_hugepage (struct page*) ; 
 int /*<<< orphan*/  huge_page_order (struct hstate*) ; 
 size_t page_to_nid (struct page*) ; 
 int pages_per_huge_page (struct hstate*) ; 
 int /*<<< orphan*/  set_compound_page_dtor (struct page*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_page_refcounted (struct page*) ; 

__attribute__((used)) static void update_and_free_page(struct hstate *h, struct page *page)
{
	int i;

	VM_BUG_ON(h->order >= MAX_ORDER);

	h->nr_huge_pages--;
	h->nr_huge_pages_node[page_to_nid(page)]--;
	for (i = 0; i < pages_per_huge_page(h); i++) {
		page[i].flags &= ~(1 << PG_locked | 1 << PG_error | 1 << PG_referenced |
				1 << PG_dirty | 1 << PG_active | 1 << PG_reserved |
				1 << PG_private | 1<< PG_writeback);
	}
	set_compound_page_dtor(page, NULL);
	set_page_refcounted(page);
	arch_release_hugepage(page);
	__free_pages(page, huge_page_order(h));
}