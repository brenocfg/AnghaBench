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
struct TYPE_2__ {int read_status_mask; int ignore_status_mask; int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  mctrl; } ;
struct uart_txx9_port {TYPE_1__ port; } ;
struct uart_port {int uartclk; } ;
struct ktermios {int c_cflag; int c_iflag; } ;

/* Variables and functions */
 int BRKINT ; 
 int CLOCAL ; 
 int CMSPAR ; 
 int CREAD ; 
 int CRTSCTS ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 int CSIZE ; 
 int CSTOPB ; 
 int HUPCL ; 
 int IGNBRK ; 
 int IGNPAR ; 
 int INPCK ; 
 int PARENB ; 
 int PARMRK ; 
 int PARODD ; 
 int TXX9_SIDISR_RDIS ; 
 int TXX9_SIDISR_TDIS ; 
 int TXX9_SIDISR_UBRK ; 
 int TXX9_SIDISR_UFER ; 
 int TXX9_SIDISR_UOER ; 
 int TXX9_SIDISR_UPER ; 
 int /*<<< orphan*/  TXX9_SIFCR ; 
 unsigned int TXX9_SIFCR_RDIL_1 ; 
 unsigned int TXX9_SIFCR_TDIL_MAX ; 
 int /*<<< orphan*/  TXX9_SIFLCR ; 
 int TXX9_SIFLCR_RCS ; 
 int TXX9_SIFLCR_TES ; 
 int /*<<< orphan*/  TXX9_SILCR ; 
 unsigned int TXX9_SILCR_UEPS ; 
 unsigned int TXX9_SILCR_UMODE_7BIT ; 
 unsigned int TXX9_SILCR_UMODE_8BIT ; 
 unsigned int TXX9_SILCR_UMODE_MASK ; 
 unsigned int TXX9_SILCR_UPEN ; 
 unsigned int TXX9_SILCR_USBL_1BIT ; 
 unsigned int TXX9_SILCR_USBL_2BIT ; 
 unsigned int TXX9_SILCR_USBL_MASK ; 
 int UPF_TXX9_HAVE_CTS_LINE ; 
 int /*<<< orphan*/  serial_txx9_set_mctrl (TYPE_1__*,int /*<<< orphan*/ ) ; 
 unsigned int sio_in (struct uart_txx9_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sio_mask (struct uart_txx9_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sio_out (struct uart_txx9_port*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  sio_quot_set (struct uart_txx9_port*,unsigned int) ; 
 int /*<<< orphan*/  sio_set (struct uart_txx9_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct uart_txx9_port* to_uart_txx9_port (struct uart_port*) ; 
 unsigned int uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int /*<<< orphan*/ ,int) ; 
 unsigned int uart_get_divisor (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,int,unsigned int) ; 

__attribute__((used)) static void
serial_txx9_set_termios(struct uart_port *port, struct ktermios *termios,
		       struct ktermios *old)
{
	struct uart_txx9_port *up = to_uart_txx9_port(port);
	unsigned int cval, fcr = 0;
	unsigned long flags;
	unsigned int baud, quot;

	/*
	 * We don't support modem control lines.
	 */
	termios->c_cflag &= ~(HUPCL | CMSPAR);
	termios->c_cflag |= CLOCAL;

	cval = sio_in(up, TXX9_SILCR);
	/* byte size and parity */
	cval &= ~TXX9_SILCR_UMODE_MASK;
	switch (termios->c_cflag & CSIZE) {
	case CS7:
		cval |= TXX9_SILCR_UMODE_7BIT;
		break;
	default:
	case CS5:	/* not supported */
	case CS6:	/* not supported */
	case CS8:
		cval |= TXX9_SILCR_UMODE_8BIT;
		break;
	}

	cval &= ~TXX9_SILCR_USBL_MASK;
	if (termios->c_cflag & CSTOPB)
		cval |= TXX9_SILCR_USBL_2BIT;
	else
		cval |= TXX9_SILCR_USBL_1BIT;
	cval &= ~(TXX9_SILCR_UPEN | TXX9_SILCR_UEPS);
	if (termios->c_cflag & PARENB)
		cval |= TXX9_SILCR_UPEN;
	if (!(termios->c_cflag & PARODD))
		cval |= TXX9_SILCR_UEPS;

	/*
	 * Ask the core to calculate the divisor for us.
	 */
	baud = uart_get_baud_rate(port, termios, old, 0, port->uartclk/16/2);
	quot = uart_get_divisor(port, baud);

	/* Set up FIFOs */
	/* TX Int by FIFO Empty, RX Int by Receiving 1 char. */
	fcr = TXX9_SIFCR_TDIL_MAX | TXX9_SIFCR_RDIL_1;

	/*
	 * Ok, we're now changing the port state.  Do it with
	 * interrupts disabled.
	 */
	spin_lock_irqsave(&up->port.lock, flags);

	/*
	 * Update the per-port timeout.
	 */
	uart_update_timeout(port, termios->c_cflag, baud);

	up->port.read_status_mask = TXX9_SIDISR_UOER |
		TXX9_SIDISR_TDIS | TXX9_SIDISR_RDIS;
	if (termios->c_iflag & INPCK)
		up->port.read_status_mask |= TXX9_SIDISR_UFER | TXX9_SIDISR_UPER;
	if (termios->c_iflag & (BRKINT | PARMRK))
		up->port.read_status_mask |= TXX9_SIDISR_UBRK;

	/*
	 * Characteres to ignore
	 */
	up->port.ignore_status_mask = 0;
	if (termios->c_iflag & IGNPAR)
		up->port.ignore_status_mask |= TXX9_SIDISR_UPER | TXX9_SIDISR_UFER;
	if (termios->c_iflag & IGNBRK) {
		up->port.ignore_status_mask |= TXX9_SIDISR_UBRK;
		/*
		 * If we're ignoring parity and break indicators,
		 * ignore overruns too (for real raw support).
		 */
		if (termios->c_iflag & IGNPAR)
			up->port.ignore_status_mask |= TXX9_SIDISR_UOER;
	}

	/*
	 * ignore all characters if CREAD is not set
	 */
	if ((termios->c_cflag & CREAD) == 0)
		up->port.ignore_status_mask |= TXX9_SIDISR_RDIS;

	/* CTS flow control flag */
	if ((termios->c_cflag & CRTSCTS) &&
	    (up->port.flags & UPF_TXX9_HAVE_CTS_LINE)) {
		sio_set(up, TXX9_SIFLCR,
			TXX9_SIFLCR_RCS | TXX9_SIFLCR_TES);
	} else {
		sio_mask(up, TXX9_SIFLCR,
			 TXX9_SIFLCR_RCS | TXX9_SIFLCR_TES);
	}

	sio_out(up, TXX9_SILCR, cval);
	sio_quot_set(up, quot);
	sio_out(up, TXX9_SIFCR, fcr);

	serial_txx9_set_mctrl(&up->port, up->port.mctrl);
	spin_unlock_irqrestore(&up->port.lock, flags);
}