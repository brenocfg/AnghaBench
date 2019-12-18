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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct ocfs2_super {int s_clustersize_bits; int /*<<< orphan*/  sb; } ;
struct ocfs2_extent_tree {int dummy; } ;
struct ocfs2_cached_dealloc_ctxt {int dummy; } ;
struct inode {struct address_space* i_mapping; int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;
struct address_space {int dummy; } ;
struct TYPE_2__ {int ip_dyn_features; scalar_t__ ip_blkno; } ;

/* Variables and functions */
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int OCFS2_INLINE_DATA_FL ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,unsigned long long,unsigned long long,int,int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_clusters_for_bytes (int /*<<< orphan*/ ,scalar_t__) ; 
 int ocfs2_get_clusters (struct inode*,int,int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_init_dealloc_ctxt (struct ocfs2_cached_dealloc_ctxt*) ; 
 int /*<<< orphan*/  ocfs2_init_dinode_extent_tree (struct ocfs2_extent_tree*,int /*<<< orphan*/ ,struct buffer_head*) ; 
 int ocfs2_remove_btree_range (struct inode*,struct ocfs2_extent_tree*,int,int,int,struct ocfs2_cached_dealloc_ctxt*) ; 
 int /*<<< orphan*/  ocfs2_run_deallocs (struct ocfs2_super*,struct ocfs2_cached_dealloc_ctxt*) ; 
 int /*<<< orphan*/  ocfs2_schedule_truncate_log_flush (struct ocfs2_super*,int) ; 
 int /*<<< orphan*/  ocfs2_truncate_cluster_pages (struct inode*,scalar_t__,scalar_t__) ; 
 int ocfs2_truncate_inline (struct inode*,struct buffer_head*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_zero_partial_clusters (struct inode*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  truncate_inode_pages (struct address_space*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmap_mapping_range (struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_remove_inode_range(struct inode *inode,
				    struct buffer_head *di_bh, u64 byte_start,
				    u64 byte_len)
{
	int ret = 0;
	u32 trunc_start, trunc_len, cpos, phys_cpos, alloc_size;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	struct ocfs2_cached_dealloc_ctxt dealloc;
	struct address_space *mapping = inode->i_mapping;
	struct ocfs2_extent_tree et;

	ocfs2_init_dinode_extent_tree(&et, INODE_CACHE(inode), di_bh);
	ocfs2_init_dealloc_ctxt(&dealloc);

	if (byte_len == 0)
		return 0;

	if (OCFS2_I(inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL) {
		ret = ocfs2_truncate_inline(inode, di_bh, byte_start,
					    byte_start + byte_len, 0);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}
		/*
		 * There's no need to get fancy with the page cache
		 * truncate of an inline-data inode. We're talking
		 * about less than a page here, which will be cached
		 * in the dinode buffer anyway.
		 */
		unmap_mapping_range(mapping, 0, 0, 0);
		truncate_inode_pages(mapping, 0);
		goto out;
	}

	trunc_start = ocfs2_clusters_for_bytes(osb->sb, byte_start);
	trunc_len = (byte_start + byte_len) >> osb->s_clustersize_bits;
	if (trunc_len >= trunc_start)
		trunc_len -= trunc_start;
	else
		trunc_len = 0;

	mlog(0, "Inode: %llu, start: %llu, len: %llu, cstart: %u, clen: %u\n",
	     (unsigned long long)OCFS2_I(inode)->ip_blkno,
	     (unsigned long long)byte_start,
	     (unsigned long long)byte_len, trunc_start, trunc_len);

	ret = ocfs2_zero_partial_clusters(inode, byte_start, byte_len);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	cpos = trunc_start;
	while (trunc_len) {
		ret = ocfs2_get_clusters(inode, cpos, &phys_cpos,
					 &alloc_size, NULL);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		if (alloc_size > trunc_len)
			alloc_size = trunc_len;

		/* Only do work for non-holes */
		if (phys_cpos != 0) {
			ret = ocfs2_remove_btree_range(inode, &et, cpos,
						       phys_cpos, alloc_size,
						       &dealloc);
			if (ret) {
				mlog_errno(ret);
				goto out;
			}
		}

		cpos += alloc_size;
		trunc_len -= alloc_size;
	}

	ocfs2_truncate_cluster_pages(inode, byte_start, byte_len);

out:
	ocfs2_schedule_truncate_log_flush(osb, 1);
	ocfs2_run_deallocs(osb, &dealloc);

	return ret;
}