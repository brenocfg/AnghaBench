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
struct ocfs2_lock_res {int l_flags; int /*<<< orphan*/  l_lksb; int /*<<< orphan*/  l_ex_holders; int /*<<< orphan*/  l_name; int /*<<< orphan*/  l_ro_holders; int /*<<< orphan*/  l_lock; int /*<<< orphan*/  l_mask_waiters; int /*<<< orphan*/  l_blocked_list; } ;

/* Variables and functions */
 int OCFS2_LOCK_INITIALIZED ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog_bug_on_msg (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_exit_void () ; 
 int /*<<< orphan*/  ocfs2_remove_lockres_tracking (struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  spin_is_locked (int /*<<< orphan*/ *) ; 

void ocfs2_lock_res_free(struct ocfs2_lock_res *res)
{
	mlog_entry_void();

	if (!(res->l_flags & OCFS2_LOCK_INITIALIZED))
		return;

	ocfs2_remove_lockres_tracking(res);

	mlog_bug_on_msg(!list_empty(&res->l_blocked_list),
			"Lockres %s is on the blocked list\n",
			res->l_name);
	mlog_bug_on_msg(!list_empty(&res->l_mask_waiters),
			"Lockres %s has mask waiters pending\n",
			res->l_name);
	mlog_bug_on_msg(spin_is_locked(&res->l_lock),
			"Lockres %s is locked\n",
			res->l_name);
	mlog_bug_on_msg(res->l_ro_holders,
			"Lockres %s has %u ro holders\n",
			res->l_name, res->l_ro_holders);
	mlog_bug_on_msg(res->l_ex_holders,
			"Lockres %s has %u ex holders\n",
			res->l_name, res->l_ex_holders);

	/* Need to clear out the lock status block for the dlm */
	memset(&res->l_lksb, 0, sizeof(res->l_lksb));

	res->l_flags = 0UL;
	mlog_exit_void();
}