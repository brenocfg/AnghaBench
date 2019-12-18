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
struct tty_struct {int flags; struct tty3270* driver_data; } ;
struct tty3270 {int /*<<< orphan*/  kbd; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int TTY_IO_ERROR ; 
 int kbd_ioctl (int /*<<< orphan*/ ,struct file*,unsigned int,unsigned long) ; 

__attribute__((used)) static int
tty3270_ioctl(struct tty_struct *tty, struct file *file,
	      unsigned int cmd, unsigned long arg)
{
	struct tty3270 *tp;

	tp = tty->driver_data;
	if (!tp)
		return -ENODEV;
	if (tty->flags & (1 << TTY_IO_ERROR))
		return -EIO;
	return kbd_ioctl(tp->kbd, file, cmd, arg);
}