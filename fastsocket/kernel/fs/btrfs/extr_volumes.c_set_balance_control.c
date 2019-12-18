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
struct btrfs_fs_info {int /*<<< orphan*/  balance_lock; struct btrfs_balance_control* balance_ctl; } ;
struct btrfs_balance_control {struct btrfs_fs_info* fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (struct btrfs_balance_control*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void set_balance_control(struct btrfs_balance_control *bctl)
{
	struct btrfs_fs_info *fs_info = bctl->fs_info;

	BUG_ON(fs_info->balance_ctl);

	spin_lock(&fs_info->balance_lock);
	fs_info->balance_ctl = bctl;
	spin_unlock(&fs_info->balance_lock);
}