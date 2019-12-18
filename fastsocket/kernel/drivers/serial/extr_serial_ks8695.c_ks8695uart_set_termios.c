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
struct uart_port {int uartclk; int fifosize; int read_status_mask; int ignore_status_mask; int /*<<< orphan*/  lock; } ;
struct ktermios {int c_cflag; int c_iflag; } ;

/* Variables and functions */
 int BRKINT ; 
 int CMSPAR ; 
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
 int UART_DUMMY_LSR_RX ; 
 scalar_t__ UART_ENABLE_MS (struct uart_port*,int) ; 
 int /*<<< orphan*/  UART_PUT_BRDR (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  UART_PUT_FCR (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  UART_PUT_LCR (struct uart_port*,unsigned int) ; 
 unsigned int URCL_5 ; 
 unsigned int URCL_6 ; 
 unsigned int URCL_7 ; 
 unsigned int URCL_8 ; 
 unsigned int URFC_URFE ; 
 unsigned int URFC_URFRT_8 ; 
 unsigned int URFC_URRFR ; 
 unsigned int URFC_URTFR ; 
 unsigned int URLC_URSB ; 
 int URLS_URBI ; 
 int URLS_URFE ; 
 int URLS_URPE ; 
 int URLS_URROE ; 
 unsigned int URPE_EVEN ; 
 unsigned int URPE_MARK ; 
 unsigned int URPE_ODD ; 
 unsigned int URPE_SPACE ; 
 int /*<<< orphan*/  ks8695uart_disable_ms (struct uart_port*) ; 
 int /*<<< orphan*/  ks8695uart_enable_ms (struct uart_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int /*<<< orphan*/ ,int) ; 
 unsigned int uart_get_divisor (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,int,unsigned int) ; 

__attribute__((used)) static void ks8695uart_set_termios(struct uart_port *port, struct ktermios *termios, struct ktermios *old)
{
	unsigned int lcr, fcr = 0;
	unsigned long flags;
	unsigned int baud, quot;

	/*
	 * Ask the core to calculate the divisor for us.
	 */
	baud = uart_get_baud_rate(port, termios, old, 0, port->uartclk/16);
	quot = uart_get_divisor(port, baud);

	switch (termios->c_cflag & CSIZE) {
	case CS5:
		lcr = URCL_5;
		break;
	case CS6:
		lcr = URCL_6;
		break;
	case CS7:
		lcr = URCL_7;
		break;
	default:
		lcr = URCL_8;
		break;
	}

	/* stop bits */
	if (termios->c_cflag & CSTOPB)
		lcr |= URLC_URSB;

	/* parity */
	if (termios->c_cflag & PARENB) {
		if (termios->c_cflag & CMSPAR) {	/* Mark or Space parity */
			if (termios->c_cflag & PARODD)
				lcr |= URPE_MARK;
			else
				lcr |= URPE_SPACE;
		}
		else if (termios->c_cflag & PARODD)
			lcr |= URPE_ODD;
		else
			lcr |= URPE_EVEN;
	}

	if (port->fifosize > 1)
		fcr = URFC_URFRT_8 | URFC_URTFR | URFC_URRFR | URFC_URFE;

	spin_lock_irqsave(&port->lock, flags);

	/*
	 * Update the per-port timeout.
	 */
	uart_update_timeout(port, termios->c_cflag, baud);

	port->read_status_mask = URLS_URROE;
	if (termios->c_iflag & INPCK)
		port->read_status_mask |= (URLS_URFE | URLS_URPE);
	if (termios->c_iflag & (BRKINT | PARMRK))
		port->read_status_mask |= URLS_URBI;

	/*
	 * Characters to ignore
	 */
	port->ignore_status_mask = 0;
	if (termios->c_iflag & IGNPAR)
		port->ignore_status_mask |= (URLS_URFE | URLS_URPE);
	if (termios->c_iflag & IGNBRK) {
		port->ignore_status_mask |= URLS_URBI;
		/*
		 * If we're ignoring parity and break indicators,
		 * ignore overruns too (for real raw support).
		 */
		if (termios->c_iflag & IGNPAR)
			port->ignore_status_mask |= URLS_URROE;
	}

	/*
	 * Ignore all characters if CREAD is not set.
	 */
	if ((termios->c_cflag & CREAD) == 0)
		port->ignore_status_mask |= UART_DUMMY_LSR_RX;

	/* first, disable everything */
	if (UART_ENABLE_MS(port, termios->c_cflag))
		ks8695uart_enable_ms(port);
	else
		ks8695uart_disable_ms(port);

	/* Set baud rate */
	UART_PUT_BRDR(port, quot);

	UART_PUT_LCR(port, lcr);
	UART_PUT_FCR(port, fcr);

	spin_unlock_irqrestore(&port->lock, flags);
}