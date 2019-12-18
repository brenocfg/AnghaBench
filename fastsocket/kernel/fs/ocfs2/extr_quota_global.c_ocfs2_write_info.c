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
struct ocfs2_mem_dqinfo {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {struct ocfs2_mem_dqinfo* dqi_priv; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OCFS2_QINFO_WRITE_CREDITS ; 
 int /*<<< orphan*/  OCFS2_SB (struct super_block*) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int dquot_commit_info (struct super_block*,int) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ocfs2_lock_global_qf (struct ocfs2_mem_dqinfo*,int) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_unlock_global_qf (struct ocfs2_mem_dqinfo*,int) ; 
 TYPE_1__* sb_dqinfo (struct super_block*,int) ; 

__attribute__((used)) static int ocfs2_write_info(struct super_block *sb, int type)
{
	handle_t *handle;
	int status = 0;
	struct ocfs2_mem_dqinfo *oinfo = sb_dqinfo(sb, type)->dqi_priv;

	mlog_entry_void();

	status = ocfs2_lock_global_qf(oinfo, 1);
	if (status < 0)
		goto out;
	handle = ocfs2_start_trans(OCFS2_SB(sb), OCFS2_QINFO_WRITE_CREDITS);
	if (IS_ERR(handle)) {
		status = PTR_ERR(handle);
		mlog_errno(status);
		goto out_ilock;
	}
	status = dquot_commit_info(sb, type);
	ocfs2_commit_trans(OCFS2_SB(sb), handle);
out_ilock:
	ocfs2_unlock_global_qf(oinfo, 1);
out:
	mlog_exit(status);
	return status;
}