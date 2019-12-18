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
struct user_lock_res {int l_flags; int l_level; int l_requested; int /*<<< orphan*/  l_lock; int /*<<< orphan*/  l_namelen; int /*<<< orphan*/  l_name; int /*<<< orphan*/  l_lksb; } ;
struct dlm_ctxt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DLM_NORMAL ; 
 int DLM_NOTQUEUED ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ERESTARTSYS ; 
 int LKM_CONVERT ; 
 int LKM_EXMODE ; 
 int LKM_IVMODE ; 
 int LKM_NLMODE ; 
 int LKM_NOQUEUE ; 
 int LKM_PRMODE ; 
 int LKM_VALBLK ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int USER_LOCK_BLOCKED ; 
 int USER_LOCK_BUSY ; 
 int /*<<< orphan*/  current ; 
 struct dlm_ctxt* dlm_ctxt_from_user_lockres (struct user_lock_res*) ; 
 int dlmlock (struct dlm_ctxt*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct user_lock_res*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_ast ; 
 int /*<<< orphan*/  user_bast ; 
 int /*<<< orphan*/  user_dlm_inc_holders (struct user_lock_res*,int) ; 
 int /*<<< orphan*/  user_log_dlm_error (char*,int,struct user_lock_res*) ; 
 int /*<<< orphan*/  user_may_continue_on_blocked_lock (struct user_lock_res*,int) ; 
 int /*<<< orphan*/  user_recover_from_dlm_error (struct user_lock_res*) ; 
 int /*<<< orphan*/  user_wait_on_blocked_lock (struct user_lock_res*) ; 
 int /*<<< orphan*/  user_wait_on_busy_lock (struct user_lock_res*) ; 

int user_dlm_cluster_lock(struct user_lock_res *lockres,
			  int level,
			  int lkm_flags)
{
	int status, local_flags;
	struct dlm_ctxt *dlm = dlm_ctxt_from_user_lockres(lockres);

	if (level != LKM_EXMODE &&
	    level != LKM_PRMODE) {
		mlog(ML_ERROR, "lockres %.*s: invalid request!\n",
		     lockres->l_namelen, lockres->l_name);
		status = -EINVAL;
		goto bail;
	}

	mlog(0, "lockres %.*s: asking for %s lock, passed flags = 0x%x\n",
	     lockres->l_namelen, lockres->l_name,
	     (level == LKM_EXMODE) ? "LKM_EXMODE" : "LKM_PRMODE",
	     lkm_flags);

again:
	if (signal_pending(current)) {
		status = -ERESTARTSYS;
		goto bail;
	}

	spin_lock(&lockres->l_lock);

	/* We only compare against the currently granted level
	 * here. If the lock is blocked waiting on a downconvert,
	 * we'll get caught below. */
	if ((lockres->l_flags & USER_LOCK_BUSY) &&
	    (level > lockres->l_level)) {
		/* is someone sitting in dlm_lock? If so, wait on
		 * them. */
		spin_unlock(&lockres->l_lock);

		user_wait_on_busy_lock(lockres);
		goto again;
	}

	if ((lockres->l_flags & USER_LOCK_BLOCKED) &&
	    (!user_may_continue_on_blocked_lock(lockres, level))) {
		/* is the lock is currently blocked on behalf of
		 * another node */
		spin_unlock(&lockres->l_lock);

		user_wait_on_blocked_lock(lockres);
		goto again;
	}

	if (level > lockres->l_level) {
		local_flags = lkm_flags | LKM_VALBLK;
		if (lockres->l_level != LKM_IVMODE)
			local_flags |= LKM_CONVERT;

		lockres->l_requested = level;
		lockres->l_flags |= USER_LOCK_BUSY;
		spin_unlock(&lockres->l_lock);

		BUG_ON(level == LKM_IVMODE);
		BUG_ON(level == LKM_NLMODE);

		/* call dlm_lock to upgrade lock now */
		status = dlmlock(dlm,
				 level,
				 &lockres->l_lksb,
				 local_flags,
				 lockres->l_name,
				 lockres->l_namelen,
				 user_ast,
				 lockres,
				 user_bast);
		if (status != DLM_NORMAL) {
			if ((lkm_flags & LKM_NOQUEUE) &&
			    (status == DLM_NOTQUEUED))
				status = -EAGAIN;
			else {
				user_log_dlm_error("dlmlock", status, lockres);
				status = -EINVAL;
			}
			user_recover_from_dlm_error(lockres);
			goto bail;
		}

		user_wait_on_busy_lock(lockres);
		goto again;
	}

	user_dlm_inc_holders(lockres, level);
	spin_unlock(&lockres->l_lock);

	status = 0;
bail:
	return status;
}