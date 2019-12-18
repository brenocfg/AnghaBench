#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
typedef  scalar_t__ xfs_off_t ;
typedef  int /*<<< orphan*/  xfs_mount_t ;
struct TYPE_16__ {int di_mode; int /*<<< orphan*/  di_flags; } ;
struct TYPE_17__ {TYPE_1__ i_d; int /*<<< orphan*/ * i_mount; } ;
typedef  TYPE_2__ xfs_inode_t ;
typedef  scalar_t__ xfs_fsize_t ;
struct TYPE_18__ {int l_whence; scalar_t__ l_start; scalar_t__ l_len; } ;
typedef  TYPE_3__ xfs_flock64_t ;
struct iattr {scalar_t__ ia_size; int /*<<< orphan*/  ia_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATTR_SIZE ; 
 int /*<<< orphan*/  EINVAL ; 
 int S_ISGID ; 
 int /*<<< orphan*/  S_ISREG (int) ; 
 int S_ISUID ; 
 int S_IXGRP ; 
 int XFS_ATTR_DMI ; 
 int XFS_ATTR_NOLOCK ; 
 int XFS_ATTR_SYNC ; 
 int XFS_BMAPI_CONVERT ; 
 int XFS_BMAPI_PREALLOC ; 
 int /*<<< orphan*/  XFS_DIFLAG_PREALLOC ; 
 int XFS_ERROR (int /*<<< orphan*/ ) ; 
 int XFS_ICHGTIME_CHG ; 
 int XFS_ICHGTIME_MOD ; 
 int /*<<< orphan*/  XFS_ILOCK_EXCL ; 
 int /*<<< orphan*/  XFS_ILOG_CORE ; 
#define  XFS_IOC_ALLOCSP 136 
#define  XFS_IOC_ALLOCSP64 135 
#define  XFS_IOC_FREESP 134 
#define  XFS_IOC_FREESP64 133 
#define  XFS_IOC_RESVSP 132 
#define  XFS_IOC_RESVSP64 131 
#define  XFS_IOC_UNRESVSP 130 
#define  XFS_IOC_UNRESVSP64 129 
#define  XFS_IOC_ZERO_RANGE 128 
 int /*<<< orphan*/  XFS_IOLOCK_EXCL ; 
 scalar_t__ XFS_ISIZE (TYPE_2__*) ; 
 scalar_t__ XFS_MAXIOFFSET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XFS_TRANS_WRITEID ; 
 int /*<<< orphan*/  XFS_WRITEID_LOG_RES (int /*<<< orphan*/ *) ; 
 int xfs_alloc_file_space (TYPE_2__*,scalar_t__,scalar_t__,int,int) ; 
 int xfs_free_file_space (TYPE_2__*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  xfs_ilock (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_iunlock (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int xfs_setattr (TYPE_2__*,struct iattr*,int) ; 
 int /*<<< orphan*/  xfs_tosspages (TYPE_2__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xfs_trans_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_cancel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int xfs_trans_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_ichgtime (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  xfs_trans_ijoin (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  xfs_trans_log_inode (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int xfs_trans_reserve (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_set_sync (int /*<<< orphan*/ *) ; 

int
xfs_change_file_space(
	xfs_inode_t	*ip,
	int		cmd,
	xfs_flock64_t	*bf,
	xfs_off_t	offset,
	int		attr_flags)
{
	xfs_mount_t	*mp = ip->i_mount;
	int		clrprealloc;
	int		error;
	xfs_fsize_t	fsize;
	int		setprealloc;
	xfs_off_t	startoffset;
	xfs_off_t	llen;
	xfs_trans_t	*tp;
	struct iattr	iattr;
	int		prealloc_type;

	if (!S_ISREG(ip->i_d.di_mode))
		return XFS_ERROR(EINVAL);

	switch (bf->l_whence) {
	case 0: /*SEEK_SET*/
		break;
	case 1: /*SEEK_CUR*/
		bf->l_start += offset;
		break;
	case 2: /*SEEK_END*/
		bf->l_start += XFS_ISIZE(ip);
		break;
	default:
		return XFS_ERROR(EINVAL);
	}

	llen = bf->l_len > 0 ? bf->l_len - 1 : bf->l_len;

	if (   (bf->l_start < 0)
	    || (bf->l_start > XFS_MAXIOFFSET(mp))
	    || (bf->l_start + llen < 0)
	    || (bf->l_start + llen > XFS_MAXIOFFSET(mp)))
		return XFS_ERROR(EINVAL);

	bf->l_whence = 0;

	startoffset = bf->l_start;
	fsize = XFS_ISIZE(ip);

	/*
	 * XFS_IOC_RESVSP and XFS_IOC_UNRESVSP will reserve or unreserve
	 * file space.
	 * These calls do NOT zero the data space allocated to the file,
	 * nor do they change the file size.
	 *
	 * XFS_IOC_ALLOCSP and XFS_IOC_FREESP will allocate and free file
	 * space.
	 * These calls cause the new file data to be zeroed and the file
	 * size to be changed.
	 */
	setprealloc = clrprealloc = 0;
	prealloc_type = XFS_BMAPI_PREALLOC;

	switch (cmd) {
	case XFS_IOC_ZERO_RANGE:
		prealloc_type |= XFS_BMAPI_CONVERT;
		xfs_tosspages(ip, startoffset, startoffset + bf->l_len, 0);
		/* FALLTHRU */
	case XFS_IOC_RESVSP:
	case XFS_IOC_RESVSP64:
		error = xfs_alloc_file_space(ip, startoffset, bf->l_len,
						prealloc_type, attr_flags);
		if (error)
			return error;
		setprealloc = 1;
		break;

	case XFS_IOC_UNRESVSP:
	case XFS_IOC_UNRESVSP64:
		if ((error = xfs_free_file_space(ip, startoffset, bf->l_len,
								attr_flags)))
			return error;
		break;

	case XFS_IOC_ALLOCSP:
	case XFS_IOC_ALLOCSP64:
	case XFS_IOC_FREESP:
	case XFS_IOC_FREESP64:
		/*
		 * These operations actually do IO when extending the file, but
		 * the allocation is done seperately to the zeroing that is
		 * done. This set of operations need to be serialised against
		 * other IO operations, such as truncate and buffered IO. We
		 * need to take the IOLOCK here to serialise the allocation and
		 * zeroing IO to prevent other IOLOCK holders (e.g. getbmap,
		 * truncate, direct IO) from racing against the transient
		 * allocated but not written state we can have here.
		 */
		xfs_ilock(ip, XFS_IOLOCK_EXCL);
		if (startoffset > fsize) {
			error = xfs_alloc_file_space(ip, fsize,
					startoffset - fsize, 0,
					attr_flags | XFS_ATTR_NOLOCK);
			if (error) {
				xfs_iunlock(ip, XFS_IOLOCK_EXCL);
				break;
			}
		}

		iattr.ia_valid = ATTR_SIZE;
		iattr.ia_size = startoffset;

		error = xfs_setattr(ip, &iattr, attr_flags | XFS_ATTR_NOLOCK);
		xfs_iunlock(ip, XFS_IOLOCK_EXCL);

		if (error)
			return error;

		clrprealloc = 1;
		break;

	default:
		ASSERT(0);
		return XFS_ERROR(EINVAL);
	}

	/*
	 * update the inode timestamp, mode, and prealloc flag bits
	 */
	tp = xfs_trans_alloc(mp, XFS_TRANS_WRITEID);

	if ((error = xfs_trans_reserve(tp, 0, XFS_WRITEID_LOG_RES(mp),
				      0, 0, 0))) {
		/* ASSERT(0); */
		xfs_trans_cancel(tp, 0);
		return error;
	}

	xfs_ilock(ip, XFS_ILOCK_EXCL);

	xfs_trans_ijoin(tp, ip);

	if ((attr_flags & XFS_ATTR_DMI) == 0) {
		ip->i_d.di_mode &= ~S_ISUID;

		/*
		 * Note that we don't have to worry about mandatory
		 * file locking being disabled here because we only
		 * clear the S_ISGID bit if the Group execute bit is
		 * on, but if it was on then mandatory locking wouldn't
		 * have been enabled.
		 */
		if (ip->i_d.di_mode & S_IXGRP)
			ip->i_d.di_mode &= ~S_ISGID;

		xfs_trans_ichgtime(tp, ip, XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG);
	}
	if (setprealloc)
		ip->i_d.di_flags |= XFS_DIFLAG_PREALLOC;
	else if (clrprealloc)
		ip->i_d.di_flags &= ~XFS_DIFLAG_PREALLOC;

	xfs_trans_log_inode(tp, ip, XFS_ILOG_CORE);
	if (attr_flags & XFS_ATTR_SYNC)
		xfs_trans_set_sync(tp);

	error = xfs_trans_commit(tp, 0);

	xfs_iunlock(ip, XFS_ILOCK_EXCL);

	return error;
}