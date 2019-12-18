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
typedef  int /*<<< orphan*/  wait_queue_t ;
struct tty_struct {int /*<<< orphan*/  write_wait; } ;
struct edgeport_port {int baud_rate; TYPE_2__* port; int /*<<< orphan*/  ep_lock; int /*<<< orphan*/  ep_out_buf; } ;
struct TYPE_4__ {TYPE_1__* serial; int /*<<< orphan*/  port; } ;
struct TYPE_3__ {int /*<<< orphan*/  interface; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int,int) ; 
 int EDGE_CLOSING_WAIT ; 
 int HZ ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  edge_buf_clear (int /*<<< orphan*/ ) ; 
 scalar_t__ edge_buf_data_avail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int max (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned long schedule_timeout (unsigned long) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_port_tty_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx_active (struct edgeport_port*) ; 
 scalar_t__ usb_get_intfdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void chase_port(struct edgeport_port *port, unsigned long timeout,
								int flush)
{
	int baud_rate;
	struct tty_struct *tty = tty_port_tty_get(&port->port->port);
	wait_queue_t wait;
	unsigned long flags;

	if (!tty)
		return;

	if (!timeout)
		timeout = (HZ * EDGE_CLOSING_WAIT)/100;

	/* wait for data to drain from the buffer */
	spin_lock_irqsave(&port->ep_lock, flags);
	init_waitqueue_entry(&wait, current);
	add_wait_queue(&tty->write_wait, &wait);
	for (;;) {
		set_current_state(TASK_INTERRUPTIBLE);
		if (edge_buf_data_avail(port->ep_out_buf) == 0
		|| timeout == 0 || signal_pending(current)
		|| !usb_get_intfdata(port->port->serial->interface))
			/* disconnect */
			break;
		spin_unlock_irqrestore(&port->ep_lock, flags);
		timeout = schedule_timeout(timeout);
		spin_lock_irqsave(&port->ep_lock, flags);
	}
	set_current_state(TASK_RUNNING);
	remove_wait_queue(&tty->write_wait, &wait);
	if (flush)
		edge_buf_clear(port->ep_out_buf);
	spin_unlock_irqrestore(&port->ep_lock, flags);
	tty_kref_put(tty);

	/* wait for data to drain from the device */
	timeout += jiffies;
	while ((long)(jiffies - timeout) < 0 && !signal_pending(current)
	&& usb_get_intfdata(port->port->serial->interface)) {
		/* not disconnected */
		if (!tx_active(port))
			break;
		msleep(10);
	}

	/* disconnected */
	if (!usb_get_intfdata(port->port->serial->interface))
		return;

	/* wait one more character time, based on baud rate */
	/* (tx_active doesn't seem to wait for the last byte) */
	baud_rate = port->baud_rate;
	if (baud_rate == 0)
		baud_rate = 50;
	msleep(max(1, DIV_ROUND_UP(10000, baud_rate)));
}