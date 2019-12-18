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
struct btrfs_root {int /*<<< orphan*/  fs_info; } ;

/* Variables and functions */
#define  BTRFS_BALANCE_CTL_CANCEL 129 
#define  BTRFS_BALANCE_CTL_PAUSE 128 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 long EINVAL ; 
 long EPERM ; 
 long btrfs_cancel_balance (int /*<<< orphan*/ ) ; 
 long btrfs_pause_balance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static long btrfs_ioctl_balance_ctl(struct btrfs_root *root, int cmd)
{
	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	switch (cmd) {
	case BTRFS_BALANCE_CTL_PAUSE:
		return btrfs_pause_balance(root->fs_info);
	case BTRFS_BALANCE_CTL_CANCEL:
		return btrfs_cancel_balance(root->fs_info);
	}

	return -EINVAL;
}