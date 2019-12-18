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
struct page {int dummy; } ;
struct buffer_head {struct buffer_head* b_this_page; } ;
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageMappedToDisk (struct page*) ; 
 int /*<<< orphan*/  ClearPageUptodate (struct page*) ; 
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 int /*<<< orphan*/  PAGEVEC_SIZE ; 
 int /*<<< orphan*/  __nilfs_clear_page_dirty (struct page*) ; 
 int /*<<< orphan*/  clear_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_nilfs_volatile (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 unsigned int pagevec_count (struct pagevec*) ; 
 int /*<<< orphan*/  pagevec_init (struct pagevec*,int /*<<< orphan*/ ) ; 
 scalar_t__ pagevec_lookup_tag (struct pagevec*,struct address_space*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pagevec_release (struct pagevec*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

void nilfs_clear_dirty_pages(struct address_space *mapping)
{
	struct pagevec pvec;
	unsigned int i;
	pgoff_t index = 0;

	pagevec_init(&pvec, 0);

	while (pagevec_lookup_tag(&pvec, mapping, &index, PAGECACHE_TAG_DIRTY,
				  PAGEVEC_SIZE)) {
		for (i = 0; i < pagevec_count(&pvec); i++) {
			struct page *page = pvec.pages[i];
			struct buffer_head *bh, *head;

			lock_page(page);
			ClearPageUptodate(page);
			ClearPageMappedToDisk(page);
			bh = head = page_buffers(page);
			do {
				lock_buffer(bh);
				clear_buffer_dirty(bh);
				clear_buffer_nilfs_volatile(bh);
				clear_buffer_uptodate(bh);
				clear_buffer_mapped(bh);
				unlock_buffer(bh);
				bh = bh->b_this_page;
			} while (bh != head);

			__nilfs_clear_page_dirty(page);
			unlock_page(page);
		}
		pagevec_release(&pvec);
		cond_resched();
	}
}