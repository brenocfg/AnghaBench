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
struct specialix_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  MSVR; } ;
struct specialix_board {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCR_SSCH1 ; 
 int /*<<< orphan*/  CD186x_CAR ; 
 int /*<<< orphan*/  CD186x_CCR ; 
 int /*<<< orphan*/  CD186x_MSVR ; 
 scalar_t__ I_IXOFF (struct tty_struct*) ; 
 int /*<<< orphan*/  MSVR_DTR ; 
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 
 struct specialix_board* port_Board (struct specialix_port*) ; 
 int /*<<< orphan*/  port_No (struct specialix_port*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ sx_crtscts (struct tty_struct*) ; 
 int /*<<< orphan*/  sx_out (struct specialix_board*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sx_paranoia_check (struct specialix_port*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sx_wait_CCR (struct specialix_board*) ; 

__attribute__((used)) static void sx_unthrottle(struct tty_struct *tty)
{
	struct specialix_port *port = tty->driver_data;
	struct specialix_board *bp;
	unsigned long flags;

	func_enter();

	if (sx_paranoia_check(port, tty->name, "sx_unthrottle")) {
		func_exit();
		return;
	}

	bp = port_Board(port);

	spin_lock_irqsave(&port->lock, flags);
	/* XXXX Use DTR INSTEAD???? */
	if (sx_crtscts(tty))
		port->MSVR |= MSVR_DTR;
	/* Else clause: see remark in "sx_throttle"... */
	spin_lock(&bp->lock);
	sx_out(bp, CD186x_CAR, port_No(port));
	spin_unlock(&bp->lock);
	if (I_IXOFF(tty)) {
		spin_unlock_irqrestore(&port->lock, flags);
		sx_wait_CCR(bp);
		spin_lock_irqsave(&bp->lock, flags);
		sx_out(bp, CD186x_CCR, CCR_SSCH1);
		spin_unlock_irqrestore(&bp->lock, flags);
		sx_wait_CCR(bp);
		spin_lock_irqsave(&port->lock, flags);
	}
	spin_lock(&bp->lock);
	sx_out(bp, CD186x_MSVR, port->MSVR);
	spin_unlock(&bp->lock);
	spin_unlock_irqrestore(&port->lock, flags);

	func_exit();
}