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
struct path {TYPE_1__* mnt; struct dentry* dentry; } ;
struct inode {int i_mode; } ;
struct dentry {struct inode* d_inode; } ;
struct TYPE_2__ {int mnt_flags; } ;

/* Variables and functions */
 int EACCES ; 
 int EISDIR ; 
 int ELOOP ; 
 int ENOENT ; 
 int EPERM ; 
 scalar_t__ IS_APPEND (struct inode*) ; 
 int MAY_WRITE ; 
 int MNT_NODEV ; 
 int O_ACCMODE ; 
 int O_APPEND ; 
 int O_NOATIME ; 
 int O_RDONLY ; 
 int O_TRUNC ; 
#define  S_IFBLK 133 
#define  S_IFCHR 132 
#define  S_IFDIR 131 
#define  S_IFIFO 130 
#define  S_IFLNK 129 
 int S_IFMT ; 
#define  S_IFSOCK 128 
 int break_lease (struct inode*,int) ; 
 int inode_permission (struct inode*,int) ; 
 int /*<<< orphan*/  is_owner_or_cap (struct inode*) ; 

int may_open(struct path *path, int acc_mode, int flag)
{
	struct dentry *dentry = path->dentry;
	struct inode *inode = dentry->d_inode;
	int error;

	if (!inode)
		return -ENOENT;

	switch (inode->i_mode & S_IFMT) {
	case S_IFLNK:
		return -ELOOP;
	case S_IFDIR:
		if (acc_mode & MAY_WRITE)
			return -EISDIR;
		break;
	case S_IFBLK:
	case S_IFCHR:
		if (path->mnt->mnt_flags & MNT_NODEV)
			return -EACCES;
		/*FALLTHRU*/
	case S_IFIFO:
	case S_IFSOCK:
		flag &= ~O_TRUNC;
		break;
	}

	error = inode_permission(inode, acc_mode);
	if (error)
		return error;

	/*
	 * An append-only file must be opened in append mode for writing.
	 */
	if (IS_APPEND(inode)) {
		if  ((flag & O_ACCMODE) != O_RDONLY && !(flag & O_APPEND))
			return -EPERM;
		if (flag & O_TRUNC)
			return -EPERM;
	}

	/* O_NOATIME can only be set by the owner or superuser */
	if (flag & O_NOATIME && !is_owner_or_cap(inode))
		return -EPERM;

	/*
	 * Ensure there are no outstanding leases on the file.
	 */
	return break_lease(inode, flag);
}