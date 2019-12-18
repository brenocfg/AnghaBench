#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flags; TYPE_2__* tty; } ;
struct gs_port {unsigned char* xmit_buf; int /*<<< orphan*/  driver_lock; TYPE_1__ port; scalar_t__ xmit_tail; scalar_t__ xmit_head; scalar_t__ xmit_cnt; int /*<<< orphan*/  port_write_mutex; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ASYNC_INITIALIZED ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GS_TX_INTEN ; 
 int /*<<< orphan*/  TTY_IO_ERROR ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 
 unsigned long get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_set_termios (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int gs_init_port(struct gs_port *port)
{
	unsigned long flags;

	func_enter ();

	if (port->port.flags & ASYNC_INITIALIZED) {
		func_exit ();
		return 0;
	}
	if (!port->xmit_buf) {
		/* We may sleep in get_zeroed_page() */
		unsigned long tmp;

		tmp = get_zeroed_page(GFP_KERNEL);
		spin_lock_irqsave (&port->driver_lock, flags);
		if (port->xmit_buf) 
			free_page (tmp);
		else
			port->xmit_buf = (unsigned char *) tmp;
		spin_unlock_irqrestore(&port->driver_lock, flags);
		if (!port->xmit_buf) {
			func_exit ();
			return -ENOMEM;
		}
	}

	spin_lock_irqsave (&port->driver_lock, flags);
	if (port->port.tty)
		clear_bit(TTY_IO_ERROR, &port->port.tty->flags);
	mutex_init(&port->port_write_mutex);
	port->xmit_cnt = port->xmit_head = port->xmit_tail = 0;
	spin_unlock_irqrestore(&port->driver_lock, flags);
	gs_set_termios(port->port.tty, NULL);
	spin_lock_irqsave (&port->driver_lock, flags);
	port->port.flags |= ASYNC_INITIALIZED;
	port->port.flags &= ~GS_TX_INTEN;

	spin_unlock_irqrestore(&port->driver_lock, flags);
	func_exit ();
	return 0;
}