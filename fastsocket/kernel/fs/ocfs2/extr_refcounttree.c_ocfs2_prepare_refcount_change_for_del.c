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
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_refcount_tree {int /*<<< orphan*/  rf_ci; } ;
struct ocfs2_inode_info {int ip_dyn_features; } ;
struct ocfs2_dinode {int /*<<< orphan*/  i_refcount_loc; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_ino; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EROFS ; 
 int OCFS2_HAS_REFCOUNT_FL ; 
 struct ocfs2_inode_info* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_blocks_to_clusters (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_calc_refcount_meta_credits (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct buffer_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  ocfs2_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int ocfs2_get_refcount_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocfs2_refcount_tree**) ; 
 int ocfs2_read_refcount_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head**) ; 
 int /*<<< orphan*/  ocfs2_refcount_tree (int /*<<< orphan*/ ) ; 
 int ocfs2_reserve_new_metadata_blocks (int /*<<< orphan*/ ,int,struct ocfs2_alloc_context**) ; 

int ocfs2_prepare_refcount_change_for_del(struct inode *inode,
					  struct buffer_head *di_bh,
					  u64 phys_blkno,
					  u32 clusters,
					  int *credits,
					  struct ocfs2_alloc_context **meta_ac)
{
	int ret, ref_blocks = 0;
	struct ocfs2_dinode *di = (struct ocfs2_dinode *)di_bh->b_data;
	struct ocfs2_inode_info *oi = OCFS2_I(inode);
	struct buffer_head *ref_root_bh = NULL;
	struct ocfs2_refcount_tree *tree;
	u64 start_cpos = ocfs2_blocks_to_clusters(inode->i_sb, phys_blkno);

	if (!ocfs2_refcount_tree(OCFS2_SB(inode->i_sb))) {
		ocfs2_error(inode->i_sb, "Inode %lu want to use refcount "
			    "tree, but the feature bit is not set in the "
			    "super block.", inode->i_ino);
		ret = -EROFS;
		goto out;
	}

	BUG_ON(!(oi->ip_dyn_features & OCFS2_HAS_REFCOUNT_FL));

	ret = ocfs2_get_refcount_tree(OCFS2_SB(inode->i_sb),
				      le64_to_cpu(di->i_refcount_loc), &tree);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_read_refcount_block(&tree->rf_ci,
					le64_to_cpu(di->i_refcount_loc),
					&ref_root_bh);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_calc_refcount_meta_credits(inode->i_sb,
					       &tree->rf_ci,
					       ref_root_bh,
					       start_cpos, clusters,
					       &ref_blocks, credits);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	mlog(0, "reserve new metadata %d, credits = %d\n",
	     ref_blocks, *credits);

	if (ref_blocks) {
		ret = ocfs2_reserve_new_metadata_blocks(OCFS2_SB(inode->i_sb),
							ref_blocks, meta_ac);
		if (ret)
			mlog_errno(ret);
	}

out:
	brelse(ref_root_bh);
	return ret;
}