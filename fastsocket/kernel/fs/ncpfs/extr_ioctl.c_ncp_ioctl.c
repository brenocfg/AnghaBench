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
struct TYPE_2__ {int /*<<< orphan*/  mnt; } ;
struct file {TYPE_1__ f_path; } ;

/* Variables and functions */
 int EACCES ; 
 int __ncp_ioctl (struct inode*,struct file*,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  mnt_drop_write (int /*<<< orphan*/ ) ; 
 scalar_t__ mnt_want_write (int /*<<< orphan*/ ) ; 
 scalar_t__ ncp_ioctl_need_write (unsigned int) ; 

int ncp_ioctl(struct inode *inode, struct file *filp,
	      unsigned int cmd, unsigned long arg)
{
	int ret;

	if (ncp_ioctl_need_write(cmd)) {
		/*
		 * inside the ioctl(), any failures which
		 * are because of file_permission() are
		 * -EACCESS, so it seems consistent to keep
		 *  that here.
		 */
		if (mnt_want_write(filp->f_path.mnt))
			return -EACCES;
	}
	ret = __ncp_ioctl(inode, filp, cmd, arg);
	if (ncp_ioctl_need_write(cmd))
		mnt_drop_write(filp->f_path.mnt);
	return ret;
}