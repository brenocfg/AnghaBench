#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct file {int dummy; } ;

/* Variables and functions */
 int ENOIOCTLCMD ; 
#define  WIOCGSTAT 130 
#define  WIOCSTART 129 
#define  WIOCSTOP 128 
 int cpwd_ioctl (struct file*,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static long cpwd_compat_ioctl(struct file *file, unsigned int cmd,
			      unsigned long arg)
{
	int rval = -ENOIOCTLCMD;

	switch (cmd) {
	/* solaris ioctls are specific to this driver */
	case WIOCSTART:
	case WIOCSTOP:
	case WIOCGSTAT:
		lock_kernel();
		rval = cpwd_ioctl(file, cmd, arg);
		unlock_kernel();
		break;

	/* everything else is handled by the generic compat layer */
	default:
		break;
	}

	return rval;
}