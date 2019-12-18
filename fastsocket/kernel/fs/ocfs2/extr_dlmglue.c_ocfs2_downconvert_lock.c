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
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_super {int /*<<< orphan*/  cconn; } ;
struct ocfs2_lock_res {int /*<<< orphan*/  l_name; int /*<<< orphan*/  l_lksb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_LKF_CONVERT ; 
 int /*<<< orphan*/  DLM_LKF_VALBLK ; 
 scalar_t__ OCFS2_LOCK_ID_MAX_LEN ; 
 int /*<<< orphan*/  lockres_clear_pending (struct ocfs2_lock_res*,unsigned int,struct ocfs2_super*) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int ocfs2_dlm_lock (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  ocfs2_log_dlm_error (char*,int,struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  ocfs2_recover_from_dlm_error (struct ocfs2_lock_res*,int) ; 

__attribute__((used)) static int ocfs2_downconvert_lock(struct ocfs2_super *osb,
				  struct ocfs2_lock_res *lockres,
				  int new_level,
				  int lvb,
				  unsigned int generation)
{
	int ret;
	u32 dlm_flags = DLM_LKF_CONVERT;

	mlog_entry_void();

	if (lvb)
		dlm_flags |= DLM_LKF_VALBLK;

	ret = ocfs2_dlm_lock(osb->cconn,
			     new_level,
			     &lockres->l_lksb,
			     dlm_flags,
			     lockres->l_name,
			     OCFS2_LOCK_ID_MAX_LEN - 1,
			     lockres);
	lockres_clear_pending(lockres, generation, osb);
	if (ret) {
		ocfs2_log_dlm_error("ocfs2_dlm_lock", ret, lockres);
		ocfs2_recover_from_dlm_error(lockres, 1);
		goto bail;
	}

	ret = 0;
bail:
	mlog_exit(ret);
	return ret;
}