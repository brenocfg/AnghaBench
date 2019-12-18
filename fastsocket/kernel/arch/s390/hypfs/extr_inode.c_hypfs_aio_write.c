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
struct super_block {int /*<<< orphan*/  s_root; struct hypfs_sb_info* s_fs_info; } ;
struct kiocb {TYPE_4__* ki_filp; } ;
struct iovec {int dummy; } ;
struct hypfs_sb_info {scalar_t__ last_update; int /*<<< orphan*/  lock; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_7__ {TYPE_2__* dentry; } ;
struct TYPE_8__ {TYPE_3__ f_path; } ;
struct TYPE_6__ {TYPE_1__* d_inode; } ;
struct TYPE_5__ {struct super_block* i_sb; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ MACHINE_IS_VM ; 
 scalar_t__ get_seconds () ; 
 int /*<<< orphan*/  hypfs_delete_tree (int /*<<< orphan*/ ) ; 
 int hypfs_diag_create_files (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hypfs_update_update (struct super_block*) ; 
 int hypfs_vm_create_files (struct super_block*,int /*<<< orphan*/ ) ; 
 size_t iov_length (struct iovec const*,unsigned long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static ssize_t hypfs_aio_write(struct kiocb *iocb, const struct iovec *iov,
			      unsigned long nr_segs, loff_t offset)
{
	int rc;
	struct super_block *sb;
	struct hypfs_sb_info *fs_info;
	size_t count = iov_length(iov, nr_segs);

	sb = iocb->ki_filp->f_path.dentry->d_inode->i_sb;
	fs_info = sb->s_fs_info;
	/*
	 * Currently we only allow one update per second for two reasons:
	 * 1. diag 204 is VERY expensive
	 * 2. If several processes do updates in parallel and then read the
	 *    hypfs data, the likelihood of collisions is reduced, if we restrict
	 *    the minimum update interval. A collision occurs, if during the
	 *    data gathering of one process another process triggers an update
	 *    If the first process wants to ensure consistent data, it has
	 *    to restart data collection in this case.
	 */
	mutex_lock(&fs_info->lock);
	if (fs_info->last_update == get_seconds()) {
		rc = -EBUSY;
		goto out;
	}
	hypfs_delete_tree(sb->s_root);
	if (MACHINE_IS_VM)
		rc = hypfs_vm_create_files(sb, sb->s_root);
	else
		rc = hypfs_diag_create_files(sb, sb->s_root);
	if (rc) {
		pr_err("Updating the hypfs tree failed\n");
		hypfs_delete_tree(sb->s_root);
		goto out;
	}
	hypfs_update_update(sb);
	rc = count;
out:
	mutex_unlock(&fs_info->lock);
	return rc;
}