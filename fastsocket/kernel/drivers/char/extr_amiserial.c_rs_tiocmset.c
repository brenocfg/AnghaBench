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
struct tty_struct {int flags; int /*<<< orphan*/  name; struct async_struct* driver_data; } ;
struct file {int dummy; } ;
struct async_struct {int /*<<< orphan*/  MCR; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  SER_DTR ; 
 int /*<<< orphan*/  SER_RTS ; 
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_RTS ; 
 int TTY_IO_ERROR ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  rtsdtr_ctrl (int /*<<< orphan*/ ) ; 
 scalar_t__ serial_paranoia_check (struct async_struct*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int rs_tiocmset(struct tty_struct *tty, struct file *file,
		       unsigned int set, unsigned int clear)
{
	struct async_struct * info = tty->driver_data;
	unsigned long flags;

	if (serial_paranoia_check(info, tty->name, "rs_ioctl"))
		return -ENODEV;
	if (tty->flags & (1 << TTY_IO_ERROR))
		return -EIO;

	local_irq_save(flags);
	if (set & TIOCM_RTS)
		info->MCR |= SER_RTS;
	if (set & TIOCM_DTR)
		info->MCR |= SER_DTR;
	if (clear & TIOCM_RTS)
		info->MCR &= ~SER_RTS;
	if (clear & TIOCM_DTR)
		info->MCR &= ~SER_DTR;
	rtsdtr_ctrl(info->MCR);
	local_irq_restore(flags);
	return 0;
}