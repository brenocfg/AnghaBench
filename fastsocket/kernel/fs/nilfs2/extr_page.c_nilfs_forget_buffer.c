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
struct page {int dummy; } ;
struct buffer_head {int b_blocknr; struct page* b_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageMappedToDisk (struct page*) ; 
 int /*<<< orphan*/  ClearPageUptodate (struct page*) ; 
 int /*<<< orphan*/  __nilfs_clear_page_dirty (struct page*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_nilfs_volatile (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 scalar_t__ nilfs_page_buffers_clean (struct page*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

void nilfs_forget_buffer(struct buffer_head *bh)
{
	struct page *page = bh->b_page;

	lock_buffer(bh);
	clear_buffer_nilfs_volatile(bh);
	clear_buffer_dirty(bh);
	if (nilfs_page_buffers_clean(page))
		__nilfs_clear_page_dirty(page);

	clear_buffer_uptodate(bh);
	clear_buffer_mapped(bh);
	bh->b_blocknr = -1;
	ClearPageUptodate(page);
	ClearPageMappedToDisk(page);
	unlock_buffer(bh);
	brelse(bh);
}