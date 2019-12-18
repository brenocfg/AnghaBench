#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct writeback_control {int dummy; } ;
struct page {unsigned int index; TYPE_1__* mapping; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;
typedef  unsigned int loff_t ;
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageChecked (struct page*) ; 
 int /*<<< orphan*/  NOBH ; 
 unsigned int PAGE_CACHE_MASK ; 
 int PAGE_CACHE_SHIFT ; 
 unsigned int PAGE_CACHE_SIZE ; 
 int PF_KSWAPD ; 
 int PF_MEMALLOC ; 
 scalar_t__ PageChecked (struct page*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int __ext4_journalled_writepage (struct page*,struct writeback_control*,unsigned int) ; 
 int /*<<< orphan*/  block_commit_write (struct page*,int /*<<< orphan*/ ,unsigned int) ; 
 int block_prepare_write (struct page*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int block_write_full_page (struct page*,int /*<<< orphan*/ ,struct writeback_control*) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  ext4_bh_delay_or_unwritten ; 
 scalar_t__ ext4_should_journal_data (struct inode*) ; 
 scalar_t__ ext4_should_writeback_data (struct inode*) ; 
 unsigned int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  noalloc_get_block_write ; 
 int nobh_writepage (struct page*,int /*<<< orphan*/ ,struct writeback_control*) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 scalar_t__ page_has_buffers (struct page*) ; 
 int /*<<< orphan*/  redirty_page_for_writepage (struct writeback_control*,struct page*) ; 
 scalar_t__ test_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ext4_writepage (struct inode*,struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 scalar_t__ walk_page_buffers (int /*<<< orphan*/ *,struct buffer_head*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_writepage(struct page *page,
			  struct writeback_control *wbc)
{
	int ret = 0;
	loff_t size;
	unsigned int len;
	struct buffer_head *page_bufs;
	struct inode *inode = page->mapping->host;

	trace_ext4_writepage(inode, page);
	size = i_size_read(inode);
	if (page->index == size >> PAGE_CACHE_SHIFT)
		len = size & ~PAGE_CACHE_MASK;
	else
		len = PAGE_CACHE_SIZE;

	if (page_has_buffers(page)) {
		page_bufs = page_buffers(page);
		if (walk_page_buffers(NULL, page_bufs, 0, len, NULL,
					ext4_bh_delay_or_unwritten)) {
			/*
			 * We don't want to do  block allocation
			 * So redirty the page and return
			 * We may reach here when we do a journal commit
			 * via journal_submit_inode_data_buffers.
			 * If we don't have mapping block we just ignore
			 * them. We can also reach here via shrink_page_list
			 * but it should never be for direct reclaim so warn
			 * if that happens
			 */
			WARN_ON_ONCE((current->flags & (PF_MEMALLOC|PF_KSWAPD)) ==
				PF_MEMALLOC);
			redirty_page_for_writepage(wbc, page);
			unlock_page(page);
			return 0;
		}
	} else {
		/*
		 * The test for page_has_buffers() is subtle:
		 * We know the page is dirty but it lost buffers. That means
		 * that at some moment in time after write_begin()/write_end()
		 * has been called all buffers have been clean and thus they
		 * must have been written at least once. So they are all
		 * mapped and we can happily proceed with mapping them
		 * and writing the page.
		 *
		 * Try to initialize the buffer_heads and check whether
		 * all are mapped and non delay. We don't want to
		 * do block allocation here.
		 */
		ret = block_prepare_write(page, 0, len,
					  noalloc_get_block_write);
		if (!ret) {
			page_bufs = page_buffers(page);
			/* check whether all are mapped and non delay */
			if (walk_page_buffers(NULL, page_bufs, 0, len, NULL,
						ext4_bh_delay_or_unwritten)) {
				redirty_page_for_writepage(wbc, page);
				unlock_page(page);
				return 0;
			}
		} else {
			/*
			 * We can't do block allocation here
			 * so just redity the page and unlock
			 * and return
			 */
			redirty_page_for_writepage(wbc, page);
			unlock_page(page);
			return 0;
		}
		/* now mark the buffer_heads as dirty and uptodate */
		block_commit_write(page, 0, len);
	}

	if (PageChecked(page) && ext4_should_journal_data(inode)) {
		/*
		 * It's mmapped pagecache.  Add buffers and journal it.  There
		 * doesn't seem much point in redirtying the page here.
		 */
		ClearPageChecked(page);
		return __ext4_journalled_writepage(page, wbc, len);
	}

	if (test_opt(inode->i_sb, NOBH) && ext4_should_writeback_data(inode))
		ret = nobh_writepage(page, noalloc_get_block_write, wbc);
	else
		ret = block_write_full_page(page, noalloc_get_block_write,
					    wbc);

	return ret;
}