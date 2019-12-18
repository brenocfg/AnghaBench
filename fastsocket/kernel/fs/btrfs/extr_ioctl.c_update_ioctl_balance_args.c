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
struct btrfs_ioctl_balance_args {int /*<<< orphan*/  stat; int /*<<< orphan*/  sys; int /*<<< orphan*/  meta; int /*<<< orphan*/  data; int /*<<< orphan*/  state; int /*<<< orphan*/  flags; } ;
struct btrfs_fs_info {int /*<<< orphan*/  balance_lock; int /*<<< orphan*/  balance_cancel_req; int /*<<< orphan*/  balance_pause_req; int /*<<< orphan*/  balance_running; struct btrfs_balance_control* balance_ctl; } ;
struct btrfs_balance_control {int /*<<< orphan*/  stat; int /*<<< orphan*/  sys; int /*<<< orphan*/  meta; int /*<<< orphan*/  data; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_BALANCE_STATE_CANCEL_REQ ; 
 int /*<<< orphan*/  BTRFS_BALANCE_STATE_PAUSE_REQ ; 
 int /*<<< orphan*/  BTRFS_BALANCE_STATE_RUNNING ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void update_ioctl_balance_args(struct btrfs_fs_info *fs_info, int lock,
			       struct btrfs_ioctl_balance_args *bargs)
{
	struct btrfs_balance_control *bctl = fs_info->balance_ctl;

	bargs->flags = bctl->flags;

	if (atomic_read(&fs_info->balance_running))
		bargs->state |= BTRFS_BALANCE_STATE_RUNNING;
	if (atomic_read(&fs_info->balance_pause_req))
		bargs->state |= BTRFS_BALANCE_STATE_PAUSE_REQ;
	if (atomic_read(&fs_info->balance_cancel_req))
		bargs->state |= BTRFS_BALANCE_STATE_CANCEL_REQ;

	memcpy(&bargs->data, &bctl->data, sizeof(bargs->data));
	memcpy(&bargs->meta, &bctl->meta, sizeof(bargs->meta));
	memcpy(&bargs->sys, &bctl->sys, sizeof(bargs->sys));

	if (lock) {
		spin_lock(&fs_info->balance_lock);
		memcpy(&bargs->stat, &bctl->stat, sizeof(bargs->stat));
		spin_unlock(&fs_info->balance_lock);
	} else {
		memcpy(&bargs->stat, &bctl->stat, sizeof(bargs->stat));
	}
}