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
struct ocfs2_super {int /*<<< orphan*/  recovery_event; int /*<<< orphan*/  recovery_lock; int /*<<< orphan*/ * recovery_thread_task; scalar_t__ disable_recovery; int /*<<< orphan*/  node_num; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __ocfs2_recovery_thread ; 
 int /*<<< orphan*/ * kthread_run (int /*<<< orphan*/ ,struct ocfs2_super*,char*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mlog_entry (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit_void () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ ocfs2_recovery_map_set (struct ocfs2_super*,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void ocfs2_recovery_thread(struct ocfs2_super *osb, int node_num)
{
	mlog_entry("(node_num=%d, osb->node_num = %d)\n",
		   node_num, osb->node_num);

	mutex_lock(&osb->recovery_lock);
	if (osb->disable_recovery)
		goto out;

	/* People waiting on recovery will wait on
	 * the recovery map to empty. */
	if (ocfs2_recovery_map_set(osb, node_num))
		mlog(0, "node %d already in recovery map.\n", node_num);

	mlog(0, "starting recovery thread...\n");

	if (osb->recovery_thread_task)
		goto out;

	osb->recovery_thread_task =  kthread_run(__ocfs2_recovery_thread, osb,
						 "ocfs2rec");
	if (IS_ERR(osb->recovery_thread_task)) {
		mlog_errno((int)PTR_ERR(osb->recovery_thread_task));
		osb->recovery_thread_task = NULL;
	}

out:
	mutex_unlock(&osb->recovery_lock);
	wake_up(&osb->recovery_event);

	mlog_exit_void();
}