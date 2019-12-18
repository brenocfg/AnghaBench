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
struct tty_struct {struct specialix_port* driver_data; } ;
struct specialix_port {int break_length; int /*<<< orphan*/  lock; int /*<<< orphan*/  IER; int /*<<< orphan*/  COR2; } ;
struct specialix_board {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCR_CORCHG2 ; 
 int /*<<< orphan*/  CD186x_CAR ; 
 int /*<<< orphan*/  CD186x_CCR ; 
 int /*<<< orphan*/  CD186x_COR2 ; 
 int /*<<< orphan*/  CD186x_IER ; 
 int /*<<< orphan*/  COR2_ETC ; 
 int EOPNOTSUPP ; 
 int HZ ; 
 int /*<<< orphan*/  IER_TXRDY ; 
 int SPECIALIX_TPS ; 
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 
 struct specialix_board* port_Board (struct specialix_port*) ; 
 int /*<<< orphan*/  port_No (struct specialix_port*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sx_out (struct specialix_board*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_wait_CCR (struct specialix_board*) ; 

__attribute__((used)) static int sx_send_break(struct tty_struct *tty, int length)
{
	struct specialix_port *port = tty->driver_data;
	struct specialix_board *bp = port_Board(port);
	unsigned long flags;

	func_enter();
	if (length == 0 || length == -1)
		return -EOPNOTSUPP;

	spin_lock_irqsave(&port->lock, flags);
	port->break_length = SPECIALIX_TPS / HZ * length;
	port->COR2 |= COR2_ETC;
	port->IER  |= IER_TXRDY;
	spin_lock(&bp->lock);
	sx_out(bp, CD186x_CAR, port_No(port));
	sx_out(bp, CD186x_COR2, port->COR2);
	sx_out(bp, CD186x_IER, port->IER);
	spin_unlock(&bp->lock);
	spin_unlock_irqrestore(&port->lock, flags);
	sx_wait_CCR(bp);
	spin_lock_irqsave(&bp->lock, flags);
	sx_out(bp, CD186x_CCR, CCR_CORCHG2);
	spin_unlock_irqrestore(&bp->lock, flags);
	sx_wait_CCR(bp);

	func_exit();
	return 0;
}