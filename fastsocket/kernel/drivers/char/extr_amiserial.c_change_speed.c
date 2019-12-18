#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct ktermios {int c_cflag; } ;
struct async_struct {int flags; int quot; int timeout; int xmit_fifo_size; int read_status_mask; int ignore_status_mask; unsigned int LCR; TYPE_3__* tty; int /*<<< orphan*/  IER; TYPE_2__* state; } ;
struct TYPE_13__ {short serper; } ;
struct TYPE_12__ {TYPE_1__* termios; } ;
struct TYPE_11__ {int baud_base; int custom_divisor; } ;
struct TYPE_10__ {unsigned int c_cflag; } ;

/* Variables and functions */
 int ASYNC_CHECK_CD ; 
 int ASYNC_CTS_FLOW ; 
 int ASYNC_HARDPPS_CD ; 
 int ASYNC_SPD_CUST ; 
 int ASYNC_SPD_MASK ; 
 int CBAUD ; 
 unsigned int CLOCAL ; 
 unsigned int CMSPAR ; 
 unsigned int CREAD ; 
 unsigned int CRTSCTS ; 
 unsigned int CSTOPB ; 
 int HZ ; 
 scalar_t__ I_BRKINT (TYPE_3__*) ; 
 scalar_t__ I_IGNBRK (TYPE_3__*) ; 
 scalar_t__ I_IGNPAR (TYPE_3__*) ; 
 scalar_t__ I_INPCK (TYPE_3__*) ; 
 scalar_t__ I_PARMRK (TYPE_3__*) ; 
 unsigned int PARENB ; 
 unsigned int PARODD ; 
 short SERPER_PARENB ; 
 int /*<<< orphan*/  UART_IER_MSI ; 
 unsigned int UART_LCR_EPAR ; 
 unsigned int UART_LCR_PARITY ; 
 unsigned int UART_LCR_SPAR ; 
 int UART_LSR_BI ; 
 int UART_LSR_DR ; 
 int UART_LSR_FE ; 
 int UART_LSR_OE ; 
 int UART_LSR_PE ; 
 TYPE_4__ custom ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mb () ; 
 int tty_get_baud_rate (TYPE_3__*) ; 

__attribute__((used)) static void change_speed(struct async_struct *info,
			 struct ktermios *old_termios)
{
	int	quot = 0, baud_base, baud;
	unsigned cflag, cval = 0;
	int	bits;
	unsigned long	flags;

	if (!info->tty || !info->tty->termios)
		return;
	cflag = info->tty->termios->c_cflag;

	/* Byte size is always 8 bits plus parity bit if requested */

	cval = 3; bits = 10;
	if (cflag & CSTOPB) {
		cval |= 0x04;
		bits++;
	}
	if (cflag & PARENB) {
		cval |= UART_LCR_PARITY;
		bits++;
	}
	if (!(cflag & PARODD))
		cval |= UART_LCR_EPAR;
#ifdef CMSPAR
	if (cflag & CMSPAR)
		cval |= UART_LCR_SPAR;
#endif

	/* Determine divisor based on baud rate */
	baud = tty_get_baud_rate(info->tty);
	if (!baud)
		baud = 9600;	/* B0 transition handled in rs_set_termios */
	baud_base = info->state->baud_base;
	if (baud == 38400 &&
	    ((info->flags & ASYNC_SPD_MASK) == ASYNC_SPD_CUST))
		quot = info->state->custom_divisor;
	else {
		if (baud == 134)
			/* Special case since 134 is really 134.5 */
			quot = (2*baud_base / 269);
		else if (baud)
			quot = baud_base / baud;
	}
	/* If the quotient is zero refuse the change */
	if (!quot && old_termios) {
		/* FIXME: Will need updating for new tty in the end */
		info->tty->termios->c_cflag &= ~CBAUD;
		info->tty->termios->c_cflag |= (old_termios->c_cflag & CBAUD);
		baud = tty_get_baud_rate(info->tty);
		if (!baud)
			baud = 9600;
		if (baud == 38400 &&
		    ((info->flags & ASYNC_SPD_MASK) == ASYNC_SPD_CUST))
			quot = info->state->custom_divisor;
		else {
			if (baud == 134)
				/* Special case since 134 is really 134.5 */
				quot = (2*baud_base / 269);
			else if (baud)
				quot = baud_base / baud;
		}
	}
	/* As a last resort, if the quotient is zero, default to 9600 bps */
	if (!quot)
		quot = baud_base / 9600;
	info->quot = quot;
	info->timeout = ((info->xmit_fifo_size*HZ*bits*quot) / baud_base);
	info->timeout += HZ/50;		/* Add .02 seconds of slop */

	/* CTS flow control flag and modem status interrupts */
	info->IER &= ~UART_IER_MSI;
	if (info->flags & ASYNC_HARDPPS_CD)
		info->IER |= UART_IER_MSI;
	if (cflag & CRTSCTS) {
		info->flags |= ASYNC_CTS_FLOW;
		info->IER |= UART_IER_MSI;
	} else
		info->flags &= ~ASYNC_CTS_FLOW;
	if (cflag & CLOCAL)
		info->flags &= ~ASYNC_CHECK_CD;
	else {
		info->flags |= ASYNC_CHECK_CD;
		info->IER |= UART_IER_MSI;
	}
	/* TBD:
	 * Does clearing IER_MSI imply that we should disable the VBL interrupt ?
	 */

	/*
	 * Set up parity check flag
	 */

	info->read_status_mask = UART_LSR_OE | UART_LSR_DR;
	if (I_INPCK(info->tty))
		info->read_status_mask |= UART_LSR_FE | UART_LSR_PE;
	if (I_BRKINT(info->tty) || I_PARMRK(info->tty))
		info->read_status_mask |= UART_LSR_BI;

	/*
	 * Characters to ignore
	 */
	info->ignore_status_mask = 0;
	if (I_IGNPAR(info->tty))
		info->ignore_status_mask |= UART_LSR_PE | UART_LSR_FE;
	if (I_IGNBRK(info->tty)) {
		info->ignore_status_mask |= UART_LSR_BI;
		/*
		 * If we're ignore parity and break indicators, ignore 
		 * overruns too.  (For real raw support).
		 */
		if (I_IGNPAR(info->tty))
			info->ignore_status_mask |= UART_LSR_OE;
	}
	/*
	 * !!! ignore all characters if CREAD is not set
	 */
	if ((cflag & CREAD) == 0)
		info->ignore_status_mask |= UART_LSR_DR;
	local_irq_save(flags);

	{
	  short serper;

	/* Set up the baud rate */
	  serper = quot - 1;

	/* Enable or disable parity bit */

	if(cval & UART_LCR_PARITY)
	  serper |= (SERPER_PARENB);

	custom.serper = serper;
	mb();
	}

	info->LCR = cval;				/* Save LCR */
	local_irq_restore(flags);
}