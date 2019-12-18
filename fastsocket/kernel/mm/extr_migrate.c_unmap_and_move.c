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
struct page {int /*<<< orphan*/  lru; } ;
typedef  struct page* (* new_page_t ) (struct page*,unsigned long,int**) ;
typedef  enum migrate_mode { ____Placeholder_migrate_mode } migrate_mode ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 scalar_t__ NR_ISOLATED_ANON ; 
 int /*<<< orphan*/  PageTransHuge (struct page*) ; 
 int __unmap_and_move (struct page*,struct page*,int,int,int) ; 
 int /*<<< orphan*/  dec_zone_page_state (struct page*,scalar_t__) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int page_count (struct page*) ; 
 scalar_t__ page_is_file_cache (struct page*) ; 
 int page_to_nid (struct page*) ; 
 int /*<<< orphan*/  putback_lru_page (struct page*) ; 
 int /*<<< orphan*/  split_huge_page (struct page*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int unmap_and_move(new_page_t get_new_page, unsigned long private,
			struct page *page, int force, bool offlining,
			enum migrate_mode mode)
{
	int rc = 0;
	int *result = NULL;
	struct page *newpage = get_new_page(page, private, &result);

	if (!newpage)
		return -ENOMEM;

	if (page_count(page) == 1) {
		/* page was freed from under us. So we are done. */
		goto out;
	}

	if (unlikely(PageTransHuge(page)))
		if (unlikely(split_huge_page(page)))
			goto out;

	rc = __unmap_and_move(page, newpage, force, offlining, mode);
out:
	if (rc != -EAGAIN) {
 		/*
 		 * A page that has been migrated has all references
 		 * removed and will be freed. A page that has not been
 		 * migrated will have kepts its references and be
 		 * restored.
 		 */
 		list_del(&page->lru);
		dec_zone_page_state(page, NR_ISOLATED_ANON +
				page_is_file_cache(page));
		putback_lru_page(page);
	}
	/*
	 * Move the new page to the LRU. If migration was not successful
	 * then this will free the page.
	 */
	putback_lru_page(newpage);
	if (result) {
		if (rc)
			*result = rc;
		else
			*result = page_to_nid(newpage);
	}
	return rc;
}