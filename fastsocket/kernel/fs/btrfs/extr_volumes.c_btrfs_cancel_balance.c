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
struct btrfs_fs_info {int /*<<< orphan*/  balance_mutex; int /*<<< orphan*/  balance_cancel_req; int /*<<< orphan*/  balance_running; scalar_t__ balance_ctl; int /*<<< orphan*/  volume_mutex; int /*<<< orphan*/  balance_wait_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  __cancel_balance (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

int btrfs_cancel_balance(struct btrfs_fs_info *fs_info)
{
	mutex_lock(&fs_info->balance_mutex);
	if (!fs_info->balance_ctl) {
		mutex_unlock(&fs_info->balance_mutex);
		return -ENOTCONN;
	}

	atomic_inc(&fs_info->balance_cancel_req);
	/*
	 * if we are running just wait and return, balance item is
	 * deleted in btrfs_balance in this case
	 */
	if (atomic_read(&fs_info->balance_running)) {
		mutex_unlock(&fs_info->balance_mutex);
		wait_event(fs_info->balance_wait_q,
			   atomic_read(&fs_info->balance_running) == 0);
		mutex_lock(&fs_info->balance_mutex);
	} else {
		/* __cancel_balance needs volume_mutex */
		mutex_unlock(&fs_info->balance_mutex);
		mutex_lock(&fs_info->volume_mutex);
		mutex_lock(&fs_info->balance_mutex);

		if (fs_info->balance_ctl)
			__cancel_balance(fs_info);

		mutex_unlock(&fs_info->volume_mutex);
	}

	BUG_ON(fs_info->balance_ctl || atomic_read(&fs_info->balance_running));
	atomic_dec(&fs_info->balance_cancel_req);
	mutex_unlock(&fs_info->balance_mutex);
	return 0;
}