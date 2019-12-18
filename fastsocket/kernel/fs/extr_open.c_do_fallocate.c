#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct inode {TYPE_4__* i_sb; TYPE_3__* i_op; int /*<<< orphan*/  i_mode; } ;
struct TYPE_7__ {TYPE_1__* dentry; } ;
struct file {int f_mode; TYPE_2__ f_path; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_9__ {scalar_t__ s_maxbytes; } ;
struct TYPE_8__ {long (* fallocate ) (struct inode*,int,scalar_t__,scalar_t__) ;} ;
struct TYPE_6__ {struct inode* d_inode; } ;

/* Variables and functions */
 int EBADF ; 
 int EFBIG ; 
 int EINVAL ; 
 int ENODEV ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int ESPIPE ; 
 int FALLOC_FL_KEEP_SIZE ; 
 int FALLOC_FL_PUNCH_HOLE ; 
 int FMODE_WRITE ; 
 scalar_t__ IS_APPEND (struct inode*) ; 
 scalar_t__ IS_IMMUTABLE (struct inode*) ; 
 int /*<<< orphan*/  MAY_WRITE ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISFIFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_end_write (TYPE_4__*) ; 
 int /*<<< orphan*/  sb_start_write (TYPE_4__*) ; 
 long security_file_permission (struct file*,int /*<<< orphan*/ ) ; 
 long stub1 (struct inode*,int,scalar_t__,scalar_t__) ; 

int do_fallocate(struct file *file, int mode, loff_t offset, loff_t len)
{
	struct inode *inode = file->f_path.dentry->d_inode;
	long ret;

	if (offset < 0 || len <= 0)
		return -EINVAL;

	/* Return error if mode is not supported */
	if (mode & ~(FALLOC_FL_KEEP_SIZE | FALLOC_FL_PUNCH_HOLE))
		return -EOPNOTSUPP;

	/* Punch hole must have keep size set */
	if ((mode & FALLOC_FL_PUNCH_HOLE) &&
	    !(mode & FALLOC_FL_KEEP_SIZE))
		return -EOPNOTSUPP;

	if (!(file->f_mode & FMODE_WRITE))
		return -EBADF;

	/* It's not possible punch hole on append only file */
	if (mode & FALLOC_FL_PUNCH_HOLE && IS_APPEND(inode))
		return -EPERM;

	if (IS_IMMUTABLE(inode))
		return -EPERM;

	/*
	 * Revalidate the write permissions, in case security policy has
	 * changed since the files were opened.
	 */
	ret = security_file_permission(file, MAY_WRITE);
	if (ret)
		return ret;

	if (S_ISFIFO(inode->i_mode))
		return -ESPIPE;

	/*
	 * Let individual file system decide if it supports preallocation
	 * for directories or not.
	 */
	if (!S_ISREG(inode->i_mode) && !S_ISDIR(inode->i_mode))
		return -ENODEV;

	/* Check for wrap through zero too */
	if (((offset + len) > inode->i_sb->s_maxbytes) || ((offset + len) < 0))
		return -EFBIG;

	if (!inode->i_op->fallocate)
		return -EOPNOTSUPP;

	sb_start_write(inode->i_sb);
	ret = inode->i_op->fallocate(inode, mode, offset, len);
	sb_end_write(inode->i_sb);
	return ret;
}