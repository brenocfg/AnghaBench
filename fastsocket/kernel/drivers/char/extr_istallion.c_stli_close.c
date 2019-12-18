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
struct tty_struct {int /*<<< orphan*/  flags; TYPE_1__* termios; struct stliport* driver_data; } ;
struct tty_port {int /*<<< orphan*/  flags; } ;
struct stliport {scalar_t__ closing_wait; size_t brdnr; int /*<<< orphan*/  state; int /*<<< orphan*/  asig; struct tty_port port; } ;
struct stlibrd {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  asysigs_t ;
struct TYPE_2__ {int c_cflag; } ;

/* Variables and functions */
 scalar_t__ ASYNC_CLOSING_WAIT_NONE ; 
 int /*<<< orphan*/  ASYNC_INITIALIZED ; 
 int /*<<< orphan*/  A_SETSIGNALS ; 
 int HUPCL ; 
 int /*<<< orphan*/  ST_CMDING ; 
 int /*<<< orphan*/  ST_DOFLUSHRX ; 
 int /*<<< orphan*/  ST_DOSIGS ; 
 int /*<<< orphan*/  ST_RXSTOP ; 
 int /*<<< orphan*/  ST_TXBUSY ; 
 int /*<<< orphan*/  TTY_IO_ERROR ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct stlibrd** stli_brds ; 
 int /*<<< orphan*/  stli_flushbuffer (struct tty_struct*) ; 
 int /*<<< orphan*/  stli_flushchars (struct tty_struct*) ; 
 int /*<<< orphan*/  stli_lock ; 
 int /*<<< orphan*/  stli_mkasysigs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stli_rawclose (struct stlibrd*,struct stliport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stli_sendcmd (struct stlibrd*,struct stliport*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct tty_struct* stli_txcooktty ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_ldisc_flush (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_port_close_end (struct tty_port*,struct tty_struct*) ; 
 scalar_t__ tty_port_close_start (struct tty_port*,struct tty_struct*,struct file*) ; 
 int /*<<< orphan*/  tty_port_tty_set (struct tty_port*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_wait_until_sent (struct tty_struct*,scalar_t__) ; 

__attribute__((used)) static void stli_close(struct tty_struct *tty, struct file *filp)
{
	struct stlibrd *brdp;
	struct stliport *portp;
	struct tty_port *port;
	unsigned long flags;

	portp = tty->driver_data;
	if (portp == NULL)
		return;
	port = &portp->port;

	if (tty_port_close_start(port, tty, filp) == 0)
		return;

/*
 *	May want to wait for data to drain before closing. The BUSY flag
 *	keeps track of whether we are still transmitting or not. It is
 *	updated by messages from the slave - indicating when all chars
 *	really have drained.
 */
 	spin_lock_irqsave(&stli_lock, flags);
	if (tty == stli_txcooktty)
		stli_flushchars(tty);
	spin_unlock_irqrestore(&stli_lock, flags);

	/* We end up doing this twice for the moment. This needs looking at
	   eventually. Note we still use portp->closing_wait as a result */
	if (portp->closing_wait != ASYNC_CLOSING_WAIT_NONE)
		tty_wait_until_sent(tty, portp->closing_wait);

	/* FIXME: port locking here needs attending to */
	port->flags &= ~ASYNC_INITIALIZED;

	brdp = stli_brds[portp->brdnr];
	stli_rawclose(brdp, portp, 0, 0);
	if (tty->termios->c_cflag & HUPCL) {
		stli_mkasysigs(&portp->asig, 0, 0);
		if (test_bit(ST_CMDING, &portp->state))
			set_bit(ST_DOSIGS, &portp->state);
		else
			stli_sendcmd(brdp, portp, A_SETSIGNALS, &portp->asig,
				sizeof(asysigs_t), 0);
	}
	clear_bit(ST_TXBUSY, &portp->state);
	clear_bit(ST_RXSTOP, &portp->state);
	set_bit(TTY_IO_ERROR, &tty->flags);
	tty_ldisc_flush(tty);
	set_bit(ST_DOFLUSHRX, &portp->state);
	stli_flushbuffer(tty);

	tty_port_close_end(port, tty);
	tty_port_tty_set(port, NULL);
}