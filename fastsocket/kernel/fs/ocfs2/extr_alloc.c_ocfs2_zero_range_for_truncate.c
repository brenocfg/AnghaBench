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
typedef  scalar_t__ u64 ;
struct super_block {scalar_t__ s_blocksize_bits; } ;
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mapping; struct super_block* i_sb; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 unsigned int OCFS2_EXT_UNWRITTEN ; 
 int /*<<< orphan*/  OCFS2_SB (struct super_block*) ; 
 int /*<<< orphan*/  SYNC_FILE_RANGE_WRITE ; 
 int do_sync_mapping_range (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 struct page** kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct page**) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_extent_map_get_blocks (struct inode*,scalar_t__,scalar_t__*,int /*<<< orphan*/ *,unsigned int*) ; 
 int ocfs2_grab_eof_pages (struct inode*,scalar_t__,scalar_t__,struct page**,int*) ; 
 int /*<<< orphan*/  ocfs2_pages_per_cluster (struct super_block*) ; 
 int /*<<< orphan*/  ocfs2_sparse_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_zero_cluster_pages (struct inode*,scalar_t__,scalar_t__,struct page**,int,scalar_t__,int /*<<< orphan*/ *) ; 

int ocfs2_zero_range_for_truncate(struct inode *inode, handle_t *handle,
				  u64 range_start, u64 range_end)
{
	int ret = 0, numpages;
	struct page **pages = NULL;
	u64 phys;
	unsigned int ext_flags;
	struct super_block *sb = inode->i_sb;

	/*
	 * File systems which don't support sparse files zero on every
	 * extend.
	 */
	if (!ocfs2_sparse_alloc(OCFS2_SB(sb)))
		return 0;

	pages = kcalloc(ocfs2_pages_per_cluster(sb),
			sizeof(struct page *), GFP_NOFS);
	if (pages == NULL) {
		ret = -ENOMEM;
		mlog_errno(ret);
		goto out;
	}

	if (range_start == range_end)
		goto out;

	ret = ocfs2_extent_map_get_blocks(inode,
					  range_start >> sb->s_blocksize_bits,
					  &phys, NULL, &ext_flags);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	/*
	 * Tail is a hole, or is marked unwritten. In either case, we
	 * can count on read and write to return/push zero's.
	 */
	if (phys == 0 || ext_flags & OCFS2_EXT_UNWRITTEN)
		goto out;

	ret = ocfs2_grab_eof_pages(inode, range_start, range_end, pages,
				   &numpages);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	ocfs2_zero_cluster_pages(inode, range_start, range_end, pages,
				 numpages, phys, handle);

	/*
	 * Initiate writeout of the pages we zero'd here. We don't
	 * wait on them - the truncate_inode_pages() call later will
	 * do that for us.
	 */
	ret = do_sync_mapping_range(inode->i_mapping, range_start,
				    range_end - 1, SYNC_FILE_RANGE_WRITE);
	if (ret)
		mlog_errno(ret);

out:
	if (pages)
		kfree(pages);

	return ret;
}