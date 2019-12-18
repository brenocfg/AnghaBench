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
struct ocfs2_super {int /*<<< orphan*/  cconn; } ;
struct ocfs2_lock_res {int /*<<< orphan*/  l_name; int /*<<< orphan*/  l_lksb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_LKF_CANCEL ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int ocfs2_dlm_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  ocfs2_log_dlm_error (char*,int,struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  ocfs2_recover_from_dlm_error (struct ocfs2_lock_res*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_cancel_convert(struct ocfs2_super *osb,
				struct ocfs2_lock_res *lockres)
{
	int ret;

	mlog_entry_void();
	mlog(0, "lock %s\n", lockres->l_name);

	ret = ocfs2_dlm_unlock(osb->cconn, &lockres->l_lksb,
			       DLM_LKF_CANCEL, lockres);
	if (ret) {
		ocfs2_log_dlm_error("ocfs2_dlm_unlock", ret, lockres);
		ocfs2_recover_from_dlm_error(lockres, 0);
	}

	mlog(0, "lock %s return from ocfs2_dlm_unlock\n", lockres->l_name);

	mlog_exit(ret);
	return ret;
}