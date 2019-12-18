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
struct btrfs_root {TYPE_1__* fs_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  open_ioctl_trans; scalar_t__ log_root_recovering; } ;

/* Variables and functions */
 int TRANS_START ; 
 int TRANS_USERSPACE ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int may_wait_transaction(struct btrfs_root *root, int type)
{
	if (root->fs_info->log_root_recovering)
		return 0;

	if (type == TRANS_USERSPACE)
		return 1;

	if (type == TRANS_START &&
	    !atomic_read(&root->fs_info->open_ioctl_trans))
		return 1;

	return 0;
}