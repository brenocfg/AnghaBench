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
struct ocfs2_super {int dummy; } ;
struct ocfs2_mem_dqinfo {int dummy; } ;
struct dquot {int /*<<< orphan*/  dq_type; int /*<<< orphan*/  dq_sb; int /*<<< orphan*/  dq_id; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {struct ocfs2_mem_dqinfo* dqi_priv; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int dquot_release (struct dquot*) ; 
 int /*<<< orphan*/  mlog_entry (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int /*<<< orphan*/  ocfs2_calc_qdel_credits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int ocfs2_lock_global_qf (struct ocfs2_mem_dqinfo*,int) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_unlock_global_qf (struct ocfs2_mem_dqinfo*,int) ; 
 TYPE_1__* sb_dqinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_release_dquot(struct dquot *dquot)
{
	handle_t *handle;
	struct ocfs2_mem_dqinfo *oinfo =
			sb_dqinfo(dquot->dq_sb, dquot->dq_type)->dqi_priv;
	struct ocfs2_super *osb = OCFS2_SB(dquot->dq_sb);
	int status = 0;

	mlog_entry("id=%u, type=%d", dquot->dq_id, dquot->dq_type);

	status = ocfs2_lock_global_qf(oinfo, 1);
	if (status < 0)
		goto out;
	handle = ocfs2_start_trans(osb,
		ocfs2_calc_qdel_credits(dquot->dq_sb, dquot->dq_type));
	if (IS_ERR(handle)) {
		status = PTR_ERR(handle);
		mlog_errno(status);
		goto out_ilock;
	}
	status = dquot_release(dquot);
	ocfs2_commit_trans(osb, handle);
out_ilock:
	ocfs2_unlock_global_qf(oinfo, 1);
out:
	mlog_exit(status);
	return status;
}