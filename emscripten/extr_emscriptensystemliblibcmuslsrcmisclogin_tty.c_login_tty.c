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
 int /*<<< orphan*/  TIOCSCTTY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  setsid () ; 

int login_tty(int fd)
{
	setsid();
	if (ioctl(fd, TIOCSCTTY, (char *)0)) return -1;
	dup2(fd, 0);
	dup2(fd, 1);
	dup2(fd, 2);
	if (fd>2) close(fd);
	return 0;
}