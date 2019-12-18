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
struct ocfs2_super {int /*<<< orphan*/  dc_task_lock; int /*<<< orphan*/  blocked_lock_count; int /*<<< orphan*/  blocked_lock_list; } ;
struct ocfs2_lock_res {int l_flags; int /*<<< orphan*/  l_blocked_list; int /*<<< orphan*/  l_name; int /*<<< orphan*/  l_lock; } ;

/* Variables and functions */
 int OCFS2_LOCK_FREEING ; 
 int /*<<< orphan*/  OCFS2_LOCK_QUEUED ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockres_or_flags (struct ocfs2_lock_res*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_exit_void () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ocfs2_schedule_blocked_lock(struct ocfs2_super *osb,
					struct ocfs2_lock_res *lockres)
{
	mlog_entry_void();

	assert_spin_locked(&lockres->l_lock);

	if (lockres->l_flags & OCFS2_LOCK_FREEING) {
		/* Do not schedule a lock for downconvert when it's on
		 * the way to destruction - any nodes wanting access
		 * to the resource will get it soon. */
		mlog(0, "Lockres %s won't be scheduled: flags 0x%lx\n",
		     lockres->l_name, lockres->l_flags);
		return;
	}

	lockres_or_flags(lockres, OCFS2_LOCK_QUEUED);

	spin_lock(&osb->dc_task_lock);
	if (list_empty(&lockres->l_blocked_list)) {
		list_add_tail(&lockres->l_blocked_list,
			      &osb->blocked_lock_list);
		osb->blocked_lock_count++;
	}
	spin_unlock(&osb->dc_task_lock);

	mlog_exit_void();
}