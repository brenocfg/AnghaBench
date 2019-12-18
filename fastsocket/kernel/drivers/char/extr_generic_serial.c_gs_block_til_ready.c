#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int flags; } ;
struct tty_port {int flags; int blocked_open; int /*<<< orphan*/  lock; int /*<<< orphan*/  count; int /*<<< orphan*/  open_wait; int /*<<< orphan*/  close_wait; struct tty_struct* tty; } ;
struct gs_port {struct tty_port port; } ;
struct file {int f_flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  blocked; } ;

/* Variables and functions */
 int ASYNC_CLOSING ; 
 int ASYNC_HUP_NOTIFY ; 
 int ASYNC_INITIALIZED ; 
 int ASYNC_NORMAL_ACTIVE ; 
 scalar_t__ C_CLOCAL (struct tty_struct*) ; 
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int EAGAIN ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GS_DEBUG_BTR ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int TTY_IO_ERROR ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 
 int /*<<< orphan*/  gs_dprintk (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  interruptible_sleep_on (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ tty_hung_up_p (struct file*) ; 
 int tty_port_carrier_raised (struct tty_port*) ; 
 int /*<<< orphan*/  wait ; 

int gs_block_til_ready(void *port_, struct file * filp)
{
	struct gs_port *gp = port_;
	struct tty_port *port = &gp->port;
	DECLARE_WAITQUEUE(wait, current);
	int    retval;
	int    do_clocal = 0;
	int    CD;
	struct tty_struct *tty;
	unsigned long flags;

	func_enter ();

	if (!port) return 0;

	tty = port->tty;

	gs_dprintk (GS_DEBUG_BTR, "Entering gs_block_till_ready.\n"); 
	/*
	 * If the device is in the middle of being closed, then block
	 * until it's done, and then try again.
	 */
	if (tty_hung_up_p(filp) || port->flags & ASYNC_CLOSING) {
		interruptible_sleep_on(&port->close_wait);
		if (port->flags & ASYNC_HUP_NOTIFY)
			return -EAGAIN;
		else
			return -ERESTARTSYS;
	}

	gs_dprintk (GS_DEBUG_BTR, "after hung up\n"); 

	/*
	 * If non-blocking mode is set, or the port is not enabled,
	 * then make the check up front and then exit.
	 */
	if ((filp->f_flags & O_NONBLOCK) ||
	    (tty->flags & (1 << TTY_IO_ERROR))) {
		port->flags |= ASYNC_NORMAL_ACTIVE;
		return 0;
	}

	gs_dprintk (GS_DEBUG_BTR, "after nonblock\n"); 
 
	if (C_CLOCAL(tty))
		do_clocal = 1;

	/*
	 * Block waiting for the carrier detect and the line to become
	 * free (i.e., not in use by the callout).  While we are in
	 * this loop, port->count is dropped by one, so that
	 * rs_close() knows when to free things.  We restore it upon
	 * exit, either normal or abnormal.
	 */
	retval = 0;

	add_wait_queue(&port->open_wait, &wait);

	gs_dprintk (GS_DEBUG_BTR, "after add waitq.\n"); 
	spin_lock_irqsave(&port->lock, flags);
	if (!tty_hung_up_p(filp)) {
		port->count--;
	}
	port->blocked_open++;
	spin_unlock_irqrestore(&port->lock, flags);
	while (1) {
		CD = tty_port_carrier_raised(port);
		gs_dprintk (GS_DEBUG_BTR, "CD is now %d.\n", CD);
		set_current_state (TASK_INTERRUPTIBLE);
		if (tty_hung_up_p(filp) ||
		    !(port->flags & ASYNC_INITIALIZED)) {
			if (port->flags & ASYNC_HUP_NOTIFY)
				retval = -EAGAIN;
			else
				retval = -ERESTARTSYS;
			break;
		}
		if (!(port->flags & ASYNC_CLOSING) &&
		    (do_clocal || CD))
			break;
		gs_dprintk (GS_DEBUG_BTR, "signal_pending is now: %d (%lx)\n", 
		(int)signal_pending (current), *(long*)(&current->blocked)); 
		if (signal_pending(current)) {
			retval = -ERESTARTSYS;
			break;
		}
		schedule();
	}
	gs_dprintk (GS_DEBUG_BTR, "Got out of the loop. (%d)\n",
		    port->blocked_open);
	set_current_state (TASK_RUNNING);
	remove_wait_queue(&port->open_wait, &wait);
	
	spin_lock_irqsave(&port->lock, flags);
	if (!tty_hung_up_p(filp)) {
		port->count++;
	}
	port->blocked_open--;
	if (retval == 0)
        	port->flags |= ASYNC_NORMAL_ACTIVE;
	spin_unlock_irqrestore(&port->lock, flags);
	func_exit ();
	return retval;
}