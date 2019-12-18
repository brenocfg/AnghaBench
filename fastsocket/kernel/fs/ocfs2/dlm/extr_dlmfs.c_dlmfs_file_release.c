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
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_mode; } ;
struct file {int /*<<< orphan*/ * private_data; } ;
struct dlmfs_inode_private {int /*<<< orphan*/  ip_lockres; } ;
struct dlmfs_filp_private {int fp_lock_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 struct dlmfs_inode_private* DLMFS_I (struct inode*) ; 
 int LKM_IVMODE ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dlmfs_filp_private*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_dlm_cluster_unlock (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int dlmfs_file_release(struct inode *inode,
			      struct file *file)
{
	int level, status;
	struct dlmfs_inode_private *ip = DLMFS_I(inode);
	struct dlmfs_filp_private *fp =
		(struct dlmfs_filp_private *) file->private_data;

	if (S_ISDIR(inode->i_mode))
		BUG();

	mlog(0, "close called on inode %lu\n", inode->i_ino);

	status = 0;
	if (fp) {
		level = fp->fp_lock_level;
		if (level != LKM_IVMODE)
			user_dlm_cluster_unlock(&ip->ip_lockres, level);

		kfree(fp);
		file->private_data = NULL;
	}

	return 0;
}