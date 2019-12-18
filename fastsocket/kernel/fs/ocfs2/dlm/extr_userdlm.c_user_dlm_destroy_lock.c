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
struct user_lock_res {int l_flags; int /*<<< orphan*/  l_lksb; int /*<<< orphan*/  l_lock; scalar_t__ l_ex_holders; scalar_t__ l_ro_holders; int /*<<< orphan*/  l_name; int /*<<< orphan*/  l_namelen; } ;
struct dlm_ctxt {int dummy; } ;

/* Variables and functions */
 int DLM_NORMAL ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  LKM_VALBLK ; 
 int USER_LOCK_ATTACHED ; 
 int USER_LOCK_BUSY ; 
 int USER_LOCK_IN_TEARDOWN ; 
 struct dlm_ctxt* dlm_ctxt_from_user_lockres (struct user_lock_res*) ; 
 int dlmunlock (struct dlm_ctxt*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct user_lock_res*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_log_dlm_error (char*,int,struct user_lock_res*) ; 
 int /*<<< orphan*/  user_unlock_ast ; 
 int /*<<< orphan*/  user_wait_on_busy_lock (struct user_lock_res*) ; 

int user_dlm_destroy_lock(struct user_lock_res *lockres)
{
	int status = -EBUSY;
	struct dlm_ctxt *dlm = dlm_ctxt_from_user_lockres(lockres);

	mlog(0, "asked to destroy %.*s\n", lockres->l_namelen, lockres->l_name);

	spin_lock(&lockres->l_lock);
	if (lockres->l_flags & USER_LOCK_IN_TEARDOWN) {
		spin_unlock(&lockres->l_lock);
		return 0;
	}

	lockres->l_flags |= USER_LOCK_IN_TEARDOWN;

	while (lockres->l_flags & USER_LOCK_BUSY) {
		spin_unlock(&lockres->l_lock);

		user_wait_on_busy_lock(lockres);

		spin_lock(&lockres->l_lock);
	}

	if (lockres->l_ro_holders || lockres->l_ex_holders) {
		spin_unlock(&lockres->l_lock);
		goto bail;
	}

	status = 0;
	if (!(lockres->l_flags & USER_LOCK_ATTACHED)) {
		spin_unlock(&lockres->l_lock);
		goto bail;
	}

	lockres->l_flags &= ~USER_LOCK_ATTACHED;
	lockres->l_flags |= USER_LOCK_BUSY;
	spin_unlock(&lockres->l_lock);

	status = dlmunlock(dlm,
			   &lockres->l_lksb,
			   LKM_VALBLK,
			   user_unlock_ast,
			   lockres);
	if (status != DLM_NORMAL) {
		user_log_dlm_error("dlmunlock", status, lockres);
		status = -EINVAL;
		goto bail;
	}

	user_wait_on_busy_lock(lockres);

	status = 0;
bail:
	return status;
}