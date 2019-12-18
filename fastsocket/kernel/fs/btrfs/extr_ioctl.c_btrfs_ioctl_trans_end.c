#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  mnt; } ;
struct file {TYPE_1__ f_path; struct btrfs_trans_handle* private_data; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {TYPE_2__* fs_info; } ;
struct TYPE_8__ {struct btrfs_root* root; } ;
struct TYPE_7__ {struct inode* d_inode; } ;
struct TYPE_6__ {int /*<<< orphan*/  open_ioctl_trans; } ;

/* Variables and functions */
 TYPE_4__* BTRFS_I (struct inode*) ; 
 long EINVAL ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_end_transaction (struct btrfs_trans_handle*,struct btrfs_root*) ; 
 TYPE_3__* fdentry (struct file*) ; 
 int /*<<< orphan*/  mnt_drop_write (int /*<<< orphan*/ ) ; 

long btrfs_ioctl_trans_end(struct file *file)
{
	struct inode *inode = fdentry(file)->d_inode;
	struct btrfs_root *root = BTRFS_I(inode)->root;
	struct btrfs_trans_handle *trans;

	trans = file->private_data;
	if (!trans)
		return -EINVAL;
	file->private_data = NULL;

	btrfs_end_transaction(trans, root);

	atomic_dec(&root->fs_info->open_ioctl_trans);

	mnt_drop_write(file->f_path.mnt);
	return 0;
}