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
struct tty_struct {int flags; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  blocked_open; int /*<<< orphan*/  count; int /*<<< orphan*/  open_wait; int /*<<< orphan*/  close_wait; } ;
struct specialix_port {TYPE_1__ port; int /*<<< orphan*/  lock; int /*<<< orphan*/  MSVR; } ;
struct specialix_board {int /*<<< orphan*/  lock; } ;
struct file {int f_flags; } ;

/* Variables and functions */
 int ASYNC_CLOSING ; 
 int ASYNC_HUP_NOTIFY ; 
 int ASYNC_INITIALIZED ; 
 int ASYNC_NORMAL_ACTIVE ; 
 int /*<<< orphan*/  CD186x_CAR ; 
 int /*<<< orphan*/  CD186x_MSVR ; 
 scalar_t__ C_CLOCAL (struct tty_struct*) ; 
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int ERESTARTSYS ; 
 int MSVR_CD ; 
 int /*<<< orphan*/  MSVR_DTR ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int TTY_IO_ERROR ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 
 int /*<<< orphan*/  interruptible_sleep_on (int /*<<< orphan*/ *) ; 
 struct specialix_board* port_Board (struct specialix_port*) ; 
 int /*<<< orphan*/  port_No (struct specialix_port*) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ sx_crtscts (struct tty_struct*) ; 
 int sx_in (struct specialix_board*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_out (struct specialix_board*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tty_hung_up_p (struct file*) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int block_til_ready(struct tty_struct *tty, struct file *filp,
						struct specialix_port *port)
{
	DECLARE_WAITQUEUE(wait,  current);
	struct specialix_board *bp = port_Board(port);
	int    retval;
	int    do_clocal = 0;
	int    CD;
	unsigned long flags;

	func_enter();

	/*
	 * If the device is in the middle of being closed, then block
	 * until it's done, and then try again.
	 */
	if (tty_hung_up_p(filp) || port->port.flags & ASYNC_CLOSING) {
		interruptible_sleep_on(&port->port.close_wait);
		if (port->port.flags & ASYNC_HUP_NOTIFY) {
			func_exit();
			return -EAGAIN;
		} else {
			func_exit();
			return -ERESTARTSYS;
		}
	}

	/*
	 * If non-blocking mode is set, or the port is not enabled,
	 * then make the check up front and then exit.
	 */
	if ((filp->f_flags & O_NONBLOCK) ||
	    (tty->flags & (1 << TTY_IO_ERROR))) {
		port->port.flags |= ASYNC_NORMAL_ACTIVE;
		func_exit();
		return 0;
	}

	if (C_CLOCAL(tty))
		do_clocal = 1;

	/*
	 * Block waiting for the carrier detect and the line to become
	 * free (i.e., not in use by the callout).  While we are in
	 * this loop, info->count is dropped by one, so that
	 * rs_close() knows when to free things.  We restore it upon
	 * exit, either normal or abnormal.
	 */
	retval = 0;
	add_wait_queue(&port->port.open_wait, &wait);
	spin_lock_irqsave(&port->lock, flags);
	if (!tty_hung_up_p(filp))
		port->port.count--;
	spin_unlock_irqrestore(&port->lock, flags);
	port->port.blocked_open++;
	while (1) {
		spin_lock_irqsave(&bp->lock, flags);
		sx_out(bp, CD186x_CAR, port_No(port));
		CD = sx_in(bp, CD186x_MSVR) & MSVR_CD;
		if (sx_crtscts(tty)) {
			/* Activate RTS */
			port->MSVR |= MSVR_DTR;		/* WTF? */
			sx_out(bp, CD186x_MSVR, port->MSVR);
		} else {
			/* Activate DTR */
			port->MSVR |= MSVR_DTR;
			sx_out(bp, CD186x_MSVR, port->MSVR);
		}
		spin_unlock_irqrestore(&bp->lock, flags);
		set_current_state(TASK_INTERRUPTIBLE);
		if (tty_hung_up_p(filp) ||
		    !(port->port.flags & ASYNC_INITIALIZED)) {
			if (port->port.flags & ASYNC_HUP_NOTIFY)
				retval = -EAGAIN;
			else
				retval = -ERESTARTSYS;
			break;
		}
		if (!(port->port.flags & ASYNC_CLOSING) &&
		    (do_clocal || CD))
			break;
		if (signal_pending(current)) {
			retval = -ERESTARTSYS;
			break;
		}
		schedule();
	}

	set_current_state(TASK_RUNNING);
	remove_wait_queue(&port->port.open_wait, &wait);
	spin_lock_irqsave(&port->lock, flags);
	if (!tty_hung_up_p(filp))
		port->port.count++;
	port->port.blocked_open--;
	spin_unlock_irqrestore(&port->lock, flags);
	if (retval) {
		func_exit();
		return retval;
	}

	port->port.flags |= ASYNC_NORMAL_ACTIVE;
	func_exit();
	return 0;
}