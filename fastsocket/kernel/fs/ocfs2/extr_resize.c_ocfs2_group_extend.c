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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct ocfs2_super {int /*<<< orphan*/  sb; } ;
struct ocfs2_group_desc {int /*<<< orphan*/  bg_blkno; int /*<<< orphan*/  bg_bits; } ;
struct TYPE_3__ {int /*<<< orphan*/  cl_cpg; int /*<<< orphan*/  cl_bpc; } ;
struct TYPE_4__ {TYPE_1__ i_chain; } ;
struct ocfs2_dinode {TYPE_2__ id2; int /*<<< orphan*/  i_clusters; } ;
struct inode {int /*<<< orphan*/  i_mutex; int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int EROFS ; 
 int /*<<< orphan*/  GLOBAL_BITMAP_SYSTEM_INODE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  OCFS2_GROUP_EXTEND_CREDITS ; 
 int /*<<< orphan*/  OCFS2_INVALID_SLOT ; 
 int /*<<< orphan*/  OCFS2_IS_VALID_DINODE (struct ocfs2_dinode*) ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit_void () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 struct inode* ocfs2_get_system_file_inode (struct ocfs2_super*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_group_bitmap_size (int /*<<< orphan*/ ) ; 
 int ocfs2_inode_lock (struct inode*,struct buffer_head**,int) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 
 scalar_t__ ocfs2_is_hard_readonly (struct ocfs2_super*) ; 
 scalar_t__ ocfs2_is_soft_readonly (struct ocfs2_super*) ; 
 int ocfs2_read_group_descriptor (struct inode*,struct ocfs2_dinode*,int /*<<< orphan*/ ,struct buffer_head**) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 int ocfs2_update_last_group_and_inode (int /*<<< orphan*/ *,struct inode*,struct buffer_head*,struct buffer_head*,scalar_t__,int) ; 
 int /*<<< orphan*/  ocfs2_update_super_and_backups (struct inode*,int) ; 
 int /*<<< orphan*/  ocfs2_which_cluster_group (struct inode*,scalar_t__) ; 

int ocfs2_group_extend(struct inode * inode, int new_clusters)
{
	int ret;
	handle_t *handle;
	struct buffer_head *main_bm_bh = NULL;
	struct buffer_head *group_bh = NULL;
	struct inode *main_bm_inode = NULL;
	struct ocfs2_dinode *fe = NULL;
	struct ocfs2_group_desc *group = NULL;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	u16 cl_bpc;
	u32 first_new_cluster;
	u64 lgd_blkno;

	mlog_entry_void();

	if (ocfs2_is_hard_readonly(osb) || ocfs2_is_soft_readonly(osb))
		return -EROFS;

	if (new_clusters < 0)
		return -EINVAL;
	else if (new_clusters == 0)
		return 0;

	main_bm_inode = ocfs2_get_system_file_inode(osb,
						    GLOBAL_BITMAP_SYSTEM_INODE,
						    OCFS2_INVALID_SLOT);
	if (!main_bm_inode) {
		ret = -EINVAL;
		mlog_errno(ret);
		goto out;
	}

	mutex_lock(&main_bm_inode->i_mutex);

	ret = ocfs2_inode_lock(main_bm_inode, &main_bm_bh, 1);
	if (ret < 0) {
		mlog_errno(ret);
		goto out_mutex;
	}

	fe = (struct ocfs2_dinode *)main_bm_bh->b_data;

	/* main_bm_bh is validated by inode read inside ocfs2_inode_lock(),
	 * so any corruption is a code bug. */
	BUG_ON(!OCFS2_IS_VALID_DINODE(fe));

	if (le16_to_cpu(fe->id2.i_chain.cl_cpg) !=
				 ocfs2_group_bitmap_size(osb->sb) * 8) {
		mlog(ML_ERROR, "The disk is too old and small. "
		     "Force to do offline resize.");
		ret = -EINVAL;
		goto out_unlock;
	}

	first_new_cluster = le32_to_cpu(fe->i_clusters);
	lgd_blkno = ocfs2_which_cluster_group(main_bm_inode,
					      first_new_cluster - 1);

	ret = ocfs2_read_group_descriptor(main_bm_inode, fe, lgd_blkno,
					  &group_bh);
	if (ret < 0) {
		mlog_errno(ret);
		goto out_unlock;
	}
	group = (struct ocfs2_group_desc *)group_bh->b_data;

	cl_bpc = le16_to_cpu(fe->id2.i_chain.cl_bpc);
	if (le16_to_cpu(group->bg_bits) / cl_bpc + new_clusters >
		le16_to_cpu(fe->id2.i_chain.cl_cpg)) {
		ret = -EINVAL;
		goto out_unlock;
	}

	mlog(0, "extend the last group at %llu, new clusters = %d\n",
	     (unsigned long long)le64_to_cpu(group->bg_blkno), new_clusters);

	handle = ocfs2_start_trans(osb, OCFS2_GROUP_EXTEND_CREDITS);
	if (IS_ERR(handle)) {
		mlog_errno(PTR_ERR(handle));
		ret = -EINVAL;
		goto out_unlock;
	}

	/* update the last group descriptor and inode. */
	ret = ocfs2_update_last_group_and_inode(handle, main_bm_inode,
						main_bm_bh, group_bh,
						first_new_cluster,
						new_clusters);
	if (ret) {
		mlog_errno(ret);
		goto out_commit;
	}

	ocfs2_update_super_and_backups(main_bm_inode, new_clusters);

out_commit:
	ocfs2_commit_trans(osb, handle);
out_unlock:
	brelse(group_bh);
	brelse(main_bm_bh);

	ocfs2_inode_unlock(main_bm_inode, 1);

out_mutex:
	mutex_unlock(&main_bm_inode->i_mutex);
	iput(main_bm_inode);

out:
	mlog_exit_void();
	return ret;
}