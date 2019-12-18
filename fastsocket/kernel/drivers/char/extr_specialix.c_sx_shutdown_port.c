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
struct tty_struct {int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int flags; struct tty_struct* tty; } ;
struct specialix_port {TYPE_1__ port; scalar_t__ IER; int /*<<< orphan*/ * xmit_buf; int /*<<< orphan*/ * hits; int /*<<< orphan*/  overrun; } ;
struct specialix_board {int /*<<< orphan*/  count; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ASYNC_INITIALIZED ; 
 scalar_t__ CCR_SOFTRESET ; 
 int /*<<< orphan*/  CD186x_CAR ; 
 int /*<<< orphan*/  CD186x_CCR ; 
 int /*<<< orphan*/  CD186x_IER ; 
 int /*<<< orphan*/  CD186x_MSVDTR ; 
 scalar_t__ C_HUPCL (struct tty_struct*) ; 
 int SX_DEBUG_FIFO ; 
 int /*<<< orphan*/  TTY_IO_ERROR ; 
 int /*<<< orphan*/  board_No (struct specialix_board*) ; 
 int /*<<< orphan*/  dprintk (int,char*,...) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 
 scalar_t__ port_No (struct specialix_port*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int sx_debug ; 
 int /*<<< orphan*/  sx_out (struct specialix_board*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sx_shutdown_board (struct specialix_board*) ; 
 int /*<<< orphan*/  sx_wait_CCR (struct specialix_board*) ; 

__attribute__((used)) static void sx_shutdown_port(struct specialix_board *bp,
						struct specialix_port *port)
{
	struct tty_struct *tty;
	int i;
	unsigned long flags;

	func_enter();

	if (!(port->port.flags & ASYNC_INITIALIZED)) {
		func_exit();
		return;
	}

	if (sx_debug & SX_DEBUG_FIFO) {
		dprintk(SX_DEBUG_FIFO,
			"sx%d: port %d: %ld overruns, FIFO hits [ ",
				board_No(bp), port_No(port), port->overrun);
		for (i = 0; i < 10; i++)
			dprintk(SX_DEBUG_FIFO, "%ld ", port->hits[i]);
		dprintk(SX_DEBUG_FIFO, "].\n");
	}

	if (port->xmit_buf) {
		free_page((unsigned long) port->xmit_buf);
		port->xmit_buf = NULL;
	}

	/* Select port */
	spin_lock_irqsave(&bp->lock, flags);
	sx_out(bp, CD186x_CAR, port_No(port));

	tty = port->port.tty;
	if (tty == NULL || C_HUPCL(tty)) {
		/* Drop DTR */
		sx_out(bp, CD186x_MSVDTR, 0);
	}
	spin_unlock_irqrestore(&bp->lock, flags);
	/* Reset port */
	sx_wait_CCR(bp);
	spin_lock_irqsave(&bp->lock, flags);
	sx_out(bp, CD186x_CCR, CCR_SOFTRESET);
	/* Disable all interrupts from this port */
	port->IER = 0;
	sx_out(bp, CD186x_IER, port->IER);
	spin_unlock_irqrestore(&bp->lock, flags);
	if (tty)
		set_bit(TTY_IO_ERROR, &tty->flags);
	port->port.flags &= ~ASYNC_INITIALIZED;

	if (!bp->count)
		sx_shutdown_board(bp);
	func_exit();
}