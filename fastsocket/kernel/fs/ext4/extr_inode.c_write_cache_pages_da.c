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
struct writeback_control {long nr_to_write; int range_start; int range_end; scalar_t__ sync_mode; } ;
struct pagevec {struct page** pages; } ;
struct page {int index; struct address_space* mapping; } ;
struct mpage_da_data {int dummy; } ;
struct address_space {int dummy; } ;
typedef  int pgoff_t ;

/* Variables and functions */
 int AOP_WRITEPAGE_ACTIVATE ; 
 int /*<<< orphan*/  BUG_ON (scalar_t__) ; 
 int PAGECACHE_TAG_DIRTY ; 
 int PAGECACHE_TAG_TOWRITE ; 
 scalar_t__ PAGEVEC_SIZE ; 
 int PAGE_CACHE_SHIFT ; 
 int /*<<< orphan*/  PageDirty (struct page*) ; 
 scalar_t__ PageWriteback (struct page*) ; 
 scalar_t__ WB_SYNC_ALL ; 
 scalar_t__ WB_SYNC_NONE ; 
 int __mpage_da_writepage (struct page*,struct writeback_control*,struct mpage_da_data*) ; 
 int /*<<< orphan*/  clear_page_dirty_for_io (struct page*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 scalar_t__ min (int,int) ; 
 int /*<<< orphan*/  pagevec_init (struct pagevec*,int /*<<< orphan*/ ) ; 
 unsigned int pagevec_lookup_tag (struct pagevec*,struct address_space*,int*,int,scalar_t__) ; 
 int /*<<< orphan*/  pagevec_release (struct pagevec*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  wait_on_page_writeback (struct page*) ; 

__attribute__((used)) static int write_cache_pages_da(struct address_space *mapping,
				struct writeback_control *wbc,
				struct mpage_da_data *mpd,
				pgoff_t *done_index)
{
	int ret = 0;
	int done = 0;
	struct pagevec pvec;
	unsigned nr_pages;
	pgoff_t index;
	pgoff_t end;		/* Inclusive */
	long nr_to_write = wbc->nr_to_write;
	int tag;

	pagevec_init(&pvec, 0);
	index = wbc->range_start >> PAGE_CACHE_SHIFT;
	end = wbc->range_end >> PAGE_CACHE_SHIFT;

	if (wbc->sync_mode == WB_SYNC_ALL)
		tag = PAGECACHE_TAG_TOWRITE;
	else
		tag = PAGECACHE_TAG_DIRTY;

	*done_index = index;
	while (!done && (index <= end)) {
		int i;

		nr_pages = pagevec_lookup_tag(&pvec, mapping, &index, tag,
			      min(end - index, (pgoff_t)PAGEVEC_SIZE-1) + 1);
		if (nr_pages == 0)
			break;

		for (i = 0; i < nr_pages; i++) {
			struct page *page = pvec.pages[i];

			/*
			 * At this point, the page may be truncated or
			 * invalidated (changing page->mapping to NULL), or
			 * even swizzled back from swapper_space to tmpfs file
			 * mapping. However, page->index will not change
			 * because we have a reference on the page.
			 */
			if (page->index > end) {
				done = 1;
				break;
			}

			*done_index = page->index + 1;

			lock_page(page);

			/*
			 * Page truncated or invalidated. We can freely skip it
			 * then, even for data integrity operations: the page
			 * has disappeared concurrently, so there could be no
			 * real expectation of this data interity operation
			 * even if there is now a new, dirty page at the same
			 * pagecache address.
			 */
			if (unlikely(page->mapping != mapping)) {
continue_unlock:
				unlock_page(page);
				continue;
			}

			if (!PageDirty(page)) {
				/* someone wrote it for us */
				goto continue_unlock;
			}

			if (PageWriteback(page)) {
				if (wbc->sync_mode != WB_SYNC_NONE)
					wait_on_page_writeback(page);
				else
					goto continue_unlock;
			}

			BUG_ON(PageWriteback(page));
			if (!clear_page_dirty_for_io(page))
				goto continue_unlock;

			ret = __mpage_da_writepage(page, wbc, mpd);
			if (unlikely(ret)) {
				if (ret == AOP_WRITEPAGE_ACTIVATE) {
					unlock_page(page);
					ret = 0;
				} else {
					done = 1;
					break;
				}
			}

			if (nr_to_write > 0) {
				nr_to_write--;
				if (nr_to_write == 0 &&
				    wbc->sync_mode == WB_SYNC_NONE) {
					/*
					 * We stop writing back only if we are
					 * not doing integrity sync. In case of
					 * integrity sync we have to keep going
					 * because someone may be concurrently
					 * dirtying pages, and we might have
					 * synced a lot of newly appeared dirty
					 * pages, but have not synced all of the
					 * old dirty pages.
					 */
					done = 1;
					break;
				}
			}
		}
		pagevec_release(&pvec);
		cond_resched();
	}
	return ret;
}