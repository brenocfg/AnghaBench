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
struct inode {int dummy; } ;
struct fuse_conn {int dummy; } ;
struct file {TYPE_1__* f_dentry; } ;
struct TYPE_2__ {struct inode* d_inode; } ;

/* Variables and functions */
 long EACCES ; 
 long EIO ; 
 int /*<<< orphan*/  fuse_allow_current_process (struct fuse_conn*) ; 
 long fuse_do_ioctl (struct file*,unsigned int,unsigned long,unsigned int) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 

__attribute__((used)) static long fuse_file_ioctl_common(struct file *file, unsigned int cmd,
				   unsigned long arg, unsigned int flags)
{
	struct inode *inode = file->f_dentry->d_inode;
	struct fuse_conn *fc = get_fuse_conn(inode);

	if (!fuse_allow_current_process(fc))
		return -EACCES;

	if (is_bad_inode(inode))
		return -EIO;

	return fuse_do_ioctl(file, cmd, arg, flags);
}