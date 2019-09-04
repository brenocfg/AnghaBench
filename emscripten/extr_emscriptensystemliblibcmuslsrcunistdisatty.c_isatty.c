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
struct winsize {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_ioctl ; 
 int /*<<< orphan*/  TIOCGWINSZ ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct winsize*) ; 

int isatty(int fd)
{
	struct winsize wsz;
	return !syscall(SYS_ioctl, fd, TIOCGWINSZ, &wsz);
}