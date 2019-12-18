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
struct page_list {struct page_list* next; struct page* page; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cache_pages (struct page_list*) ; 
 struct page_list* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct page_list *alloc_cache_pages(unsigned pages)
{
	struct page_list *pl, *ret = NULL;
	struct page *page;

	while (pages--) {
		page = alloc_page(GFP_NOIO);
		if (!page)
			goto err;

		pl = kmalloc(sizeof(*pl), GFP_NOIO);
		if (!pl) {
			__free_page(page);
			goto err;
		}

		pl->page = page;
		pl->next = ret;
		ret = pl;
	}

	return ret;

err:
	free_cache_pages(ret);
	return NULL;
}