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
struct uart_port {int uartclk; int read_status_mask; int ignore_status_mask; int /*<<< orphan*/  lock; TYPE_1__* ops; } ;
struct ktermios {int c_cflag; int c_iflag; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable_ms ) (struct uart_port*) ;} ;

/* Variables and functions */
 unsigned int ATMEL_US_CHRL ; 
 unsigned int ATMEL_US_CHRL_5 ; 
 unsigned int ATMEL_US_CHRL_6 ; 
 unsigned int ATMEL_US_CHRL_7 ; 
 unsigned int ATMEL_US_CHRL_8 ; 
 int ATMEL_US_FRAME ; 
 unsigned int ATMEL_US_NBSTOP ; 
 unsigned int ATMEL_US_NBSTOP_2 ; 
 int ATMEL_US_OVRE ; 
 unsigned int ATMEL_US_PAR ; 
 int ATMEL_US_PARE ; 
 unsigned int ATMEL_US_PAR_EVEN ; 
 unsigned int ATMEL_US_PAR_MARK ; 
 unsigned int ATMEL_US_PAR_NONE ; 
 unsigned int ATMEL_US_PAR_ODD ; 
 unsigned int ATMEL_US_PAR_SPACE ; 
 int ATMEL_US_RSTRX ; 
 int ATMEL_US_RSTSTA ; 
 int ATMEL_US_RXBRK ; 
 int ATMEL_US_RXDIS ; 
 int ATMEL_US_RXEN ; 
 int ATMEL_US_TXDIS ; 
 int ATMEL_US_TXEN ; 
 unsigned int ATMEL_US_USCLKS ; 
 unsigned int ATMEL_US_USCLKS_MCK_DIV8 ; 
 unsigned int ATMEL_US_USMODE ; 
 unsigned int ATMEL_US_USMODE_HWHS ; 
 unsigned int ATMEL_US_USMODE_NORMAL ; 
 int BRKINT ; 
 int CMSPAR ; 
 int CRTSCTS ; 
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
 scalar_t__ UART_ENABLE_MS (struct uart_port*,int) ; 
 unsigned int UART_GET_IMR (struct uart_port*) ; 
 unsigned int UART_GET_MR (struct uart_port*) ; 
 int /*<<< orphan*/  UART_PUT_BRGR (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  UART_PUT_CR (struct uart_port*,int) ; 
 int /*<<< orphan*/  UART_PUT_IDR (struct uart_port*,int) ; 
 int /*<<< orphan*/  UART_PUT_IER (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  UART_PUT_MR (struct uart_port*,unsigned int) ; 
 scalar_t__ atmel_use_dma_rx (struct uart_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct uart_port*) ; 
 unsigned int uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int /*<<< orphan*/ ,int) ; 
 unsigned int uart_get_divisor (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,int,unsigned int) ; 

__attribute__((used)) static void atmel_set_termios(struct uart_port *port, struct ktermios *termios,
			      struct ktermios *old)
{
	unsigned long flags;
	unsigned int mode, imr, quot, baud;

	/* Get current mode register */
	mode = UART_GET_MR(port) & ~(ATMEL_US_USCLKS | ATMEL_US_CHRL
					| ATMEL_US_NBSTOP | ATMEL_US_PAR
					| ATMEL_US_USMODE);

	baud = uart_get_baud_rate(port, termios, old, 0, port->uartclk / 16);
	quot = uart_get_divisor(port, baud);

	if (quot > 65535) {	/* BRGR is 16-bit, so switch to slower clock */
		quot /= 8;
		mode |= ATMEL_US_USCLKS_MCK_DIV8;
	}

	/* byte size */
	switch (termios->c_cflag & CSIZE) {
	case CS5:
		mode |= ATMEL_US_CHRL_5;
		break;
	case CS6:
		mode |= ATMEL_US_CHRL_6;
		break;
	case CS7:
		mode |= ATMEL_US_CHRL_7;
		break;
	default:
		mode |= ATMEL_US_CHRL_8;
		break;
	}

	/* stop bits */
	if (termios->c_cflag & CSTOPB)
		mode |= ATMEL_US_NBSTOP_2;

	/* parity */
	if (termios->c_cflag & PARENB) {
		/* Mark or Space parity */
		if (termios->c_cflag & CMSPAR) {
			if (termios->c_cflag & PARODD)
				mode |= ATMEL_US_PAR_MARK;
			else
				mode |= ATMEL_US_PAR_SPACE;
		} else if (termios->c_cflag & PARODD)
			mode |= ATMEL_US_PAR_ODD;
		else
			mode |= ATMEL_US_PAR_EVEN;
	} else
		mode |= ATMEL_US_PAR_NONE;

	/* hardware handshake (RTS/CTS) */
	if (termios->c_cflag & CRTSCTS)
		mode |= ATMEL_US_USMODE_HWHS;
	else
		mode |= ATMEL_US_USMODE_NORMAL;

	spin_lock_irqsave(&port->lock, flags);

	port->read_status_mask = ATMEL_US_OVRE;
	if (termios->c_iflag & INPCK)
		port->read_status_mask |= (ATMEL_US_FRAME | ATMEL_US_PARE);
	if (termios->c_iflag & (BRKINT | PARMRK))
		port->read_status_mask |= ATMEL_US_RXBRK;

	if (atmel_use_dma_rx(port))
		/* need to enable error interrupts */
		UART_PUT_IER(port, port->read_status_mask);

	/*
	 * Characters to ignore
	 */
	port->ignore_status_mask = 0;
	if (termios->c_iflag & IGNPAR)
		port->ignore_status_mask |= (ATMEL_US_FRAME | ATMEL_US_PARE);
	if (termios->c_iflag & IGNBRK) {
		port->ignore_status_mask |= ATMEL_US_RXBRK;
		/*
		 * If we're ignoring parity and break indicators,
		 * ignore overruns too (for real raw support).
		 */
		if (termios->c_iflag & IGNPAR)
			port->ignore_status_mask |= ATMEL_US_OVRE;
	}
	/* TODO: Ignore all characters if CREAD is set.*/

	/* update the per-port timeout */
	uart_update_timeout(port, termios->c_cflag, baud);

	/*
	 * save/disable interrupts. The tty layer will ensure that the
	 * transmitter is empty if requested by the caller, so there's
	 * no need to wait for it here.
	 */
	imr = UART_GET_IMR(port);
	UART_PUT_IDR(port, -1);

	/* disable receiver and transmitter */
	UART_PUT_CR(port, ATMEL_US_TXDIS | ATMEL_US_RXDIS);

	/* set the parity, stop bits and data size */
	UART_PUT_MR(port, mode);

	/* set the baud rate */
	UART_PUT_BRGR(port, quot);
	UART_PUT_CR(port, ATMEL_US_RSTSTA | ATMEL_US_RSTRX);
	UART_PUT_CR(port, ATMEL_US_TXEN | ATMEL_US_RXEN);

	/* restore interrupts */
	UART_PUT_IER(port, imr);

	/* CTS flow-control and modem-status interrupts */
	if (UART_ENABLE_MS(port, termios->c_cflag))
		port->ops->enable_ms(port);

	spin_unlock_irqrestore(&port->lock, flags);
}