#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tty_port {int flags; TYPE_3__* tty; int /*<<< orphan*/  blocked_open; int /*<<< orphan*/  count; int /*<<< orphan*/  open_wait; int /*<<< orphan*/  mutex; } ;
struct uart_state {struct tty_port port; struct uart_port* uart_port; } ;
struct uart_port {int /*<<< orphan*/  lock; TYPE_2__* ops; } ;
struct file {int f_flags; } ;
struct TYPE_6__ {int flags; TYPE_1__* termios; } ;
struct TYPE_5__ {unsigned int (* get_mctrl ) (struct uart_port*) ;int /*<<< orphan*/  (* enable_ms ) (struct uart_port*) ;} ;
struct TYPE_4__ {int c_cflag; } ;

/* Variables and functions */
 int ASYNC_INITIALIZED ; 
 int CBAUD ; 
 int CDTRDSR ; 
 int CLOCAL ; 
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int ERESTARTSYS ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 unsigned int TIOCM_CAR ; 
 int /*<<< orphan*/  TIOCM_DTR ; 
 int TTY_IO_ERROR ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct uart_port*) ; 
 unsigned int stub2 (struct uart_port*) ; 
 scalar_t__ tty_hung_up_p (struct file*) ; 
 int /*<<< orphan*/  uart_set_mctrl (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int
uart_block_til_ready(struct file *filp, struct uart_state *state)
{
	DECLARE_WAITQUEUE(wait, current);
	struct uart_port *uport = state->uart_port;
	struct tty_port *port = &state->port;
	unsigned int mctrl;

	port->blocked_open++;
	port->count--;

	add_wait_queue(&port->open_wait, &wait);
	while (1) {
		set_current_state(TASK_INTERRUPTIBLE);

		/*
		 * If we have been hung up, tell userspace/restart open.
		 */
		if (tty_hung_up_p(filp) || port->tty == NULL)
			break;

		/*
		 * If the port has been closed, tell userspace/restart open.
		 */
		if (!(port->flags & ASYNC_INITIALIZED))
			break;

		/*
		 * If non-blocking mode is set, or CLOCAL mode is set,
		 * we don't want to wait for the modem status lines to
		 * indicate that the port is ready.
		 *
		 * Also, if the port is not enabled/configured, we want
		 * to allow the open to succeed here.  Note that we will
		 * have set TTY_IO_ERROR for a non-existant port.
		 */
		if ((filp->f_flags & O_NONBLOCK) ||
		    (port->tty->termios->c_cflag & CLOCAL) ||
		    (port->tty->flags & (1 << TTY_IO_ERROR)))
			break;

		/*
		 * Set DTR to allow modem to know we're waiting.  Do
		 * not set RTS here - we want to make sure we catch
		 * the data from the modem.
		 */
		if (port->tty->termios->c_cflag & CBAUD &&
		    !(port->tty->termios->c_cflag & CDTRDSR))
			uart_set_mctrl(uport, TIOCM_DTR);

		/*
		 * and wait for the carrier to indicate that the
		 * modem is ready for us.
		 */
		spin_lock_irq(&uport->lock);
		uport->ops->enable_ms(uport);
		mctrl = uport->ops->get_mctrl(uport);
		spin_unlock_irq(&uport->lock);
		if (mctrl & TIOCM_CAR)
			break;

		mutex_unlock(&port->mutex);
		schedule();
		mutex_lock(&port->mutex);

		if (signal_pending(current))
			break;
	}
	set_current_state(TASK_RUNNING);
	remove_wait_queue(&port->open_wait, &wait);

	port->count++;
	port->blocked_open--;

	if (signal_pending(current))
		return -ERESTARTSYS;

	if (!port->tty || tty_hung_up_p(filp))
		return -EAGAIN;

	return 0;
}