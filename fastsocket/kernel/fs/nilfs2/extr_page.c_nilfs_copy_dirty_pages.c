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
struct pagevec {struct page** pages; } ;
struct page {int /*<<< orphan*/  index; } ;
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NILFS_PAGE_BUG (struct page*,char*) ; 
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 int /*<<< orphan*/  PAGEVEC_SIZE ; 
 int /*<<< orphan*/  PageDirty (struct page*) ; 
 int /*<<< orphan*/  __set_page_dirty_nobuffers (struct page*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 struct page* grab_cache_page (struct address_space*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  nilfs_copy_page (struct page*,struct page*,int) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  page_has_buffers (struct page*) ; 
 unsigned int pagevec_count (struct pagevec*) ; 
 int /*<<< orphan*/  pagevec_init (struct pagevec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pagevec_lookup_tag (struct pagevec*,struct address_space*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pagevec_release (struct pagevec*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int nilfs_copy_dirty_pages(struct address_space *dmap,
			   struct address_space *smap)
{
	struct pagevec pvec;
	unsigned int i;
	pgoff_t index = 0;
	int err = 0;

	pagevec_init(&pvec, 0);
repeat:
	if (!pagevec_lookup_tag(&pvec, smap, &index, PAGECACHE_TAG_DIRTY,
				PAGEVEC_SIZE))
		return 0;

	for (i = 0; i < pagevec_count(&pvec); i++) {
		struct page *page = pvec.pages[i], *dpage;

		lock_page(page);
		if (unlikely(!PageDirty(page)))
			NILFS_PAGE_BUG(page, "inconsistent dirty state");

		dpage = grab_cache_page(dmap, page->index);
		if (unlikely(!dpage)) {
			/* No empty page is added to the page cache */
			err = -ENOMEM;
			unlock_page(page);
			break;
		}
		if (unlikely(!page_has_buffers(page)))
			NILFS_PAGE_BUG(page,
				       "found empty page in dat page cache");

		nilfs_copy_page(dpage, page, 1);
		__set_page_dirty_nobuffers(dpage);

		unlock_page(dpage);
		page_cache_release(dpage);
		unlock_page(page);
	}
	pagevec_release(&pvec);
	cond_resched();

	if (likely(!err))
		goto repeat;
	return err;
}