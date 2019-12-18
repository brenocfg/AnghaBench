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
struct page {scalar_t__ index; } ;
struct mpage_da_data {scalar_t__ first_page; scalar_t__ next_page; struct inode* inode; } ;
struct inode {struct address_space* i_mapping; } ;
struct address_space {int dummy; } ;
typedef  scalar_t__ pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ClearPageUptodate (struct page*) ; 
 int /*<<< orphan*/  PAGEVEC_SIZE ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int PageWriteback (struct page*) ; 
 int /*<<< orphan*/  block_invalidatepage (struct page*,int /*<<< orphan*/ ) ; 
 int pagevec_lookup (struct pagevec*,struct address_space*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pagevec_release (struct pagevec*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static void ext4_da_block_invalidatepages(struct mpage_da_data *mpd)
{
	int nr_pages, i;
	pgoff_t index, end;
	struct pagevec pvec;
	struct inode *inode = mpd->inode;
	struct address_space *mapping = inode->i_mapping;

	index = mpd->first_page;
	end   = mpd->next_page - 1;
	while (index <= end) {
		nr_pages = pagevec_lookup(&pvec, mapping, index, PAGEVEC_SIZE);
		if (nr_pages == 0)
			break;
		for (i = 0; i < nr_pages; i++) {
			struct page *page = pvec.pages[i];
			if (page->index > end)
				break;
			BUG_ON(!PageLocked(page));
			BUG_ON(PageWriteback(page));
			block_invalidatepage(page, 0);
			ClearPageUptodate(page);
			unlock_page(page);
		}
		index = pvec.pages[nr_pages - 1]->index + 1;
		pagevec_release(&pvec);
	}
	return;
}