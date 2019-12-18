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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_7__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_6__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_5__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct inode {int i_mode; TYPE_4__* i_sb; int /*<<< orphan*/  i_blkbits; TYPE_3__ i_ctime; TYPE_2__ i_mtime; TYPE_1__ i_atime; int /*<<< orphan*/  i_blocks; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_nlink; int /*<<< orphan*/  i_ino; } ;
struct fuse_inode {int orig_i_mode; int /*<<< orphan*/  orig_ino; int /*<<< orphan*/  i_time; scalar_t__ attr_version; } ;
struct fuse_conn {int flags; scalar_t__ attr_version; } ;
struct fuse_attr {int mode; scalar_t__ blksize; int /*<<< orphan*/  ino; int /*<<< orphan*/  ctimensec; int /*<<< orphan*/  ctime; int /*<<< orphan*/  mtimensec; int /*<<< orphan*/  mtime; int /*<<< orphan*/  atimensec; int /*<<< orphan*/  atime; int /*<<< orphan*/  blocks; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  nlink; } ;
struct TYPE_8__ {int /*<<< orphan*/  s_blocksize_bits; } ;

/* Variables and functions */
 int FUSE_DEFAULT_PERMISSIONS ; 
 int S_IFMT ; 
 int S_ISVTX ; 
 int /*<<< orphan*/  fuse_squash_ino (int /*<<< orphan*/ ) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 struct fuse_inode* get_fuse_inode (struct inode*) ; 
 int /*<<< orphan*/  ilog2 (scalar_t__) ; 

void fuse_change_attributes_common(struct inode *inode, struct fuse_attr *attr,
				   u64 attr_valid)
{
	struct fuse_conn *fc = get_fuse_conn(inode);
	struct fuse_inode *fi = get_fuse_inode(inode);

	fi->attr_version = ++fc->attr_version;
	fi->i_time = attr_valid;

	inode->i_ino     = fuse_squash_ino(attr->ino);
	inode->i_mode    = (inode->i_mode & S_IFMT) | (attr->mode & 07777);
	inode->i_nlink   = attr->nlink;
	inode->i_uid     = attr->uid;
	inode->i_gid     = attr->gid;
	inode->i_blocks  = attr->blocks;
	inode->i_atime.tv_sec   = attr->atime;
	inode->i_atime.tv_nsec  = attr->atimensec;
	inode->i_mtime.tv_sec   = attr->mtime;
	inode->i_mtime.tv_nsec  = attr->mtimensec;
	inode->i_ctime.tv_sec   = attr->ctime;
	inode->i_ctime.tv_nsec  = attr->ctimensec;

	if (attr->blksize != 0)
		inode->i_blkbits = ilog2(attr->blksize);
	else
		inode->i_blkbits = inode->i_sb->s_blocksize_bits;

	/*
	 * Don't set the sticky bit in i_mode, unless we want the VFS
	 * to check permissions.  This prevents failures due to the
	 * check in may_delete().
	 */
	fi->orig_i_mode = inode->i_mode;
	if (!(fc->flags & FUSE_DEFAULT_PERMISSIONS))
		inode->i_mode &= ~S_ISVTX;

	fi->orig_ino = attr->ino;
}