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
struct ocfs2_lock_res {int l_unlock_action; int l_flags; int /*<<< orphan*/  l_lock; int /*<<< orphan*/  l_event; int /*<<< orphan*/  l_level; int /*<<< orphan*/  l_action; int /*<<< orphan*/  l_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DLM_LOCK_IV ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  OCFS2_AST_INVALID ; 
 int OCFS2_LOCK_BLOCKED ; 
 int /*<<< orphan*/  OCFS2_LOCK_BUSY ; 
#define  OCFS2_UNLOCK_CANCEL_CONVERT 129 
#define  OCFS2_UNLOCK_DROP_LOCK 128 
 int OCFS2_UNLOCK_INVALID ; 
 int /*<<< orphan*/  lockres_clear_flags (struct ocfs2_lock_res*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_exit_void () ; 
 int /*<<< orphan*/  ocfs2_get_lockres_osb (struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  ocfs2_wake_downconvert_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ocfs2_unlock_ast(void *opaque, int error)
{
	struct ocfs2_lock_res *lockres = opaque;
	unsigned long flags;

	mlog_entry_void();

	mlog(0, "UNLOCK AST called on lock %s, action = %d\n", lockres->l_name,
	     lockres->l_unlock_action);

	spin_lock_irqsave(&lockres->l_lock, flags);
	if (error) {
		mlog(ML_ERROR, "Dlm passes error %d for lock %s, "
		     "unlock_action %d\n", error, lockres->l_name,
		     lockres->l_unlock_action);
		spin_unlock_irqrestore(&lockres->l_lock, flags);
		mlog_exit_void();
		return;
	}

	switch(lockres->l_unlock_action) {
	case OCFS2_UNLOCK_CANCEL_CONVERT:
		mlog(0, "Cancel convert success for %s\n", lockres->l_name);
		lockres->l_action = OCFS2_AST_INVALID;
		/* Downconvert thread may have requeued this lock, we
		 * need to wake it. */
		if (lockres->l_flags & OCFS2_LOCK_BLOCKED)
			ocfs2_wake_downconvert_thread(ocfs2_get_lockres_osb(lockres));
		break;
	case OCFS2_UNLOCK_DROP_LOCK:
		lockres->l_level = DLM_LOCK_IV;
		break;
	default:
		BUG();
	}

	lockres_clear_flags(lockres, OCFS2_LOCK_BUSY);
	lockres->l_unlock_action = OCFS2_UNLOCK_INVALID;
	wake_up(&lockres->l_event);
	spin_unlock_irqrestore(&lockres->l_lock, flags);

	mlog_exit_void();
}