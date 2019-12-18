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
struct tty_struct {int index; int /*<<< orphan*/  termios; struct moxa_port* driver_data; } ;
struct TYPE_2__ {scalar_t__ count; int flags; } ;
struct moxa_port {scalar_t__ type; TYPE_1__ port; scalar_t__ statusflags; } ;
struct moxa_board_conf {int numPorts; struct moxa_port* ports; int /*<<< orphan*/  ready; } ;
struct file {int f_flags; } ;

/* Variables and functions */
 int ASYNC_INITIALIZED ; 
 int ASYNC_NORMAL_ACTIVE ; 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  C_CLOCAL (struct tty_struct*) ; 
 int ENODEV ; 
 int EPERM ; 
 int ERESTARTSYS ; 
 int MAX_PORTS ; 
 int MAX_PORTS_PER_BOARD ; 
 int /*<<< orphan*/  MoxaPortEnable (struct moxa_port*) ; 
 int /*<<< orphan*/  MoxaPortLineCtrl (struct moxa_port*,int,int) ; 
 int /*<<< orphan*/  MoxaSetFifo (struct moxa_port*,int) ; 
 int O_NONBLOCK ; 
 scalar_t__ PORT_16550A ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 int moxa_block_till_ready (struct tty_struct*,struct file*,struct moxa_port*) ; 
 struct moxa_board_conf* moxa_boards ; 
 int /*<<< orphan*/  moxa_close_port (struct tty_struct*) ; 
 int /*<<< orphan*/  moxa_openlock ; 
 int /*<<< orphan*/  moxa_set_tty_param (struct tty_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_tty_set (TYPE_1__*,struct tty_struct*) ; 

__attribute__((used)) static int moxa_open(struct tty_struct *tty, struct file *filp)
{
	struct moxa_board_conf *brd;
	struct moxa_port *ch;
	int port;
	int retval;

	port = tty->index;
	if (port == MAX_PORTS) {
		return capable(CAP_SYS_ADMIN) ? 0 : -EPERM;
	}
	if (mutex_lock_interruptible(&moxa_openlock))
		return -ERESTARTSYS;
	brd = &moxa_boards[port / MAX_PORTS_PER_BOARD];
	if (!brd->ready) {
		mutex_unlock(&moxa_openlock);
		return -ENODEV;
	}

	if (port % MAX_PORTS_PER_BOARD >= brd->numPorts) {
		mutex_unlock(&moxa_openlock);
		return -ENODEV;
	}

	ch = &brd->ports[port % MAX_PORTS_PER_BOARD];
	ch->port.count++;
	tty->driver_data = ch;
	tty_port_tty_set(&ch->port, tty);
	if (!(ch->port.flags & ASYNC_INITIALIZED)) {
		ch->statusflags = 0;
		moxa_set_tty_param(tty, tty->termios);
		MoxaPortLineCtrl(ch, 1, 1);
		MoxaPortEnable(ch);
		MoxaSetFifo(ch, ch->type == PORT_16550A);
		ch->port.flags |= ASYNC_INITIALIZED;
	}
	mutex_unlock(&moxa_openlock);

	retval = 0;
	if (!(filp->f_flags & O_NONBLOCK) && !C_CLOCAL(tty))
		retval = moxa_block_till_ready(tty, filp, ch);
	mutex_lock(&moxa_openlock);
	if (retval) {
		if (ch->port.count) /* 0 means already hung up... */
			if (--ch->port.count == 0)
				moxa_close_port(tty);
	} else
		ch->port.flags |= ASYNC_NORMAL_ACTIVE;
	mutex_unlock(&moxa_openlock);

	return retval;
}