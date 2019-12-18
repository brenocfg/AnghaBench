#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct ocfs2_super {int s_clustersize_bits; int /*<<< orphan*/  sb; } ;
struct ocfs2_new_group_input {size_t chain; int clusters; int frees; scalar_t__ group; } ;
struct ocfs2_group_desc {int /*<<< orphan*/  bg_next_group; } ;
struct TYPE_6__ {int /*<<< orphan*/  i_used; int /*<<< orphan*/  i_total; } ;
struct TYPE_7__ {TYPE_2__ bitmap1; } ;
struct ocfs2_chain_list {int /*<<< orphan*/  cl_next_free_rec; struct ocfs2_chain_rec* cl_recs; int /*<<< orphan*/  cl_bpc; int /*<<< orphan*/  cl_cpg; } ;
struct TYPE_5__ {struct ocfs2_chain_list i_chain; } ;
struct ocfs2_dinode {int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_clusters; TYPE_3__ id1; TYPE_1__ id2; } ;
struct ocfs2_chain_rec {int /*<<< orphan*/  c_free; int /*<<< orphan*/  c_total; int /*<<< orphan*/  c_blkno; } ;
struct inode {int /*<<< orphan*/  i_mutex; int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_8__ {int /*<<< orphan*/  ip_lock; int /*<<< orphan*/  ip_clusters; } ;

/* Variables and functions */
 int EINVAL ; 
 int EROFS ; 
 int /*<<< orphan*/  GLOBAL_BITMAP_SYSTEM_INODE ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  OCFS2_GROUP_ADD_CREDITS ; 
 TYPE_4__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_INVALID_SLOT ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  cpu_to_le64 (scalar_t__) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_add_cpu (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ocfs2_chain_rec*,int /*<<< orphan*/ ,int) ; 
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
 int ocfs2_journal_access_di (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_access_gd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int ocfs2_read_blocks_sync (struct ocfs2_super*,scalar_t__,int,struct buffer_head**) ; 
 int /*<<< orphan*/  ocfs2_set_new_buffer_uptodate (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_update_super_and_backups (struct inode*,int) ; 
 int ocfs2_verify_group_and_input (struct inode*,struct ocfs2_dinode*,struct ocfs2_new_group_input*,struct buffer_head*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int ocfs2_group_add(struct inode *inode, struct ocfs2_new_group_input *input)
{
	int ret;
	handle_t *handle;
	struct buffer_head *main_bm_bh = NULL;
	struct inode *main_bm_inode = NULL;
	struct ocfs2_dinode *fe = NULL;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	struct buffer_head *group_bh = NULL;
	struct ocfs2_group_desc *group = NULL;
	struct ocfs2_chain_list *cl;
	struct ocfs2_chain_rec *cr;
	u16 cl_bpc;

	mlog_entry_void();

	if (ocfs2_is_hard_readonly(osb) || ocfs2_is_soft_readonly(osb))
		return -EROFS;

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

	if (le16_to_cpu(fe->id2.i_chain.cl_cpg) !=
				 ocfs2_group_bitmap_size(osb->sb) * 8) {
		mlog(ML_ERROR, "The disk is too old and small."
		     " Force to do offline resize.");
		ret = -EINVAL;
		goto out_unlock;
	}

	ret = ocfs2_read_blocks_sync(osb, input->group, 1, &group_bh);
	if (ret < 0) {
		mlog(ML_ERROR, "Can't read the group descriptor # %llu "
		     "from the device.", (unsigned long long)input->group);
		goto out_unlock;
	}

	ocfs2_set_new_buffer_uptodate(INODE_CACHE(inode), group_bh);

	ret = ocfs2_verify_group_and_input(main_bm_inode, fe, input, group_bh);
	if (ret) {
		mlog_errno(ret);
		goto out_unlock;
	}

	mlog(0, "Add a new group  %llu in chain = %u, length = %u\n",
	     (unsigned long long)input->group, input->chain, input->clusters);

	handle = ocfs2_start_trans(osb, OCFS2_GROUP_ADD_CREDITS);
	if (IS_ERR(handle)) {
		mlog_errno(PTR_ERR(handle));
		ret = -EINVAL;
		goto out_unlock;
	}

	cl_bpc = le16_to_cpu(fe->id2.i_chain.cl_bpc);
	cl = &fe->id2.i_chain;
	cr = &cl->cl_recs[input->chain];

	ret = ocfs2_journal_access_gd(handle, INODE_CACHE(main_bm_inode),
				      group_bh, OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret < 0) {
		mlog_errno(ret);
		goto out_commit;
	}

	group = (struct ocfs2_group_desc *)group_bh->b_data;
	group->bg_next_group = cr->c_blkno;

	ret = ocfs2_journal_dirty(handle, group_bh);
	if (ret < 0) {
		mlog_errno(ret);
		goto out_commit;
	}

	ret = ocfs2_journal_access_di(handle, INODE_CACHE(main_bm_inode),
				      main_bm_bh, OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret < 0) {
		mlog_errno(ret);
		goto out_commit;
	}

	if (input->chain == le16_to_cpu(cl->cl_next_free_rec)) {
		le16_add_cpu(&cl->cl_next_free_rec, 1);
		memset(cr, 0, sizeof(struct ocfs2_chain_rec));
	}

	cr->c_blkno = cpu_to_le64(input->group);
	le32_add_cpu(&cr->c_total, input->clusters * cl_bpc);
	le32_add_cpu(&cr->c_free, input->frees * cl_bpc);

	le32_add_cpu(&fe->id1.bitmap1.i_total, input->clusters *cl_bpc);
	le32_add_cpu(&fe->id1.bitmap1.i_used,
		     (input->clusters - input->frees) * cl_bpc);
	le32_add_cpu(&fe->i_clusters, input->clusters);

	ocfs2_journal_dirty(handle, main_bm_bh);

	spin_lock(&OCFS2_I(main_bm_inode)->ip_lock);
	OCFS2_I(main_bm_inode)->ip_clusters = le32_to_cpu(fe->i_clusters);
	le64_add_cpu(&fe->i_size, input->clusters << osb->s_clustersize_bits);
	spin_unlock(&OCFS2_I(main_bm_inode)->ip_lock);
	i_size_write(main_bm_inode, le64_to_cpu(fe->i_size));

	ocfs2_update_super_and_backups(main_bm_inode, input->clusters);

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