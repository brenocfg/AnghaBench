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
typedef  int /*<<< orphan*/  xfs_flock64_t ;
struct xfs_inode {TYPE_1__* i_mount; } ;
struct inode {int i_flags; int /*<<< orphan*/  i_mode; } ;
struct file {int f_mode; int f_flags; int /*<<< orphan*/  f_pos; } ;
struct TYPE_2__ {int /*<<< orphan*/  m_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EPERM ; 
 int FMODE_WRITE ; 
 int IO_INVIS ; 
 int O_NDELAY ; 
 int O_NONBLOCK ; 
 int O_SYNC ; 
 int S_APPEND ; 
 int S_IMMUTABLE ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int XFS_ATTR_DMI ; 
 int XFS_ATTR_NONBLOCK ; 
 int XFS_ATTR_SYNC ; 
 int XFS_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mnt_drop_write_file (struct file*) ; 
 int mnt_want_write_file (struct file*) ; 
 int xfs_change_file_space (struct xfs_inode*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xfs_sb_version_hasextflgbit (int /*<<< orphan*/ *) ; 

int
xfs_ioc_space(
	struct xfs_inode	*ip,
	struct inode		*inode,
	struct file		*filp,
	int			ioflags,
	unsigned int		cmd,
	xfs_flock64_t		*bf)
{
	int			attr_flags = 0;
	int			error;

	/*
	 * Only allow the sys admin to reserve space unless
	 * unwritten extents are enabled.
	 */
	if (!xfs_sb_version_hasextflgbit(&ip->i_mount->m_sb) &&
	    !capable(CAP_SYS_ADMIN))
		return -XFS_ERROR(EPERM);

	if (inode->i_flags & (S_IMMUTABLE|S_APPEND))
		return -XFS_ERROR(EPERM);

	if (!(filp->f_mode & FMODE_WRITE))
		return -XFS_ERROR(EBADF);

	if (!S_ISREG(inode->i_mode))
		return -XFS_ERROR(EINVAL);

	if (filp->f_flags & (O_NDELAY|O_NONBLOCK))
		attr_flags |= XFS_ATTR_NONBLOCK;

	if (filp->f_flags & O_SYNC)
		attr_flags |= XFS_ATTR_SYNC;

	if (ioflags & IO_INVIS)
		attr_flags |= XFS_ATTR_DMI;

	error = mnt_want_write_file(filp);
	if (error)
		return error;
	error = xfs_change_file_space(ip, cmd, bf, filp->f_pos, attr_flags);
	mnt_drop_write_file(filp);
	return -error;
}