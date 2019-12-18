#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ sx_fdtmp; scalar_t__ sx_fdtarget; } ;
typedef  TYPE_3__ xfs_swapext_t ;
struct TYPE_13__ {scalar_t__ i_mount; scalar_t__ i_ino; } ;
typedef  TYPE_4__ xfs_inode_t ;
struct TYPE_11__ {TYPE_1__* dentry; } ;
struct file {int f_mode; int f_flags; TYPE_2__ f_path; } ;
struct TYPE_10__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 scalar_t__ IS_SWAPFILE (int /*<<< orphan*/ ) ; 
 int O_APPEND ; 
 int XFS_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ XFS_FORCED_SHUTDOWN (scalar_t__) ; 
 TYPE_4__* XFS_I (int /*<<< orphan*/ ) ; 
 struct file* fget (int) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 int xfs_swap_extents (TYPE_4__*,TYPE_4__*,TYPE_3__*) ; 

int
xfs_swapext(
	xfs_swapext_t	*sxp)
{
	xfs_inode_t     *ip, *tip;
	struct file	*file, *tmp_file;
	int		error = 0;

	/* Pull information for the target fd */
	file = fget((int)sxp->sx_fdtarget);
	if (!file) {
		error = XFS_ERROR(EINVAL);
		goto out;
	}

	if (!(file->f_mode & FMODE_WRITE) ||
	    !(file->f_mode & FMODE_READ) ||
	    (file->f_flags & O_APPEND)) {
		error = XFS_ERROR(EBADF);
		goto out_put_file;
	}

	tmp_file = fget((int)sxp->sx_fdtmp);
	if (!tmp_file) {
		error = XFS_ERROR(EINVAL);
		goto out_put_file;
	}

	if (!(tmp_file->f_mode & FMODE_WRITE) ||
	    !(tmp_file->f_mode & FMODE_READ) ||
	    (tmp_file->f_flags & O_APPEND)) {
		error = XFS_ERROR(EBADF);
		goto out_put_tmp_file;
	}

	if (IS_SWAPFILE(file->f_path.dentry->d_inode) ||
	    IS_SWAPFILE(tmp_file->f_path.dentry->d_inode)) {
		error = XFS_ERROR(EINVAL);
		goto out_put_tmp_file;
	}

	ip = XFS_I(file->f_path.dentry->d_inode);
	tip = XFS_I(tmp_file->f_path.dentry->d_inode);

	if (ip->i_mount != tip->i_mount) {
		error = XFS_ERROR(EINVAL);
		goto out_put_tmp_file;
	}

	if (ip->i_ino == tip->i_ino) {
		error = XFS_ERROR(EINVAL);
		goto out_put_tmp_file;
	}

	if (XFS_FORCED_SHUTDOWN(ip->i_mount)) {
		error = XFS_ERROR(EIO);
		goto out_put_tmp_file;
	}

	error = xfs_swap_extents(ip, tip, sxp);

 out_put_tmp_file:
	fput(tmp_file);
 out_put_file:
	fput(file);
 out:
	return error;
}