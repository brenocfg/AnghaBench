#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct super_block {int s_blocksize_bits; } ;
struct ocfs2_super {int dummy; } ;
struct ocfs2_mem_dqinfo {int /*<<< orphan*/  dqi_gi; struct inode* dqi_gqinode; } ;
struct inode {scalar_t__ i_size; } ;
struct TYPE_6__ {int /*<<< orphan*/  dqb_curinodes; int /*<<< orphan*/  dqb_curspace; } ;
struct dquot {int dq_type; struct super_block* dq_sb; int /*<<< orphan*/  dq_off; TYPE_1__ dq_dqb; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_9__ {int /*<<< orphan*/  dq_originodes; int /*<<< orphan*/  dq_origspace; int /*<<< orphan*/  dq_use_count; } ;
struct TYPE_8__ {int /*<<< orphan*/  ip_alloc_sem; } ;
struct TYPE_7__ {struct ocfs2_mem_dqinfo* dqi_priv; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 TYPE_5__* OCFS2_DQUOT (struct dquot*) ; 
 TYPE_4__* OCFS2_I (struct inode*) ; 
 struct ocfs2_super* OCFS2_SB (struct super_block*) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int __ocfs2_global_write_info (struct super_block*,int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ info_dirty (TYPE_2__*) ; 
 int /*<<< orphan*/  journal_current_handle () ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_calc_global_qinit_credits (struct super_block*,int) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int ocfs2_extend_no_holes (struct inode*,scalar_t__,scalar_t__) ; 
 int ocfs2_global_qinit_alloc (struct super_block*,int) ; 
 int ocfs2_qinfo_lock (struct ocfs2_mem_dqinfo*,int) ; 
 int /*<<< orphan*/  ocfs2_qinfo_unlock (struct ocfs2_mem_dqinfo*,int) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 int qtree_read_dquot (int /*<<< orphan*/ *,struct dquot*) ; 
 int qtree_write_dquot (int /*<<< orphan*/ *,struct dquot*) ; 
 TYPE_2__* sb_dqinfo (struct super_block*,int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int ocfs2_global_read_dquot(struct dquot *dquot)
{
	int err, err2, ex = 0;
	struct super_block *sb = dquot->dq_sb;
	int type = dquot->dq_type;
	struct ocfs2_mem_dqinfo *info = sb_dqinfo(sb, type)->dqi_priv;
	struct ocfs2_super *osb = OCFS2_SB(sb);
	struct inode *gqinode = info->dqi_gqinode;
	int need_alloc = ocfs2_global_qinit_alloc(sb, type);
	handle_t *handle = NULL;

	err = ocfs2_qinfo_lock(info, 0);
	if (err < 0)
		goto out;
	err = qtree_read_dquot(&info->dqi_gi, dquot);
	if (err < 0)
		goto out_qlock;
	OCFS2_DQUOT(dquot)->dq_use_count++;
	OCFS2_DQUOT(dquot)->dq_origspace = dquot->dq_dqb.dqb_curspace;
	OCFS2_DQUOT(dquot)->dq_originodes = dquot->dq_dqb.dqb_curinodes;
	ocfs2_qinfo_unlock(info, 0);

	if (!dquot->dq_off) {	/* No real quota entry? */
		ex = 1;
		/*
		 * Add blocks to quota file before we start a transaction since
		 * locking allocators ranks above a transaction start
		 */
		WARN_ON(journal_current_handle());
		down_write(&OCFS2_I(gqinode)->ip_alloc_sem);
		err = ocfs2_extend_no_holes(gqinode,
			gqinode->i_size + (need_alloc << sb->s_blocksize_bits),
			gqinode->i_size);
		up_write(&OCFS2_I(gqinode)->ip_alloc_sem);
		if (err < 0)
			goto out;
	}

	handle = ocfs2_start_trans(osb,
				   ocfs2_calc_global_qinit_credits(sb, type));
	if (IS_ERR(handle)) {
		err = PTR_ERR(handle);
		goto out;
	}
	err = ocfs2_qinfo_lock(info, ex);
	if (err < 0)
		goto out_trans;
	err = qtree_write_dquot(&info->dqi_gi, dquot);
	if (ex && info_dirty(sb_dqinfo(dquot->dq_sb, dquot->dq_type))) {
		err2 = __ocfs2_global_write_info(dquot->dq_sb, dquot->dq_type);
		if (!err)
			err = err2;
	}
out_qlock:
	if (ex)
		ocfs2_qinfo_unlock(info, 1);
	else
		ocfs2_qinfo_unlock(info, 0);
out_trans:
	if (handle)
		ocfs2_commit_trans(osb, handle);
out:
	if (err < 0)
		mlog_errno(err);
	return err;
}