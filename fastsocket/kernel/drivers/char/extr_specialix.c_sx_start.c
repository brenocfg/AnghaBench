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
struct tty_struct {int /*<<< orphan*/  name; struct specialix_port* driver_data; } ;
struct specialix_port {int IER; int /*<<< orphan*/  lock; scalar_t__ xmit_buf; scalar_t__ xmit_cnt; } ;
struct specialix_board {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CD186x_CAR ; 
 int /*<<< orphan*/  CD186x_IER ; 
 int IER_TXRDY ; 
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 
 struct specialix_board* port_Board (struct specialix_port*) ; 
 int port_No (struct specialix_port*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sx_out (struct specialix_board*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sx_paranoia_check (struct specialix_port*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void sx_start(struct tty_struct *tty)
{
	struct specialix_port *port = tty->driver_data;
	struct specialix_board *bp;
	unsigned long flags;

	func_enter();

	if (sx_paranoia_check(port, tty->name, "sx_start")) {
		func_exit();
		return;
	}

	bp = port_Board(port);

	spin_lock_irqsave(&port->lock, flags);
	if (port->xmit_cnt && port->xmit_buf && !(port->IER & IER_TXRDY)) {
		port->IER |= IER_TXRDY;
		spin_lock(&bp->lock);
		sx_out(bp, CD186x_CAR, port_No(port));
		sx_out(bp, CD186x_IER, port->IER);
		spin_unlock(&bp->lock);
	}
	spin_unlock_irqrestore(&port->lock, flags);

	func_exit();
}