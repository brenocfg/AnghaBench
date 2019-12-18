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

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  TIOCGWINSZ ; 
 int /*<<< orphan*/  TIOCSWINSZ ; 
 int _IOC_NR (unsigned long) ; 
 int sys_ioctl (int,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int hpux_ioctl_t(int fd, unsigned long cmd, unsigned long arg)
{
	int result = -EOPNOTSUPP;
	int nr = _IOC_NR(cmd);
	switch (nr) {
	case 106:
		result = sys_ioctl(fd, TIOCSWINSZ, arg);
		break;
	case 107:
		result = sys_ioctl(fd, TIOCGWINSZ, arg);
		break;
	}
	return result;
}