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
struct page {scalar_t__ index; struct address_space* mapping; } ;
struct inode {struct address_space* i_mapping; } ;
struct buffer_head {struct buffer_head* b_this_page; } ;
struct address_space {int dummy; } ;
typedef  scalar_t__ pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 scalar_t__ PAGEVEC_SIZE ; 
 int /*<<< orphan*/  PageDirty (struct page*) ; 
 scalar_t__ PageWriteback (struct page*) ; 
 int /*<<< orphan*/  buffer_delay (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_unwritten (struct buffer_head*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 scalar_t__ page_has_buffers (struct page*) ; 
 int /*<<< orphan*/  pagevec_init (struct pagevec*,int /*<<< orphan*/ ) ; 
 int pagevec_lookup_tag (struct pagevec*,struct address_space*,scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pagevec_release (struct pagevec*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static pgoff_t ext4_num_dirty_pages(struct inode *inode, pgoff_t idx,
				    unsigned int max_pages)
{
	struct address_space *mapping = inode->i_mapping;
	pgoff_t	index;
	struct pagevec pvec;
	pgoff_t num = 0;
	int i, nr_pages, done = 0;

	if (max_pages == 0)
		return 0;
	pagevec_init(&pvec, 0);
	while (!done) {
		index = idx;
		nr_pages = pagevec_lookup_tag(&pvec, mapping, &index,
					      PAGECACHE_TAG_DIRTY,
					      (pgoff_t)PAGEVEC_SIZE);
		if (nr_pages == 0)
			break;
		for (i = 0; i < nr_pages; i++) {
			struct page *page = pvec.pages[i];
			struct buffer_head *bh, *head;

			lock_page(page);
			if (unlikely(page->mapping != mapping) ||
			    !PageDirty(page) ||
			    PageWriteback(page) ||
			    page->index != idx) {
				done = 1;
				unlock_page(page);
				break;
			}
			if (page_has_buffers(page)) {
				bh = head = page_buffers(page);
				do {
					if (!buffer_delay(bh) &&
					    !buffer_unwritten(bh))
						done = 1;
					bh = bh->b_this_page;
				} while (!done && (bh != head));
			}
			unlock_page(page);
			if (done)
				break;
			idx++;
			num++;
			if (num >= max_pages) {
				done = 1;
				break;
			}
		}
		pagevec_release(&pvec);
	}
	return num;
}