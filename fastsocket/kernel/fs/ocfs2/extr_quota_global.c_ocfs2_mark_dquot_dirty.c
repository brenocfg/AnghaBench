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
struct super_block {int dummy; } ;
struct ocfs2_super {int dummy; } ;
struct ocfs2_mem_dqinfo {int dummy; } ;
struct dquot {int dq_type; unsigned long dq_flags; int /*<<< orphan*/  dq_id; struct super_block* dq_sb; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {struct ocfs2_mem_dqinfo* dqi_priv; } ;

/* Variables and functions */
 int DQ_LASTSET_B ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OCFS2_QSYNC_CREDITS ; 
 struct ocfs2_super* OCFS2_SB (struct super_block*) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int QIF_BLIMITS_B ; 
 int QIF_BTIME_B ; 
 int QIF_ILIMITS_B ; 
 int QIF_INODES_B ; 
 int QIF_ITIME_B ; 
 int QIF_SPACE_B ; 
 int /*<<< orphan*/  dq_data_lock ; 
 int dquot_commit (struct dquot*) ; 
 int /*<<< orphan*/  dquot_mark_dquot_dirty (struct dquot*) ; 
 scalar_t__ journal_current_handle () ; 
 int /*<<< orphan*/  mlog_entry (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int ocfs2_lock_global_qf (struct ocfs2_mem_dqinfo*,int) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 int ocfs2_sync_dquot (struct dquot*) ; 
 int /*<<< orphan*/  ocfs2_unlock_global_qf (struct ocfs2_mem_dqinfo*,int) ; 
 int ocfs2_write_dquot (struct dquot*) ; 
 TYPE_1__* sb_dqinfo (struct super_block*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_mark_dquot_dirty(struct dquot *dquot)
{
	unsigned long mask = (1 << (DQ_LASTSET_B + QIF_ILIMITS_B)) |
			     (1 << (DQ_LASTSET_B + QIF_BLIMITS_B)) |
			     (1 << (DQ_LASTSET_B + QIF_INODES_B)) |
			     (1 << (DQ_LASTSET_B + QIF_SPACE_B)) |
			     (1 << (DQ_LASTSET_B + QIF_BTIME_B)) |
			     (1 << (DQ_LASTSET_B + QIF_ITIME_B));
	int sync = 0;
	int status;
	struct super_block *sb = dquot->dq_sb;
	int type = dquot->dq_type;
	struct ocfs2_mem_dqinfo *oinfo = sb_dqinfo(sb, type)->dqi_priv;
	handle_t *handle;
	struct ocfs2_super *osb = OCFS2_SB(sb);

	mlog_entry("id=%u, type=%d", dquot->dq_id, type);
	dquot_mark_dquot_dirty(dquot);

	/* In case user set some limits, sync dquot immediately to global
	 * quota file so that information propagates quicker */
	spin_lock(&dq_data_lock);
	if (dquot->dq_flags & mask)
		sync = 1;
	spin_unlock(&dq_data_lock);
	/* This is a slight hack but we can't afford getting global quota
	 * lock if we already have a transaction started. */
	if (!sync || journal_current_handle()) {
		status = ocfs2_write_dquot(dquot);
		goto out;
	}
	status = ocfs2_lock_global_qf(oinfo, 1);
	if (status < 0)
		goto out;
	handle = ocfs2_start_trans(osb, OCFS2_QSYNC_CREDITS);
	if (IS_ERR(handle)) {
		status = PTR_ERR(handle);
		mlog_errno(status);
		goto out_ilock;
	}
	status = ocfs2_sync_dquot(dquot);
	if (status < 0) {
		mlog_errno(status);
		goto out_trans;
	}
	/* Now write updated local dquot structure */
	status = dquot_commit(dquot);
out_trans:
	ocfs2_commit_trans(osb, handle);
out_ilock:
	ocfs2_unlock_global_qf(oinfo, 1);
out:
	mlog_exit(status);
	return status;
}