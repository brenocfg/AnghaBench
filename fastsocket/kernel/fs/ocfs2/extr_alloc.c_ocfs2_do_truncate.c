#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u64 ;
struct ocfs2_truncate_context {int /*<<< orphan*/  tc_dealloc; } ;
struct ocfs2_super {int /*<<< orphan*/  sb; } ;
struct ocfs2_path {int dummy; } ;
struct ocfs2_extent_list {scalar_t__ l_tree_depth; TYPE_2__* l_recs; } ;
struct ocfs2_extent_block {scalar_t__ h_next_leaf_blk; scalar_t__ h_blkno; } ;
struct TYPE_4__ {struct ocfs2_extent_list i_list; } ;
struct ocfs2_dinode {scalar_t__ i_last_eb_blk; int /*<<< orphan*/  i_clusters; TYPE_1__ id2; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct inode {int /*<<< orphan*/  i_blocks; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_6__ {int /*<<< orphan*/  ip_lock; scalar_t__ ip_clusters; } ;
struct TYPE_5__ {scalar_t__ e_int_clusters; } ;

/* Variables and functions */
 int EROFS ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int OCFS2_EXT_REFCOUNTED ; 
 TYPE_3__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int /*<<< orphan*/  ocfs2_blocks_to_clusters (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ocfs2_clusters_to_bytes (int /*<<< orphan*/ ,unsigned int) ; 
 int ocfs2_decrease_refcount (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,struct ocfs2_alloc_context*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ocfs2_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_find_new_last_ext_blk (struct inode*,unsigned int,struct ocfs2_path*,struct buffer_head**) ; 
 int /*<<< orphan*/  ocfs2_inode_sector_count (struct inode*) ; 
 int ocfs2_journal_access_eb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_access_path (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ocfs2_path*) ; 
 int ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int ocfs2_trim_tree (struct inode*,struct ocfs2_path*,int /*<<< orphan*/ *,struct ocfs2_truncate_context*,unsigned int,scalar_t__*,int*) ; 
 int ocfs2_truncate_log_append (struct ocfs2_super*,int /*<<< orphan*/ *,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfs_dq_free_space_nodirty (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_do_truncate(struct ocfs2_super *osb,
			     unsigned int clusters_to_del,
			     struct inode *inode,
			     struct buffer_head *fe_bh,
			     handle_t *handle,
			     struct ocfs2_truncate_context *tc,
			     struct ocfs2_path *path,
			     struct ocfs2_alloc_context *meta_ac)
{
	int status;
	struct ocfs2_dinode *fe;
	struct ocfs2_extent_block *last_eb = NULL;
	struct ocfs2_extent_list *el;
	struct buffer_head *last_eb_bh = NULL;
	u64 delete_blk = 0;
	u8 rec_flags;

	fe = (struct ocfs2_dinode *) fe_bh->b_data;

	status = ocfs2_find_new_last_ext_blk(inode, clusters_to_del,
					     path, &last_eb_bh);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	/*
	 * Each component will be touched, so we might as well journal
	 * here to avoid having to handle errors later.
	 */
	status = ocfs2_journal_access_path(INODE_CACHE(inode), handle, path);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	if (last_eb_bh) {
		status = ocfs2_journal_access_eb(handle, INODE_CACHE(inode), last_eb_bh,
						 OCFS2_JOURNAL_ACCESS_WRITE);
		if (status < 0) {
			mlog_errno(status);
			goto bail;
		}

		last_eb = (struct ocfs2_extent_block *) last_eb_bh->b_data;
	}

	el = &(fe->id2.i_list);

	/*
	 * Lower levels depend on this never happening, but it's best
	 * to check it up here before changing the tree.
	 */
	if (el->l_tree_depth && el->l_recs[0].e_int_clusters == 0) {
		ocfs2_error(inode->i_sb,
			    "Inode %lu has an empty extent record, depth %u\n",
			    inode->i_ino, le16_to_cpu(el->l_tree_depth));
		status = -EROFS;
		goto bail;
	}

	vfs_dq_free_space_nodirty(inode,
			ocfs2_clusters_to_bytes(osb->sb, clusters_to_del));
	spin_lock(&OCFS2_I(inode)->ip_lock);
	OCFS2_I(inode)->ip_clusters = le32_to_cpu(fe->i_clusters) -
				      clusters_to_del;
	spin_unlock(&OCFS2_I(inode)->ip_lock);
	le32_add_cpu(&fe->i_clusters, -clusters_to_del);
	inode->i_blocks = ocfs2_inode_sector_count(inode);

	status = ocfs2_trim_tree(inode, path, handle, tc,
				 clusters_to_del, &delete_blk, &rec_flags);
	if (status) {
		mlog_errno(status);
		goto bail;
	}

	if (le32_to_cpu(fe->i_clusters) == 0) {
		/* trunc to zero is a special case. */
		el->l_tree_depth = 0;
		fe->i_last_eb_blk = 0;
	} else if (last_eb)
		fe->i_last_eb_blk = last_eb->h_blkno;

	status = ocfs2_journal_dirty(handle, fe_bh);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	if (last_eb) {
		/* If there will be a new last extent block, then by
		 * definition, there cannot be any leaves to the right of
		 * him. */
		last_eb->h_next_leaf_blk = 0;
		status = ocfs2_journal_dirty(handle, last_eb_bh);
		if (status < 0) {
			mlog_errno(status);
			goto bail;
		}
	}

	if (delete_blk) {
		if (rec_flags & OCFS2_EXT_REFCOUNTED)
			status = ocfs2_decrease_refcount(inode, handle,
					ocfs2_blocks_to_clusters(osb->sb,
								 delete_blk),
					clusters_to_del, meta_ac,
					&tc->tc_dealloc, 1);
		else
			status = ocfs2_truncate_log_append(osb, handle,
							   delete_blk,
							   clusters_to_del);
		if (status < 0) {
			mlog_errno(status);
			goto bail;
		}
	}
	status = 0;
bail:
	brelse(last_eb_bh);
	mlog_exit(status);
	return status;
}