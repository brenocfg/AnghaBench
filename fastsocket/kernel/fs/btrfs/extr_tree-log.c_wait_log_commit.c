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
struct btrfs_trans_handle {scalar_t__ transid; } ;
struct btrfs_root {unsigned long log_transid; int /*<<< orphan*/  log_mutex; int /*<<< orphan*/ * log_commit_wait; int /*<<< orphan*/ * log_commit; TYPE_1__* fs_info; } ;
struct TYPE_2__ {scalar_t__ last_trans_log_full_commit; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int wait_log_commit(struct btrfs_trans_handle *trans,
			   struct btrfs_root *root, unsigned long transid)
{
	DEFINE_WAIT(wait);
	int index = transid % 2;

	/*
	 * we only allow two pending log transactions at a time,
	 * so we know that if ours is more than 2 older than the
	 * current transaction, we're done
	 */
	do {
		prepare_to_wait(&root->log_commit_wait[index],
				&wait, TASK_UNINTERRUPTIBLE);
		mutex_unlock(&root->log_mutex);

		if (root->fs_info->last_trans_log_full_commit !=
		    trans->transid && root->log_transid < transid + 2 &&
		    atomic_read(&root->log_commit[index]))
			schedule();

		finish_wait(&root->log_commit_wait[index], &wait);
		mutex_lock(&root->log_mutex);
	} while (root->fs_info->last_trans_log_full_commit !=
		 trans->transid && root->log_transid < transid + 2 &&
		 atomic_read(&root->log_commit[index]));
	return 0;
}