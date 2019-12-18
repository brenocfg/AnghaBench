#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  if_rdev; } ;
struct TYPE_13__ {int if_flags; TYPE_2__ if_u2; } ;
struct TYPE_23__ {int /*<<< orphan*/  t_nsec; int /*<<< orphan*/  t_sec; } ;
struct TYPE_21__ {int /*<<< orphan*/  t_nsec; int /*<<< orphan*/  t_sec; } ;
struct TYPE_19__ {int /*<<< orphan*/  t_nsec; int /*<<< orphan*/  t_sec; } ;
struct TYPE_24__ {int di_mode; TYPE_8__ di_ctime; TYPE_6__ di_mtime; TYPE_4__ di_atime; int /*<<< orphan*/  di_size; int /*<<< orphan*/  di_gen; int /*<<< orphan*/  di_gid; int /*<<< orphan*/  di_uid; int /*<<< orphan*/  di_nlink; } ;
struct TYPE_22__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_20__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_18__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct inode {int i_state; int i_mode; int /*<<< orphan*/  i_rdev; int /*<<< orphan*/ * i_op; TYPE_11__* i_mapping; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/  i_sb; TYPE_7__ i_ctime; TYPE_5__ i_mtime; TYPE_3__ i_atime; int /*<<< orphan*/  i_generation; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_nlink; int /*<<< orphan*/  i_ino; } ;
struct xfs_inode {TYPE_10__ i_df; TYPE_9__ i_d; TYPE_1__* i_mount; int /*<<< orphan*/  i_ino; struct inode i_vnode; } ;
struct TYPE_16__ {int /*<<< orphan*/  m_super; } ;
struct TYPE_15__ {int /*<<< orphan*/  m_sb; } ;
struct TYPE_14__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int I_LOCK ; 
 int I_NEW ; 
 int /*<<< orphan*/  MKDEV (int,int /*<<< orphan*/ ) ; 
#define  S_IFBLK 132 
#define  S_IFCHR 131 
#define  S_IFDIR 130 
#define  S_IFLNK 129 
 int S_IFMT ; 
#define  S_IFREG 128 
 int XFS_IFINLINE ; 
 int /*<<< orphan*/  XFS_INEW ; 
 TYPE_12__* XFS_M (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  i_size_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_add_to_lists (int /*<<< orphan*/ ,struct inode*) ; 
 int sysv_major (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysv_minor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 
 int /*<<< orphan*/  xfs_address_space_operations ; 
 int /*<<< orphan*/  xfs_diflags_to_iflags (struct inode*,struct xfs_inode*) ; 
 int /*<<< orphan*/  xfs_dir_ci_inode_operations ; 
 int /*<<< orphan*/  xfs_dir_file_operations ; 
 int /*<<< orphan*/  xfs_dir_inode_operations ; 
 int /*<<< orphan*/  xfs_file_operations ; 
 int /*<<< orphan*/  xfs_iflags_clear (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_inode_operations ; 
 int /*<<< orphan*/  xfs_sb_version_hasasciici (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_symlink_inode_operations ; 

void
xfs_setup_inode(
	struct xfs_inode	*ip)
{
	struct inode		*inode = &ip->i_vnode;

	inode->i_ino = ip->i_ino;
	inode->i_state = I_NEW|I_LOCK;
	inode_add_to_lists(ip->i_mount->m_super, inode);

	inode->i_mode	= ip->i_d.di_mode;
	inode->i_nlink	= ip->i_d.di_nlink;
	inode->i_uid	= ip->i_d.di_uid;
	inode->i_gid	= ip->i_d.di_gid;

	switch (inode->i_mode & S_IFMT) {
	case S_IFBLK:
	case S_IFCHR:
		inode->i_rdev =
			MKDEV(sysv_major(ip->i_df.if_u2.if_rdev) & 0x1ff,
			      sysv_minor(ip->i_df.if_u2.if_rdev));
		break;
	default:
		inode->i_rdev = 0;
		break;
	}

	inode->i_generation = ip->i_d.di_gen;
	i_size_write(inode, ip->i_d.di_size);
	inode->i_atime.tv_sec	= ip->i_d.di_atime.t_sec;
	inode->i_atime.tv_nsec	= ip->i_d.di_atime.t_nsec;
	inode->i_mtime.tv_sec	= ip->i_d.di_mtime.t_sec;
	inode->i_mtime.tv_nsec	= ip->i_d.di_mtime.t_nsec;
	inode->i_ctime.tv_sec	= ip->i_d.di_ctime.t_sec;
	inode->i_ctime.tv_nsec	= ip->i_d.di_ctime.t_nsec;
	xfs_diflags_to_iflags(inode, ip);

	switch (inode->i_mode & S_IFMT) {
	case S_IFREG:
		inode->i_op = &xfs_inode_operations;
		inode->i_fop = &xfs_file_operations;
		inode->i_mapping->a_ops = &xfs_address_space_operations;
		break;
	case S_IFDIR:
		if (xfs_sb_version_hasasciici(&XFS_M(inode->i_sb)->m_sb))
			inode->i_op = &xfs_dir_ci_inode_operations;
		else
			inode->i_op = &xfs_dir_inode_operations;
		inode->i_fop = &xfs_dir_file_operations;
		break;
	case S_IFLNK:
		inode->i_op = &xfs_symlink_inode_operations;
		if (!(ip->i_df.if_flags & XFS_IFINLINE))
			inode->i_mapping->a_ops = &xfs_address_space_operations;
		break;
	default:
		inode->i_op = &xfs_inode_operations;
		init_special_inode(inode, inode->i_mode, inode->i_rdev);
		break;
	}

	xfs_iflags_clear(ip, XFS_INEW);
	barrier();

	unlock_new_inode(inode);
}