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
typedef  int u64 ;
struct page {int dummy; } ;
struct inode {TYPE_1__* i_sb; struct address_space* i_mapping; } ;
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {int s_blocksize; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OCFS2_SB (TYPE_1__*) ; 
 int PAGE_CACHE_SHIFT ; 
 int PAGE_CACHE_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int block_commit_write (struct page*,unsigned int,unsigned int) ; 
 struct page* grab_cache_page (struct address_space*,unsigned long) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ocfs2_prepare_write_nolock (struct inode*,struct page*,unsigned int,unsigned int) ; 
 scalar_t__ ocfs2_should_order_data (struct inode*) ; 
 int /*<<< orphan*/ * ocfs2_start_walk_page_trans (struct inode*,struct page*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int ocfs2_write_zero_page(struct inode *inode,
				 u64 size)
{
	struct address_space *mapping = inode->i_mapping;
	struct page *page;
	unsigned long index;
	unsigned int offset;
	handle_t *handle = NULL;
	int ret;

	offset = (size & (PAGE_CACHE_SIZE-1)); /* Within page */
	/* ugh.  in prepare/commit_write, if from==to==start of block, we 
	** skip the prepare.  make sure we never send an offset for the start
	** of a block
	*/
	if ((offset & (inode->i_sb->s_blocksize - 1)) == 0) {
		offset++;
	}
	index = size >> PAGE_CACHE_SHIFT;

	page = grab_cache_page(mapping, index);
	if (!page) {
		ret = -ENOMEM;
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_prepare_write_nolock(inode, page, offset, offset);
	if (ret < 0) {
		mlog_errno(ret);
		goto out_unlock;
	}

	if (ocfs2_should_order_data(inode)) {
		handle = ocfs2_start_walk_page_trans(inode, page, offset,
						     offset);
		if (IS_ERR(handle)) {
			ret = PTR_ERR(handle);
			handle = NULL;
			goto out_unlock;
		}
	}

	/* must not update i_size! */
	ret = block_commit_write(page, offset, offset);
	if (ret < 0)
		mlog_errno(ret);
	else
		ret = 0;

	if (handle)
		ocfs2_commit_trans(OCFS2_SB(inode->i_sb), handle);
out_unlock:
	unlock_page(page);
	page_cache_release(page);
out:
	return ret;
}