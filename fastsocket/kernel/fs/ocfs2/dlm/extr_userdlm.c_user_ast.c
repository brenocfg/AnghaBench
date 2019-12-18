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
struct dlm_lockstatus {scalar_t__ status; } ;
struct user_lock_res {scalar_t__ l_requested; scalar_t__ l_level; int /*<<< orphan*/  l_event; int /*<<< orphan*/  l_lock; int /*<<< orphan*/  l_flags; int /*<<< orphan*/  l_blocking; int /*<<< orphan*/  l_name; int /*<<< orphan*/  l_namelen; struct dlm_lockstatus l_lksb; } ;

/* Variables and functions */
 scalar_t__ DLM_NORMAL ; 
 scalar_t__ LKM_IVMODE ; 
 int /*<<< orphan*/  LKM_NLMODE ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  USER_LOCK_ATTACHED ; 
 int /*<<< orphan*/  USER_LOCK_BLOCKED ; 
 int /*<<< orphan*/  USER_LOCK_BUSY ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  mlog_bug_on_msg (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ user_highest_compat_lock_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void user_ast(void *opaque)
{
	struct user_lock_res *lockres = opaque;
	struct dlm_lockstatus *lksb;

	mlog(0, "AST fired for lockres %.*s\n", lockres->l_namelen,
	     lockres->l_name);

	spin_lock(&lockres->l_lock);

	lksb = &(lockres->l_lksb);
	if (lksb->status != DLM_NORMAL) {
		mlog(ML_ERROR, "lksb status value of %u on lockres %.*s\n",
		     lksb->status, lockres->l_namelen, lockres->l_name);
		spin_unlock(&lockres->l_lock);
		return;
	}

	mlog_bug_on_msg(lockres->l_requested == LKM_IVMODE,
			"Lockres %.*s, requested ivmode. flags 0x%x\n",
			lockres->l_namelen, lockres->l_name, lockres->l_flags);

	/* we're downconverting. */
	if (lockres->l_requested < lockres->l_level) {
		if (lockres->l_requested <=
		    user_highest_compat_lock_level(lockres->l_blocking)) {
			lockres->l_blocking = LKM_NLMODE;
			lockres->l_flags &= ~USER_LOCK_BLOCKED;
		}
	}

	lockres->l_level = lockres->l_requested;
	lockres->l_requested = LKM_IVMODE;
	lockres->l_flags |= USER_LOCK_ATTACHED;
	lockres->l_flags &= ~USER_LOCK_BUSY;

	spin_unlock(&lockres->l_lock);

	wake_up(&lockres->l_event);
}