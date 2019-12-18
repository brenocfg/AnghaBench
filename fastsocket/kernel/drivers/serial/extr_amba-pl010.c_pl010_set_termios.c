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
struct uart_port {int dummy; } ;
struct TYPE_2__ {int uartclk; int fifosize; int read_status_mask; int ignore_status_mask; int /*<<< orphan*/  lock; scalar_t__ membase; } ;
struct uart_amba_port {TYPE_1__ port; } ;
struct ktermios {int c_cflag; int c_iflag; } ;

/* Variables and functions */
 int BRKINT ; 
 int CREAD ; 
#define  CS5 130 
#define  CS6 129 
#define  CS7 128 
 int CSIZE ; 
 int CSTOPB ; 
 int IGNBRK ; 
 int IGNPAR ; 
 int INPCK ; 
 int PARENB ; 
 int PARMRK ; 
 int PARODD ; 
 scalar_t__ UART010_CR ; 
 unsigned int UART010_CR_MSIE ; 
 scalar_t__ UART010_LCRH ; 
 scalar_t__ UART010_LCRL ; 
 scalar_t__ UART010_LCRM ; 
 unsigned int UART01x_LCRH_EPS ; 
 unsigned int UART01x_LCRH_FEN ; 
 unsigned int UART01x_LCRH_PEN ; 
 unsigned int UART01x_LCRH_STP2 ; 
 unsigned int UART01x_LCRH_WLEN_5 ; 
 unsigned int UART01x_LCRH_WLEN_6 ; 
 unsigned int UART01x_LCRH_WLEN_7 ; 
 unsigned int UART01x_LCRH_WLEN_8 ; 
 int UART01x_RSR_BE ; 
 int UART01x_RSR_FE ; 
 int UART01x_RSR_OE ; 
 int UART01x_RSR_PE ; 
 int UART_DUMMY_RSR_RX ; 
 scalar_t__ UART_ENABLE_MS (struct uart_port*,int) ; 
 unsigned int readb (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int /*<<< orphan*/ ,int) ; 
 unsigned int uart_get_divisor (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,int,unsigned int) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void
pl010_set_termios(struct uart_port *port, struct ktermios *termios,
		     struct ktermios *old)
{
	struct uart_amba_port *uap = (struct uart_amba_port *)port;
	unsigned int lcr_h, old_cr;
	unsigned long flags;
	unsigned int baud, quot;

	/*
	 * Ask the core to calculate the divisor for us.
	 */
	baud = uart_get_baud_rate(port, termios, old, 0, uap->port.uartclk/16); 
	quot = uart_get_divisor(port, baud);

	switch (termios->c_cflag & CSIZE) {
	case CS5:
		lcr_h = UART01x_LCRH_WLEN_5;
		break;
	case CS6:
		lcr_h = UART01x_LCRH_WLEN_6;
		break;
	case CS7:
		lcr_h = UART01x_LCRH_WLEN_7;
		break;
	default: // CS8
		lcr_h = UART01x_LCRH_WLEN_8;
		break;
	}
	if (termios->c_cflag & CSTOPB)
		lcr_h |= UART01x_LCRH_STP2;
	if (termios->c_cflag & PARENB) {
		lcr_h |= UART01x_LCRH_PEN;
		if (!(termios->c_cflag & PARODD))
			lcr_h |= UART01x_LCRH_EPS;
	}
	if (uap->port.fifosize > 1)
		lcr_h |= UART01x_LCRH_FEN;

	spin_lock_irqsave(&uap->port.lock, flags);

	/*
	 * Update the per-port timeout.
	 */
	uart_update_timeout(port, termios->c_cflag, baud);

	uap->port.read_status_mask = UART01x_RSR_OE;
	if (termios->c_iflag & INPCK)
		uap->port.read_status_mask |= UART01x_RSR_FE | UART01x_RSR_PE;
	if (termios->c_iflag & (BRKINT | PARMRK))
		uap->port.read_status_mask |= UART01x_RSR_BE;

	/*
	 * Characters to ignore
	 */
	uap->port.ignore_status_mask = 0;
	if (termios->c_iflag & IGNPAR)
		uap->port.ignore_status_mask |= UART01x_RSR_FE | UART01x_RSR_PE;
	if (termios->c_iflag & IGNBRK) {
		uap->port.ignore_status_mask |= UART01x_RSR_BE;
		/*
		 * If we're ignoring parity and break indicators,
		 * ignore overruns too (for real raw support).
		 */
		if (termios->c_iflag & IGNPAR)
			uap->port.ignore_status_mask |= UART01x_RSR_OE;
	}

	/*
	 * Ignore all characters if CREAD is not set.
	 */
	if ((termios->c_cflag & CREAD) == 0)
		uap->port.ignore_status_mask |= UART_DUMMY_RSR_RX;

	/* first, disable everything */
	old_cr = readb(uap->port.membase + UART010_CR) & ~UART010_CR_MSIE;

	if (UART_ENABLE_MS(port, termios->c_cflag))
		old_cr |= UART010_CR_MSIE;

	writel(0, uap->port.membase + UART010_CR);

	/* Set baud rate */
	quot -= 1;
	writel((quot & 0xf00) >> 8, uap->port.membase + UART010_LCRM);
	writel(quot & 0xff, uap->port.membase + UART010_LCRL);

	/*
	 * ----------v----------v----------v----------v-----
	 * NOTE: MUST BE WRITTEN AFTER UARTLCR_M & UARTLCR_L
	 * ----------^----------^----------^----------^-----
	 */
	writel(lcr_h, uap->port.membase + UART010_LCRH);
	writel(old_cr, uap->port.membase + UART010_CR);

	spin_unlock_irqrestore(&uap->port.lock, flags);
}