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
struct super_block {int /*<<< orphan*/ * s_bdev; TYPE_4__* s_op; } ;
struct TYPE_7__ {TYPE_2__* dentry; } ;
struct file {TYPE_3__ f_path; } ;
struct TYPE_8__ {int /*<<< orphan*/ * freeze_fs; } ;
struct TYPE_6__ {TYPE_1__* d_inode; } ;
struct TYPE_5__ {struct super_block* i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 scalar_t__ IS_ERR (struct super_block*) ; 
 int PTR_ERR (struct super_block*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct super_block* freeze_bdev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ioctl_fsfreeze(struct file *filp)
{
	struct super_block *sb = filp->f_path.dentry->d_inode->i_sb;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	/* If filesystem doesn't support freeze feature, return. */
	if (sb->s_op->freeze_fs == NULL)
		return -EOPNOTSUPP;

	/* If a blockdevice-backed filesystem isn't specified, return. */
	if (sb->s_bdev == NULL)
		return -EINVAL;

	/* Freeze */
	sb = freeze_bdev(sb->s_bdev);
	if (IS_ERR(sb))
		return PTR_ERR(sb);
	return 0;
}