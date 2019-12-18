#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {int /*<<< orphan*/  index; int /*<<< orphan*/  lru; } ;
struct list_head {int dummy; } ;
struct file {int dummy; } ;
struct address_space {TYPE_1__* a_ops; } ;
struct TYPE_2__ {int (* readpages ) (struct file*,struct address_space*,struct list_head*,unsigned int) ;int /*<<< orphan*/  (* readpage ) (struct file*,struct page*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  add_to_page_cache_lru (struct page*,struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct page* list_to_page (struct list_head*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  put_pages_list (struct list_head*) ; 
 int stub1 (struct file*,struct address_space*,struct list_head*,unsigned int) ; 
 int /*<<< orphan*/  stub2 (struct file*,struct page*) ; 

__attribute__((used)) static int read_pages(struct address_space *mapping, struct file *filp,
		struct list_head *pages, unsigned nr_pages)
{
	unsigned page_idx;
	int ret;

	if (mapping->a_ops->readpages) {
		ret = mapping->a_ops->readpages(filp, mapping, pages, nr_pages);
		/* Clean up the remaining pages */
		put_pages_list(pages);
		goto out;
	}

	for (page_idx = 0; page_idx < nr_pages; page_idx++) {
		struct page *page = list_to_page(pages);
		list_del(&page->lru);
		if (!add_to_page_cache_lru(page, mapping,
					page->index, GFP_KERNEL)) {
			mapping->a_ops->readpage(filp, page);
		}
		page_cache_release(page);
	}
	ret = 0;
out:
	return ret;
}