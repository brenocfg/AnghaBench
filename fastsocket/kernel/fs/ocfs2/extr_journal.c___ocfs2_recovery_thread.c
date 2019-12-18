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
struct ocfs2_super {int max_slots; int slot_num; int /*<<< orphan*/  recovery_lock; int /*<<< orphan*/  recovery_event; int /*<<< orphan*/ * recovery_thread_task; int /*<<< orphan*/  journal; int /*<<< orphan*/  osb_lock; TYPE_1__* sb; struct ocfs2_recovery_map* recovery_map; } ;
struct ocfs2_recovery_map {int* rm_entries; scalar_t__ rm_used; } ;
struct ocfs2_quota_recovery {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_dev; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int EROFS ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct ocfs2_quota_recovery*) ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int PTR_ERR (struct ocfs2_quota_recovery*) ; 
 int /*<<< orphan*/  complete_and_exit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ocfs2_quota_recovery* ocfs2_begin_quota_recovery (struct ocfs2_super*,int) ; 
 int ocfs2_check_journals_nolocks (struct ocfs2_super*) ; 
 int ocfs2_compute_replay_slots (struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_free_replay_slots (struct ocfs2_super*) ; 
 int ocfs2_node_num_to_slot (struct ocfs2_super*,int) ; 
 int /*<<< orphan*/  ocfs2_queue_recovery_completion (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ocfs2_quota_recovery*) ; 
 int /*<<< orphan*/  ocfs2_queue_replay_slots (struct ocfs2_super*) ; 
 int ocfs2_recover_node (struct ocfs2_super*,int,int) ; 
 int /*<<< orphan*/  ocfs2_recovery_completed (struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_recovery_map_clear (struct ocfs2_super*,int) ; 
 int ocfs2_super_lock (struct ocfs2_super*,int) ; 
 int /*<<< orphan*/  ocfs2_super_unlock (struct ocfs2_super*,int) ; 
 int ocfs2_wait_on_mount (struct ocfs2_super*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __ocfs2_recovery_thread(void *arg)
{
	int status, node_num, slot_num;
	struct ocfs2_super *osb = arg;
	struct ocfs2_recovery_map *rm = osb->recovery_map;
	int *rm_quota = NULL;
	int rm_quota_used = 0, i;
	struct ocfs2_quota_recovery *qrec;

	mlog_entry_void();

	status = ocfs2_wait_on_mount(osb);
	if (status < 0) {
		goto bail;
	}

	rm_quota = kzalloc(osb->max_slots * sizeof(int), GFP_NOFS);
	if (!rm_quota) {
		status = -ENOMEM;
		goto bail;
	}
restart:
	status = ocfs2_super_lock(osb, 1);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	status = ocfs2_compute_replay_slots(osb);
	if (status < 0)
		mlog_errno(status);

	/* queue recovery for our own slot */
	ocfs2_queue_recovery_completion(osb->journal, osb->slot_num, NULL,
					NULL, NULL);

	spin_lock(&osb->osb_lock);
	while (rm->rm_used) {
		/* It's always safe to remove entry zero, as we won't
		 * clear it until ocfs2_recover_node() has succeeded. */
		node_num = rm->rm_entries[0];
		spin_unlock(&osb->osb_lock);
		mlog(0, "checking node %d\n", node_num);
		slot_num = ocfs2_node_num_to_slot(osb, node_num);
		if (slot_num == -ENOENT) {
			status = 0;
			mlog(0, "no slot for this node, so no recovery"
			     "required.\n");
			goto skip_recovery;
		}
		mlog(0, "node %d was using slot %d\n", node_num, slot_num);

		/* It is a bit subtle with quota recovery. We cannot do it
		 * immediately because we have to obtain cluster locks from
		 * quota files and we also don't want to just skip it because
		 * then quota usage would be out of sync until some node takes
		 * the slot. So we remember which nodes need quota recovery
		 * and when everything else is done, we recover quotas. */
		for (i = 0; i < rm_quota_used && rm_quota[i] != slot_num; i++);
		if (i == rm_quota_used)
			rm_quota[rm_quota_used++] = slot_num;

		status = ocfs2_recover_node(osb, node_num, slot_num);
skip_recovery:
		if (!status) {
			ocfs2_recovery_map_clear(osb, node_num);
		} else {
			mlog(ML_ERROR,
			     "Error %d recovering node %d on device (%u,%u)!\n",
			     status, node_num,
			     MAJOR(osb->sb->s_dev), MINOR(osb->sb->s_dev));
			mlog(ML_ERROR, "Volume requires unmount.\n");
		}

		spin_lock(&osb->osb_lock);
	}
	spin_unlock(&osb->osb_lock);
	mlog(0, "All nodes recovered\n");

	/* Refresh all journal recovery generations from disk */
	status = ocfs2_check_journals_nolocks(osb);
	status = (status == -EROFS) ? 0 : status;
	if (status < 0)
		mlog_errno(status);

	/* Now it is right time to recover quotas... We have to do this under
	 * superblock lock so that noone can start using the slot (and crash)
	 * before we recover it */
	for (i = 0; i < rm_quota_used; i++) {
		qrec = ocfs2_begin_quota_recovery(osb, rm_quota[i]);
		if (IS_ERR(qrec)) {
			status = PTR_ERR(qrec);
			mlog_errno(status);
			continue;
		}
		ocfs2_queue_recovery_completion(osb->journal, rm_quota[i],
						NULL, NULL, qrec);
	}

	ocfs2_super_unlock(osb, 1);

	/* queue recovery for offline slots */
	ocfs2_queue_replay_slots(osb);

bail:
	mutex_lock(&osb->recovery_lock);
	if (!status && !ocfs2_recovery_completed(osb)) {
		mutex_unlock(&osb->recovery_lock);
		goto restart;
	}

	ocfs2_free_replay_slots(osb);
	osb->recovery_thread_task = NULL;
	mb(); /* sync with ocfs2_recovery_thread_running */
	wake_up(&osb->recovery_event);

	mutex_unlock(&osb->recovery_lock);

	if (rm_quota)
		kfree(rm_quota);

	mlog_exit(status);
	/* no one is callint kthread_stop() for us so the kthread() api
	 * requires that we call do_exit().  And it isn't exported, but
	 * complete_and_exit() seems to be a minimal wrapper around it. */
	complete_and_exit(NULL, status);
	return status;
}