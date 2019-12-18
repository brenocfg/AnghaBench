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
typedef  int /*<<< orphan*/  u64 ;
struct page {int dummy; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_jbd2_file_inode (int /*<<< orphan*/ *,struct inode*) ; 
 int ocfs2_map_page_blocks (struct page*,int /*<<< orphan*/ *,struct inode*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_should_order_data (struct inode*) ; 
 int /*<<< orphan*/  ocfs2_zero_func ; 
 int /*<<< orphan*/  page_buffers (struct page*) ; 
 int walk_page_buffers (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,unsigned int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zero_user_segment (struct page*,unsigned int,unsigned int) ; 

void ocfs2_map_and_dirty_page(struct inode *inode, handle_t *handle,
			      unsigned int from, unsigned int to,
			      struct page *page, int zero, u64 *phys)
{
	int ret, partial = 0;

	ret = ocfs2_map_page_blocks(page, phys, inode, from, to, 0);
	if (ret)
		mlog_errno(ret);

	if (zero)
		zero_user_segment(page, from, to);

	/*
	 * Need to set the buffers we zero'd into uptodate
	 * here if they aren't - ocfs2_map_page_blocks()
	 * might've skipped some
	 */
	ret = walk_page_buffers(handle, page_buffers(page),
				from, to, &partial,
				ocfs2_zero_func);
	if (ret < 0)
		mlog_errno(ret);
	else if (ocfs2_should_order_data(inode)) {
		ret = ocfs2_jbd2_file_inode(handle, inode);
		if (ret < 0)
			mlog_errno(ret);
	}

	if (!partial)
		SetPageUptodate(page);

	flush_dcache_page(page);
}