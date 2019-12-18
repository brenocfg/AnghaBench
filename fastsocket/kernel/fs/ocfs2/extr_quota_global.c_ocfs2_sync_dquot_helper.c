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
struct super_block {int /*<<< orphan*/  s_id; } ;
struct ocfs2_super {int dummy; } ;
struct ocfs2_mem_dqinfo {int dummy; } ;
struct dquot {unsigned long dq_type; int /*<<< orphan*/  dq_id; struct super_block* dq_sb; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_4__ {struct ocfs2_mem_dqinfo* dqi_priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  dqio_mutex; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OCFS2_QSYNC_CREDITS ; 
 struct ocfs2_super* OCFS2_SB (struct super_block*) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int dquot_commit (struct dquot*) ; 
 int /*<<< orphan*/  dquot_mark_dquot_dirty (struct dquot*) ; 
 int /*<<< orphan*/  mlog_entry (char*,int /*<<< orphan*/ ,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int ocfs2_lock_global_qf (struct ocfs2_mem_dqinfo*,int) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 int ocfs2_sync_dquot (struct dquot*) ; 
 int /*<<< orphan*/  ocfs2_unlock_global_qf (struct ocfs2_mem_dqinfo*,int) ; 
 TYPE_2__* sb_dqinfo (struct super_block*,unsigned long) ; 
 TYPE_1__* sb_dqopt (struct super_block*) ; 

__attribute__((used)) static int ocfs2_sync_dquot_helper(struct dquot *dquot, unsigned long type)
{
	handle_t *handle;
	struct super_block *sb = dquot->dq_sb;
	struct ocfs2_mem_dqinfo *oinfo = sb_dqinfo(sb, type)->dqi_priv;
	struct ocfs2_super *osb = OCFS2_SB(sb);
	int status = 0;

	mlog_entry("id=%u qtype=%u type=%lu device=%s\n", dquot->dq_id,
		   dquot->dq_type, type, sb->s_id);
	if (type != dquot->dq_type)
		goto out;
	status = ocfs2_lock_global_qf(oinfo, 1);
	if (status < 0)
		goto out;

	handle = ocfs2_start_trans(osb, OCFS2_QSYNC_CREDITS);
	if (IS_ERR(handle)) {
		status = PTR_ERR(handle);
		mlog_errno(status);
		goto out_ilock;
	}
	mutex_lock(&sb_dqopt(sb)->dqio_mutex);
	status = ocfs2_sync_dquot(dquot);
	mutex_unlock(&sb_dqopt(sb)->dqio_mutex);
	if (status < 0)
		mlog_errno(status);
	/* We have to write local structure as well... */
	dquot_mark_dquot_dirty(dquot);
	status = dquot_commit(dquot);
	if (status < 0)
		mlog_errno(status);
	ocfs2_commit_trans(osb, handle);
out_ilock:
	ocfs2_unlock_global_qf(oinfo, 1);
out:
	mlog_exit(status);
	return status;
}