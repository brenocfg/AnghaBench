#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t type; unsigned int uartclk; int read_status_mask; int ignore_status_mask; int /*<<< orphan*/  lock; } ;
struct uart_sunsu_port {int rev; unsigned char lcr; unsigned int cflag; TYPE_2__ port; int /*<<< orphan*/  ier; } ;
struct uart_port {int uartclk; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 unsigned int BRKINT ; 
 unsigned int CMSPAR ; 
 unsigned int CREAD ; 
 unsigned int CRTSCTS ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 unsigned int CSIZE ; 
 unsigned int CSTOPB ; 
 unsigned int IGNBRK ; 
 unsigned int IGNPAR ; 
 unsigned int INPCK ; 
 unsigned int PARENB ; 
 unsigned int PARMRK ; 
 unsigned int PARODD ; 
 size_t PORT_16750 ; 
 size_t PORT_16C950 ; 
 size_t PORT_RSA ; 
 int /*<<< orphan*/  UART_DLL ; 
 int /*<<< orphan*/  UART_DLM ; 
 int /*<<< orphan*/  UART_EFR ; 
 unsigned char UART_EFR_CTS ; 
 scalar_t__ UART_ENABLE_MS (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  UART_FCR ; 
 unsigned char UART_FCR7_64BYTE ; 
 unsigned char UART_FCR_ENABLE_FIFO ; 
 unsigned char UART_FCR_TRIGGER_1 ; 
 unsigned char UART_FCR_TRIGGER_14 ; 
 unsigned char UART_FCR_TRIGGER_8 ; 
 int /*<<< orphan*/  UART_IER ; 
 int /*<<< orphan*/  UART_IER_MSI ; 
 int /*<<< orphan*/  UART_LCR ; 
 unsigned char UART_LCR_DLAB ; 
 unsigned char UART_LCR_EPAR ; 
 unsigned char UART_LCR_PARITY ; 
 unsigned char UART_LCR_SPAR ; 
 int UART_LSR_BI ; 
 int UART_LSR_DR ; 
 int UART_LSR_FE ; 
 int UART_LSR_OE ; 
 int UART_LSR_PE ; 
 int UART_LSR_THRE ; 
 int UART_STARTECH ; 
 int UART_USE_FIFO ; 
 int /*<<< orphan*/  serial_out (struct uart_sunsu_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_outp (struct uart_sunsu_port*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__* uart_config ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,unsigned int,int) ; 

__attribute__((used)) static void
sunsu_change_speed(struct uart_port *port, unsigned int cflag,
		   unsigned int iflag, unsigned int quot)
{
	struct uart_sunsu_port *up = (struct uart_sunsu_port *) port;
	unsigned char cval, fcr = 0;
	unsigned long flags;

	switch (cflag & CSIZE) {
	case CS5:
		cval = 0x00;
		break;
	case CS6:
		cval = 0x01;
		break;
	case CS7:
		cval = 0x02;
		break;
	default:
	case CS8:
		cval = 0x03;
		break;
	}

	if (cflag & CSTOPB)
		cval |= 0x04;
	if (cflag & PARENB)
		cval |= UART_LCR_PARITY;
	if (!(cflag & PARODD))
		cval |= UART_LCR_EPAR;
#ifdef CMSPAR
	if (cflag & CMSPAR)
		cval |= UART_LCR_SPAR;
#endif

	/*
	 * Work around a bug in the Oxford Semiconductor 952 rev B
	 * chip which causes it to seriously miscalculate baud rates
	 * when DLL is 0.
	 */
	if ((quot & 0xff) == 0 && up->port.type == PORT_16C950 &&
	    up->rev == 0x5201)
		quot ++;

	if (uart_config[up->port.type].flags & UART_USE_FIFO) {
		if ((up->port.uartclk / quot) < (2400 * 16))
			fcr = UART_FCR_ENABLE_FIFO | UART_FCR_TRIGGER_1;
#ifdef CONFIG_SERIAL_8250_RSA
		else if (up->port.type == PORT_RSA)
			fcr = UART_FCR_ENABLE_FIFO | UART_FCR_TRIGGER_14;
#endif
		else
			fcr = UART_FCR_ENABLE_FIFO | UART_FCR_TRIGGER_8;
	}
	if (up->port.type == PORT_16750)
		fcr |= UART_FCR7_64BYTE;

	/*
	 * Ok, we're now changing the port state.  Do it with
	 * interrupts disabled.
	 */
	spin_lock_irqsave(&up->port.lock, flags);

	/*
	 * Update the per-port timeout.
	 */
	uart_update_timeout(port, cflag, (port->uartclk / (16 * quot)));

	up->port.read_status_mask = UART_LSR_OE | UART_LSR_THRE | UART_LSR_DR;
	if (iflag & INPCK)
		up->port.read_status_mask |= UART_LSR_FE | UART_LSR_PE;
	if (iflag & (BRKINT | PARMRK))
		up->port.read_status_mask |= UART_LSR_BI;

	/*
	 * Characteres to ignore
	 */
	up->port.ignore_status_mask = 0;
	if (iflag & IGNPAR)
		up->port.ignore_status_mask |= UART_LSR_PE | UART_LSR_FE;
	if (iflag & IGNBRK) {
		up->port.ignore_status_mask |= UART_LSR_BI;
		/*
		 * If we're ignoring parity and break indicators,
		 * ignore overruns too (for real raw support).
		 */
		if (iflag & IGNPAR)
			up->port.ignore_status_mask |= UART_LSR_OE;
	}

	/*
	 * ignore all characters if CREAD is not set
	 */
	if ((cflag & CREAD) == 0)
		up->port.ignore_status_mask |= UART_LSR_DR;

	/*
	 * CTS flow control flag and modem status interrupts
	 */
	up->ier &= ~UART_IER_MSI;
	if (UART_ENABLE_MS(&up->port, cflag))
		up->ier |= UART_IER_MSI;

	serial_out(up, UART_IER, up->ier);

	if (uart_config[up->port.type].flags & UART_STARTECH) {
		serial_outp(up, UART_LCR, 0xBF);
		serial_outp(up, UART_EFR, cflag & CRTSCTS ? UART_EFR_CTS :0);
	}
	serial_outp(up, UART_LCR, cval | UART_LCR_DLAB);/* set DLAB */
	serial_outp(up, UART_DLL, quot & 0xff);		/* LS of divisor */
	serial_outp(up, UART_DLM, quot >> 8);		/* MS of divisor */
	if (up->port.type == PORT_16750)
		serial_outp(up, UART_FCR, fcr);		/* set fcr */
	serial_outp(up, UART_LCR, cval);		/* reset DLAB */
	up->lcr = cval;					/* Save LCR */
	if (up->port.type != PORT_16750) {
		if (fcr & UART_FCR_ENABLE_FIFO) {
			/* emulated UARTs (Lucent Venus 167x) need two steps */
			serial_outp(up, UART_FCR, UART_FCR_ENABLE_FIFO);
		}
		serial_outp(up, UART_FCR, fcr);		/* set fcr */
	}

	up->cflag = cflag;

	spin_unlock_irqrestore(&up->port.lock, flags);
}