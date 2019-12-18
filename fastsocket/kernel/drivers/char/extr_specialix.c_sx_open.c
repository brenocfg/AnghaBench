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
struct tty_struct {struct specialix_port* driver_data; int /*<<< orphan*/  name; int /*<<< orphan*/  index; } ;
struct TYPE_2__ {struct tty_struct* tty; int /*<<< orphan*/  count; } ;
struct specialix_port {TYPE_1__ port; scalar_t__* hits; scalar_t__ overrun; } ;
struct specialix_board {int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  count; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int SX_BOARD (int /*<<< orphan*/ ) ; 
 int SX_BOARD_PRESENT ; 
 int /*<<< orphan*/  SX_DEBUG_OPEN ; 
 int SX_NBOARD ; 
 int SX_NPORT ; 
 int SX_PORT (int /*<<< orphan*/ ) ; 
 int block_til_ready (struct tty_struct*,struct file*,struct specialix_port*) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,char*,int,struct specialix_board*,struct specialix_port*,int) ; 
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct specialix_board* sx_board ; 
 scalar_t__ sx_paranoia_check (struct specialix_port*,int /*<<< orphan*/ ,char*) ; 
 struct specialix_port* sx_port ; 
 int sx_setup_board (struct specialix_board*) ; 
 int sx_setup_port (struct specialix_board*,struct specialix_port*) ; 

__attribute__((used)) static int sx_open(struct tty_struct *tty, struct file *filp)
{
	int board;
	int error;
	struct specialix_port *port;
	struct specialix_board *bp;
	int i;
	unsigned long flags;

	func_enter();

	board = SX_BOARD(tty->index);

	if (board >= SX_NBOARD || !(sx_board[board].flags & SX_BOARD_PRESENT)) {
		func_exit();
		return -ENODEV;
	}

	bp = &sx_board[board];
	port = sx_port + board * SX_NPORT + SX_PORT(tty->index);
	port->overrun = 0;
	for (i = 0; i < 10; i++)
		port->hits[i] = 0;

	dprintk(SX_DEBUG_OPEN,
			"Board = %d, bp = %p, port = %p, portno = %d.\n",
				 board, bp, port, SX_PORT(tty->index));

	if (sx_paranoia_check(port, tty->name, "sx_open")) {
		func_enter();
		return -ENODEV;
	}

	error = sx_setup_board(bp);
	if (error) {
		func_exit();
		return error;
	}

	spin_lock_irqsave(&bp->lock, flags);
	port->port.count++;
	bp->count++;
	tty->driver_data = port;
	port->port.tty = tty;
	spin_unlock_irqrestore(&bp->lock, flags);

	error = sx_setup_port(bp, port);
	if (error) {
		func_enter();
		return error;
	}

	error = block_til_ready(tty, filp, port);
	if (error) {
		func_enter();
		return error;
	}

	func_exit();
	return 0;
}