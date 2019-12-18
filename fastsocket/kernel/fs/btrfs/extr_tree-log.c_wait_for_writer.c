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
struct btrfs_root {int /*<<< orphan*/  log_writer_wait; int /*<<< orphan*/  log_mutex; int /*<<< orphan*/  log_writers; TYPE_1__* fs_info; } ;
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

__attribute__((used)) static void wait_for_writer(struct btrfs_trans_handle *trans,
			    struct btrfs_root *root)
{
	DEFINE_WAIT(wait);
	while (root->fs_info->last_trans_log_full_commit !=
	       trans->transid && atomic_read(&root->log_writers)) {
		prepare_to_wait(&root->log_writer_wait,
				&wait, TASK_UNINTERRUPTIBLE);
		mutex_unlock(&root->log_mutex);
		if (root->fs_info->last_trans_log_full_commit !=
		    trans->transid && atomic_read(&root->log_writers))
			schedule();
		mutex_lock(&root->log_mutex);
		finish_wait(&root->log_writer_wait, &wait);
	}
}