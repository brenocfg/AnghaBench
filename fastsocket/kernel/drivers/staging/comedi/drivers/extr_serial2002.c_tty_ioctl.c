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
struct file {TYPE_2__* f_dentry; TYPE_1__* f_op; } ;
struct TYPE_4__ {int /*<<< orphan*/  d_inode; } ;
struct TYPE_3__ {long (* unlocked_ioctl ) (struct file*,unsigned int,unsigned long) ;long (* ioctl ) (int /*<<< orphan*/ ,struct file*,unsigned int,unsigned long) ;} ;

/* Variables and functions */
 long ENOSYS ; 
 long stub1 (struct file*,unsigned int,unsigned long) ; 
 long stub2 (int /*<<< orphan*/ ,struct file*,unsigned int,unsigned long) ; 

__attribute__((used)) static long tty_ioctl(struct file *f, unsigned op, unsigned long param)
{
#ifdef HAVE_UNLOCKED_IOCTL
	if (f->f_op->unlocked_ioctl) {
		return f->f_op->unlocked_ioctl(f, op, param);
	}
#endif
	if (f->f_op->ioctl) {
		return f->f_op->ioctl(f->f_dentry->d_inode, f, op, param);
	}
	return -ENOSYS;
}