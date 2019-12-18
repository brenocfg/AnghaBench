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
struct page_list {int /*<<< orphan*/  page; struct page_list* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct page_list*) ; 

__attribute__((used)) static void free_cache_pages(struct page_list *list)
{
	while (list) {
		struct page_list *pl = list;

		list = pl->next;
		BUG_ON(!pl->page);
		__free_page(pl->page);
		kfree(pl);
	}
}