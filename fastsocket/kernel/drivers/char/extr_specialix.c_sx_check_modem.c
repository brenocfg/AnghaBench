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
struct tty_struct {int hw_stopped; } ;
struct TYPE_2__ {int /*<<< orphan*/  open_wait; struct tty_struct* tty; } ;
struct specialix_port {scalar_t__ xmit_cnt; scalar_t__ wakeup_chars; int /*<<< orphan*/  IER; TYPE_1__ port; } ;
struct specialix_board {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CD186x_IER ; 
 int /*<<< orphan*/  CD186x_MCR ; 
 int /*<<< orphan*/  CD186x_MSVR ; 
 int /*<<< orphan*/  IER_TXRDY ; 
 unsigned char MCR_CDCHG ; 
 unsigned char MCR_CTSCHG ; 
 unsigned char MCR_DSSXHG ; 
 int MSVR_CD ; 
 int MSVR_CTS ; 
 int MSVR_DSR ; 
 int /*<<< orphan*/  SX_DEBUG_SIGNALS ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,char*) ; 
 struct specialix_port* sx_get_port (struct specialix_board*,char*) ; 
 int sx_in (struct specialix_board*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_out (struct specialix_board*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_hangup (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_wakeup (struct tty_struct*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sx_check_modem(struct specialix_board *bp)
{
	struct specialix_port *port;
	struct tty_struct *tty;
	unsigned char mcr;
	int msvr_cd;

	dprintk(SX_DEBUG_SIGNALS, "Modem intr. ");
	port = sx_get_port(bp, "Modem");
	if (port == NULL)
		return;

	tty = port->port.tty;

	mcr = sx_in(bp, CD186x_MCR);

	if ((mcr & MCR_CDCHG)) {
		dprintk(SX_DEBUG_SIGNALS, "CD just changed... ");
		msvr_cd = sx_in(bp, CD186x_MSVR) & MSVR_CD;
		if (msvr_cd) {
			dprintk(SX_DEBUG_SIGNALS, "Waking up guys in open.\n");
			wake_up_interruptible(&port->port.open_wait);
		} else {
			dprintk(SX_DEBUG_SIGNALS, "Sending HUP.\n");
			tty_hangup(tty);
		}
	}

#ifdef SPECIALIX_BRAIN_DAMAGED_CTS
	if (mcr & MCR_CTSCHG) {
		if (sx_in(bp, CD186x_MSVR) & MSVR_CTS) {
			tty->hw_stopped = 0;
			port->IER |= IER_TXRDY;
			if (port->xmit_cnt <= port->wakeup_chars)
				tty_wakeup(tty);
		} else {
			tty->hw_stopped = 1;
			port->IER &= ~IER_TXRDY;
		}
		sx_out(bp, CD186x_IER, port->IER);
	}
	if (mcr & MCR_DSSXHG) {
		if (sx_in(bp, CD186x_MSVR) & MSVR_DSR) {
			tty->hw_stopped = 0;
			port->IER |= IER_TXRDY;
			if (port->xmit_cnt <= port->wakeup_chars)
				tty_wakeup(tty);
		} else {
			tty->hw_stopped = 1;
			port->IER &= ~IER_TXRDY;
		}
		sx_out(bp, CD186x_IER, port->IER);
	}
#endif /* SPECIALIX_BRAIN_DAMAGED_CTS */

	/* Clear change bits */
	sx_out(bp, CD186x_MCR, 0);
}