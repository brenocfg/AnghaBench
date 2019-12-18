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
typedef  int /*<<< orphan*/  u16 ;
struct ocfs2_super {int dummy; } ;
struct ocfs2_refcount_tree {int /*<<< orphan*/  rf_ci; } ;
struct ocfs2_refcount_block {int /*<<< orphan*/  rf_count; int /*<<< orphan*/  rf_suballoc_slot; int /*<<< orphan*/  rf_suballoc_bit; scalar_t__ rf_blkno; } ;
struct ocfs2_inode_info {int ip_dyn_features; int /*<<< orphan*/  ip_lock; } ;
struct ocfs2_dinode {scalar_t__ i_refcount_loc; int /*<<< orphan*/  i_dyn_features; } ;
struct inode {int /*<<< orphan*/  i_mutex; int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EXTENT_ALLOC_SYSTEM_INODE ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int OCFS2_HAS_REFCOUNT_FL ; 
 struct ocfs2_inode_info* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 int OCFS2_REFCOUNT_TREE_REMOVE_CREDITS ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ OCFS2_SUBALLOC_FREE ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_erase_refcount_tree_from_list (struct ocfs2_super*,struct ocfs2_refcount_tree*) ; 
 int ocfs2_free_suballoc_bits (int /*<<< orphan*/ *,struct inode*,struct buffer_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct inode* ocfs2_get_system_file_inode (struct ocfs2_super*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_inode_lock (struct inode*,struct buffer_head**,int) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 
 int ocfs2_journal_access_di (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_access_rb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int ocfs2_lock_refcount_tree (struct ocfs2_super*,int /*<<< orphan*/ ,int,struct ocfs2_refcount_tree**,struct buffer_head**) ; 
 int /*<<< orphan*/  ocfs2_refcount_tree_put (struct ocfs2_refcount_tree*) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int) ; 
 int /*<<< orphan*/  ocfs2_unlock_refcount_tree (struct ocfs2_super*,struct ocfs2_refcount_tree*,int) ; 
 int /*<<< orphan*/  ocfs2_which_suballoc_group (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int ocfs2_remove_refcount_tree(struct inode *inode, struct buffer_head *di_bh)
{
	int ret, delete_tree = 0;
	handle_t *handle = NULL;
	struct ocfs2_dinode *di = (struct ocfs2_dinode *)di_bh->b_data;
	struct ocfs2_inode_info *oi = OCFS2_I(inode);
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	struct ocfs2_refcount_block *rb;
	struct inode *alloc_inode = NULL;
	struct buffer_head *alloc_bh = NULL;
	struct buffer_head *blk_bh = NULL;
	struct ocfs2_refcount_tree *ref_tree;
	int credits = OCFS2_REFCOUNT_TREE_REMOVE_CREDITS;
	u64 blk = 0, bg_blkno = 0, ref_blkno = le64_to_cpu(di->i_refcount_loc);
	u16 bit = 0;

	if (!(oi->ip_dyn_features & OCFS2_HAS_REFCOUNT_FL))
		return 0;

	BUG_ON(!ref_blkno);
	ret = ocfs2_lock_refcount_tree(osb, ref_blkno, 1, &ref_tree, &blk_bh);
	if (ret) {
		mlog_errno(ret);
		return ret;
	}

	rb = (struct ocfs2_refcount_block *)blk_bh->b_data;

	/*
	 * If we are the last user, we need to free the block.
	 * So lock the allocator ahead.
	 */
	if (le32_to_cpu(rb->rf_count) == 1) {
		blk = le64_to_cpu(rb->rf_blkno);
		bit = le16_to_cpu(rb->rf_suballoc_bit);
		bg_blkno = ocfs2_which_suballoc_group(blk, bit);

		alloc_inode = ocfs2_get_system_file_inode(osb,
					EXTENT_ALLOC_SYSTEM_INODE,
					le16_to_cpu(rb->rf_suballoc_slot));
		if (!alloc_inode) {
			ret = -ENOMEM;
			mlog_errno(ret);
			goto out;
		}
		mutex_lock(&alloc_inode->i_mutex);

		ret = ocfs2_inode_lock(alloc_inode, &alloc_bh, 1);
		if (ret) {
			mlog_errno(ret);
			goto out_mutex;
		}

		credits += OCFS2_SUBALLOC_FREE;
	}

	handle = ocfs2_start_trans(osb, credits);
	if (IS_ERR(handle)) {
		ret = PTR_ERR(handle);
		mlog_errno(ret);
		goto out_unlock;
	}

	ret = ocfs2_journal_access_di(handle, INODE_CACHE(inode), di_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret) {
		mlog_errno(ret);
		goto out_commit;
	}

	ret = ocfs2_journal_access_rb(handle, &ref_tree->rf_ci, blk_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret) {
		mlog_errno(ret);
		goto out_commit;
	}

	spin_lock(&oi->ip_lock);
	oi->ip_dyn_features &= ~OCFS2_HAS_REFCOUNT_FL;
	di->i_dyn_features = cpu_to_le16(oi->ip_dyn_features);
	di->i_refcount_loc = 0;
	spin_unlock(&oi->ip_lock);
	ocfs2_journal_dirty(handle, di_bh);

	le32_add_cpu(&rb->rf_count , -1);
	ocfs2_journal_dirty(handle, blk_bh);

	if (!rb->rf_count) {
		delete_tree = 1;
		ocfs2_erase_refcount_tree_from_list(osb, ref_tree);
		ret = ocfs2_free_suballoc_bits(handle, alloc_inode,
					       alloc_bh, bit, bg_blkno, 1);
		if (ret)
			mlog_errno(ret);
	}

out_commit:
	ocfs2_commit_trans(osb, handle);
out_unlock:
	if (alloc_inode) {
		ocfs2_inode_unlock(alloc_inode, 1);
		brelse(alloc_bh);
	}
out_mutex:
	if (alloc_inode) {
		mutex_unlock(&alloc_inode->i_mutex);
		iput(alloc_inode);
	}
out:
	ocfs2_unlock_refcount_tree(osb, ref_tree, 1);
	if (delete_tree)
		ocfs2_refcount_tree_put(ref_tree);
	brelse(blk_bh);

	return ret;
}