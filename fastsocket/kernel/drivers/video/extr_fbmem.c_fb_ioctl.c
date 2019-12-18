#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; } ;
struct fb_info {int dummy; } ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 long do_fb_ioctl (struct fb_info*,unsigned int,unsigned long) ; 
 int iminor (struct inode*) ; 
 struct fb_info** registered_fb ; 

__attribute__((used)) static long fb_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	struct inode *inode = file->f_path.dentry->d_inode;
	int fbidx = iminor(inode);
	struct fb_info *info = registered_fb[fbidx];

	return do_fb_ioctl(info, cmd, arg);
}