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
struct file {struct dlmfs_filp_private* private_data; int /*<<< orphan*/  f_flags; } ;
struct dlmfs_inode_private {int /*<<< orphan*/  ip_lockres; } ;
struct dlmfs_filp_private {int fp_lock_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 struct dlmfs_inode_private* DLMFS_I (struct inode*) ; 
 int EAGAIN ; 
 int ENOMEM ; 
 int ETXTBSY ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int LKM_NOQUEUE ; 
 int /*<<< orphan*/  O_APPEND ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int dlmfs_decode_open_flags (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  kfree (struct dlmfs_filp_private*) ; 
 struct dlmfs_filp_private* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int user_dlm_cluster_lock (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int dlmfs_file_open(struct inode *inode,
			   struct file *file)
{
	int status, level, flags;
	struct dlmfs_filp_private *fp = NULL;
	struct dlmfs_inode_private *ip;

	if (S_ISDIR(inode->i_mode))
		BUG();

	mlog(0, "open called on inode %lu, flags 0x%x\n", inode->i_ino,
		file->f_flags);

	status = dlmfs_decode_open_flags(file->f_flags, &level, &flags);
	if (status < 0)
		goto bail;

	/* We don't want to honor O_APPEND at read/write time as it
	 * doesn't make sense for LVB writes. */
	file->f_flags &= ~O_APPEND;

	fp = kmalloc(sizeof(*fp), GFP_NOFS);
	if (!fp) {
		status = -ENOMEM;
		goto bail;
	}
	fp->fp_lock_level = level;

	ip = DLMFS_I(inode);

	status = user_dlm_cluster_lock(&ip->ip_lockres, level, flags);
	if (status < 0) {
		/* this is a strange error to return here but I want
		 * to be able userspace to be able to distinguish a
		 * valid lock request from one that simply couldn't be
		 * granted. */
		if (flags & LKM_NOQUEUE && status == -EAGAIN)
			status = -ETXTBSY;
		kfree(fp);
		goto bail;
	}

	file->private_data = fp;
bail:
	return status;
}