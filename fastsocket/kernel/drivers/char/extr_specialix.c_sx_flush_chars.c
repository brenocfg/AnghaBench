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
struct tty_struct {scalar_t__ hw_stopped; scalar_t__ stopped; int /*<<< orphan*/  name; struct specialix_port* driver_data; } ;
struct specialix_port {scalar_t__ xmit_cnt; int /*<<< orphan*/  IER; int /*<<< orphan*/  xmit_buf; } ;
struct specialix_board {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CD186x_CAR ; 
 int /*<<< orphan*/  CD186x_IER ; 
 int /*<<< orphan*/  IER_TXRDY ; 
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 
 struct specialix_board* port_Board (struct specialix_port*) ; 
 int /*<<< orphan*/  port_No (struct specialix_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sx_out (struct specialix_board*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sx_paranoia_check (struct specialix_port*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void sx_flush_chars(struct tty_struct *tty)
{
	struct specialix_port *port = tty->driver_data;
	unsigned long flags;
	struct specialix_board  *bp = port_Board(port);

	func_enter();

	if (sx_paranoia_check(port, tty->name, "sx_flush_chars")) {
		func_exit();
		return;
	}
	if (port->xmit_cnt <= 0 || tty->stopped || tty->hw_stopped ||
	    !port->xmit_buf) {
		func_exit();
		return;
	}
	spin_lock_irqsave(&bp->lock, flags);
	port->IER |= IER_TXRDY;
	sx_out(port_Board(port), CD186x_CAR, port_No(port));
	sx_out(port_Board(port), CD186x_IER, port->IER);
	spin_unlock_irqrestore(&bp->lock, flags);

	func_exit();
}