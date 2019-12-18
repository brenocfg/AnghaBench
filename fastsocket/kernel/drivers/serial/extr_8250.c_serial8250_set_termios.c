#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int uartclk; } ;
struct TYPE_5__ {size_t type; int fifosize; int read_status_mask; int ignore_status_mask; int /*<<< orphan*/  lock; int /*<<< orphan*/  mctrl; } ;
struct uart_8250_port {int bugs; int capabilities; int ier; unsigned char lcr; TYPE_2__ port; int /*<<< orphan*/  mcr; } ;
struct ktermios {int c_cflag; int c_iflag; } ;
struct TYPE_4__ {unsigned char fcr; } ;

/* Variables and functions */
 int BRKINT ; 
 int CMSPAR ; 
 int CREAD ; 
 int CRTSCTS ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 int CSIZE ; 
 int CSTOPB ; 
 int IGNBRK ; 
 int IGNPAR ; 
 int INPCK ; 
 int PARENB ; 
 int PARMRK ; 
 int PARODD ; 
 size_t PORT_16750 ; 
 size_t PORT_16C950 ; 
 int UART_BUG_NOMSR ; 
 int UART_BUG_QUOT ; 
 int UART_CAP_AFE ; 
 int UART_CAP_EFR ; 
 int UART_CAP_FIFO ; 
 int UART_CAP_UUE ; 
 int /*<<< orphan*/  UART_EFR ; 
 unsigned char UART_EFR_CTS ; 
 scalar_t__ UART_ENABLE_MS (TYPE_2__*,int) ; 
 int /*<<< orphan*/  UART_FCR ; 
 unsigned char UART_FCR_ENABLE_FIFO ; 
 unsigned char UART_FCR_TRIGGER_1 ; 
 int /*<<< orphan*/  UART_IER ; 
 int UART_IER_MSI ; 
 int UART_IER_RTOIE ; 
 int UART_IER_UUE ; 
 int /*<<< orphan*/  UART_LCR ; 
 unsigned char UART_LCR_DLAB ; 
 unsigned char UART_LCR_EPAR ; 
 unsigned char UART_LCR_PARITY ; 
 unsigned char UART_LCR_SPAR ; 
 unsigned char UART_LCR_STOP ; 
 unsigned char UART_LCR_WLEN5 ; 
 unsigned char UART_LCR_WLEN6 ; 
 unsigned char UART_LCR_WLEN7 ; 
 unsigned char UART_LCR_WLEN8 ; 
 int UART_LSR_BI ; 
 int UART_LSR_DR ; 
 int UART_LSR_FE ; 
 int UART_LSR_OE ; 
 int UART_LSR_PE ; 
 int UART_LSR_THRE ; 
 int /*<<< orphan*/  UART_MCR_AFE ; 
 int UART_NATSEMI ; 
 int /*<<< orphan*/  UART_OMAP_OSC_12M_SEL ; 
 int /*<<< orphan*/  UART_TCR ; 
 scalar_t__ cpu_is_omap1510 () ; 
 scalar_t__ is_omap_port (struct uart_8250_port*) ; 
 unsigned int serial8250_get_divisor (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  serial8250_set_mctrl (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_dl_write (struct uart_8250_port*,unsigned int) ; 
 int /*<<< orphan*/  serial_icr_write (struct uart_8250_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  serial_out (struct uart_8250_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  serial_outp (struct uart_8250_port*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ tty_termios_baud_rate (struct ktermios*) ; 
 int /*<<< orphan*/  tty_termios_encode_baud_rate (struct ktermios*,unsigned int,unsigned int) ; 
 TYPE_1__* uart_config ; 
 unsigned int uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int,unsigned int) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,int,unsigned int) ; 

__attribute__((used)) static void
serial8250_set_termios(struct uart_port *port, struct ktermios *termios,
		       struct ktermios *old)
{
	struct uart_8250_port *up = (struct uart_8250_port *)port;
	unsigned char cval, fcr = 0;
	unsigned long flags;
	unsigned int baud, quot, max_baud;

	switch (termios->c_cflag & CSIZE) {
	case CS5:
		cval = UART_LCR_WLEN5;
		break;
	case CS6:
		cval = UART_LCR_WLEN6;
		break;
	case CS7:
		cval = UART_LCR_WLEN7;
		break;
	default:
	case CS8:
		cval = UART_LCR_WLEN8;
		break;
	}

	if (termios->c_cflag & CSTOPB)
		cval |= UART_LCR_STOP;
	if (termios->c_cflag & PARENB)
		cval |= UART_LCR_PARITY;
	if (!(termios->c_cflag & PARODD))
		cval |= UART_LCR_EPAR;
#ifdef CMSPAR
	if (termios->c_cflag & CMSPAR)
		cval |= UART_LCR_SPAR;
#endif

	/*
	 * Ask the core to calculate the divisor for us.
	 */
	max_baud = (up->port.type == PORT_16C950 ? port->uartclk/4 : port->uartclk/16);
	baud = uart_get_baud_rate(port, termios, old,
				  port->uartclk / 16 / 0xffff,
				  max_baud);
	quot = serial8250_get_divisor(port, baud);

	/*
	 * Oxford Semi 952 rev B workaround
	 */
	if (up->bugs & UART_BUG_QUOT && (quot & 0xff) == 0)
		quot++;

	if (up->capabilities & UART_CAP_FIFO && up->port.fifosize > 1) {
		if (baud < 2400)
			fcr = UART_FCR_ENABLE_FIFO | UART_FCR_TRIGGER_1;
		else
			fcr = uart_config[up->port.type].fcr;
	}

	/*
	 * MCR-based auto flow control.  When AFE is enabled, RTS will be
	 * deasserted when the receive FIFO contains more characters than
	 * the trigger, or the MCR RTS bit is cleared.  In the case where
	 * the remote UART is not using CTS auto flow control, we must
	 * have sufficient FIFO entries for the latency of the remote
	 * UART to respond.  IOW, at least 32 bytes of FIFO.
	 */
	if (up->capabilities & UART_CAP_AFE && up->port.fifosize >= 32) {
		up->mcr &= ~UART_MCR_AFE;
		if (termios->c_cflag & CRTSCTS)
			up->mcr |= UART_MCR_AFE;
	}

	/*
	 * Ok, we're now changing the port state.  Do it with
	 * interrupts disabled.
	 */
	spin_lock_irqsave(&up->port.lock, flags);

	/*
	 * 16C950 supports additional prescaler ratios between 1:16 and 1:4
	 * thus increasing max baud rate to uartclk/4.
	 */
	if (up->port.type == PORT_16C950) {
		if (baud == port->uartclk/4)
			serial_icr_write(up, UART_TCR, 0x4);
		else if (baud == port->uartclk/8)
			serial_icr_write(up, UART_TCR, 0x8);
		else
			serial_icr_write(up, UART_TCR, 0);
	}

	/*
	 * Update the per-port timeout.
	 */
	uart_update_timeout(port, termios->c_cflag, baud);

	up->port.read_status_mask = UART_LSR_OE | UART_LSR_THRE | UART_LSR_DR;
	if (termios->c_iflag & INPCK)
		up->port.read_status_mask |= UART_LSR_FE | UART_LSR_PE;
	if (termios->c_iflag & (BRKINT | PARMRK))
		up->port.read_status_mask |= UART_LSR_BI;

	/*
	 * Characteres to ignore
	 */
	up->port.ignore_status_mask = 0;
	if (termios->c_iflag & IGNPAR)
		up->port.ignore_status_mask |= UART_LSR_PE | UART_LSR_FE;
	if (termios->c_iflag & IGNBRK) {
		up->port.ignore_status_mask |= UART_LSR_BI;
		/*
		 * If we're ignoring parity and break indicators,
		 * ignore overruns too (for real raw support).
		 */
		if (termios->c_iflag & IGNPAR)
			up->port.ignore_status_mask |= UART_LSR_OE;
	}

	/*
	 * ignore all characters if CREAD is not set
	 */
	if ((termios->c_cflag & CREAD) == 0)
		up->port.ignore_status_mask |= UART_LSR_DR;

	/*
	 * CTS flow control flag and modem status interrupts
	 */
	up->ier &= ~UART_IER_MSI;
	if (!(up->bugs & UART_BUG_NOMSR) &&
			UART_ENABLE_MS(&up->port, termios->c_cflag))
		up->ier |= UART_IER_MSI;
	if (up->capabilities & UART_CAP_UUE)
		up->ier |= UART_IER_UUE | UART_IER_RTOIE;

	serial_out(up, UART_IER, up->ier);

	if (up->capabilities & UART_CAP_EFR) {
		unsigned char efr = 0;
		/*
		 * TI16C752/Startech hardware flow control.  FIXME:
		 * - TI16C752 requires control thresholds to be set.
		 * - UART_MCR_RTS is ineffective if auto-RTS mode is enabled.
		 */
		if (termios->c_cflag & CRTSCTS)
			efr |= UART_EFR_CTS;

		serial_outp(up, UART_LCR, 0xBF);
		serial_outp(up, UART_EFR, efr);
	}

#ifdef CONFIG_ARCH_OMAP
	/* Workaround to enable 115200 baud on OMAP1510 internal ports */
	if (cpu_is_omap1510() && is_omap_port(up)) {
		if (baud == 115200) {
			quot = 1;
			serial_out(up, UART_OMAP_OSC_12M_SEL, 1);
		} else
			serial_out(up, UART_OMAP_OSC_12M_SEL, 0);
	}
#endif

	if (up->capabilities & UART_NATSEMI) {
		/* Switch to bank 2 not bank 1, to avoid resetting EXCR2 */
		serial_outp(up, UART_LCR, 0xe0);
	} else {
		serial_outp(up, UART_LCR, cval | UART_LCR_DLAB);/* set DLAB */
	}

	serial_dl_write(up, quot);

	/*
	 * LCR DLAB must be set to enable 64-byte FIFO mode. If the FCR
	 * is written without DLAB set, this mode will be disabled.
	 */
	if (up->port.type == PORT_16750)
		serial_outp(up, UART_FCR, fcr);

	serial_outp(up, UART_LCR, cval);		/* reset DLAB */
	up->lcr = cval;					/* Save LCR */
	if (up->port.type != PORT_16750) {
		if (fcr & UART_FCR_ENABLE_FIFO) {
			/* emulated UARTs (Lucent Venus 167x) need two steps */
			serial_outp(up, UART_FCR, UART_FCR_ENABLE_FIFO);
		}
		serial_outp(up, UART_FCR, fcr);		/* set fcr */
	}
	serial8250_set_mctrl(&up->port, up->port.mctrl);
	spin_unlock_irqrestore(&up->port.lock, flags);
	/* Don't rewrite B0 */
	if (tty_termios_baud_rate(termios))
		tty_termios_encode_baud_rate(termios, baud, baud);
}