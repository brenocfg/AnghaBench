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
struct tty_struct {int flags; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ENOIOCTLCMD ; 
 int TTY_IO_ERROR ; 

__attribute__((used)) static int tty3215_ioctl(struct tty_struct *tty, struct file * file,
			 unsigned int cmd, unsigned long arg)
{
	if (tty->flags & (1 << TTY_IO_ERROR))
		return -EIO;

	switch (cmd) {
	default:
		return -ENOIOCTLCMD;
	}
	return 0;
}