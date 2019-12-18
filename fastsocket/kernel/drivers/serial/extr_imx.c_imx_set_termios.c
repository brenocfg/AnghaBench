#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long uint64_t ;
struct uart_port {int uartclk; TYPE_2__* state; } ;
struct ktermios {unsigned int c_cflag; int c_iflag; } ;
struct TYPE_11__ {int read_status_mask; int ignore_status_mask; unsigned int uartclk; int /*<<< orphan*/  lock; scalar_t__ membase; TYPE_4__* state; } ;
struct imx_port {TYPE_5__ port; int /*<<< orphan*/  timer; scalar_t__ have_rtscts; } ;
typedef  int /*<<< orphan*/  speed_t ;
struct TYPE_9__ {int /*<<< orphan*/  tty; } ;
struct TYPE_10__ {TYPE_3__ port; } ;
struct TYPE_7__ {scalar_t__ tty; } ;
struct TYPE_8__ {TYPE_1__ port; } ;

/* Variables and functions */
 int BRKINT ; 
 int CLOCAL ; 
 int CMSPAR ; 
 int CRTSCTS ; 
 unsigned int CS7 ; 
 unsigned int CS8 ; 
 unsigned int CSIZE ; 
 int CSTOPB ; 
 int HUPCL ; 
 int IGNBRK ; 
 int IGNPAR ; 
 int INPCK ; 
 scalar_t__ MX2_ONEMS ; 
 int PARENB ; 
 int PARMRK ; 
 int PARODD ; 
 scalar_t__ UART_ENABLE_MS (TYPE_5__*,int) ; 
 scalar_t__ UBIR ; 
 scalar_t__ UBMR ; 
 scalar_t__ UCR1 ; 
 unsigned int UCR1_RRDYEN ; 
 unsigned int UCR1_RTSDEN ; 
 unsigned int UCR1_TXMPTYEN ; 
 scalar_t__ UCR2 ; 
 unsigned int UCR2_CTSC ; 
 unsigned int UCR2_IRTS ; 
 unsigned int UCR2_PREN ; 
 unsigned int UCR2_PROE ; 
 unsigned int UCR2_RXEN ; 
 unsigned int UCR2_SRST ; 
 unsigned int UCR2_STPB ; 
 unsigned int UCR2_TXEN ; 
 unsigned int UCR2_WS ; 
 scalar_t__ UFCR ; 
 unsigned int UFCR_RFDIV ; 
 unsigned int UFCR_RFDIV_REG (unsigned int) ; 
 int URXD_BRK ; 
 int URXD_FRMERR ; 
 int URXD_OVRRUN ; 
 int URXD_PRERR ; 
 scalar_t__ USE_IRDA (struct imx_port*) ; 
 scalar_t__ USR2 ; 
 unsigned int USR2_TXDC ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  cpu_is_mx1 () ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_div (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  imx_enable_ms (TYPE_5__*) ; 
 int /*<<< orphan*/  rational_best_approximation (int,unsigned int,int,int,unsigned long*,unsigned long*) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_encode_baud_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int,int) ; 
 unsigned int uart_get_divisor (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,int,unsigned int) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void
imx_set_termios(struct uart_port *port, struct ktermios *termios,
		   struct ktermios *old)
{
	struct imx_port *sport = (struct imx_port *)port;
	unsigned long flags;
	unsigned int ucr2, old_ucr1, old_txrxen, baud, quot;
	unsigned int old_csize = old ? old->c_cflag & CSIZE : CS8;
	unsigned int div, ufcr;
	unsigned long num, denom;
	uint64_t tdiv64;

	/*
	 * If we don't support modem control lines, don't allow
	 * these to be set.
	 */
	if (0) {
		termios->c_cflag &= ~(HUPCL | CRTSCTS | CMSPAR);
		termios->c_cflag |= CLOCAL;
	}

	/*
	 * We only support CS7 and CS8.
	 */
	while ((termios->c_cflag & CSIZE) != CS7 &&
	       (termios->c_cflag & CSIZE) != CS8) {
		termios->c_cflag &= ~CSIZE;
		termios->c_cflag |= old_csize;
		old_csize = CS8;
	}

	if ((termios->c_cflag & CSIZE) == CS8)
		ucr2 = UCR2_WS | UCR2_SRST | UCR2_IRTS;
	else
		ucr2 = UCR2_SRST | UCR2_IRTS;

	if (termios->c_cflag & CRTSCTS) {
		if( sport->have_rtscts ) {
			ucr2 &= ~UCR2_IRTS;
			ucr2 |= UCR2_CTSC;
		} else {
			termios->c_cflag &= ~CRTSCTS;
		}
	}

	if (termios->c_cflag & CSTOPB)
		ucr2 |= UCR2_STPB;
	if (termios->c_cflag & PARENB) {
		ucr2 |= UCR2_PREN;
		if (termios->c_cflag & PARODD)
			ucr2 |= UCR2_PROE;
	}

	/*
	 * Ask the core to calculate the divisor for us.
	 */
	baud = uart_get_baud_rate(port, termios, old, 50, port->uartclk / 16);
	quot = uart_get_divisor(port, baud);

	spin_lock_irqsave(&sport->port.lock, flags);

	sport->port.read_status_mask = 0;
	if (termios->c_iflag & INPCK)
		sport->port.read_status_mask |= (URXD_FRMERR | URXD_PRERR);
	if (termios->c_iflag & (BRKINT | PARMRK))
		sport->port.read_status_mask |= URXD_BRK;

	/*
	 * Characters to ignore
	 */
	sport->port.ignore_status_mask = 0;
	if (termios->c_iflag & IGNPAR)
		sport->port.ignore_status_mask |= URXD_PRERR;
	if (termios->c_iflag & IGNBRK) {
		sport->port.ignore_status_mask |= URXD_BRK;
		/*
		 * If we're ignoring parity and break indicators,
		 * ignore overruns too (for real raw support).
		 */
		if (termios->c_iflag & IGNPAR)
			sport->port.ignore_status_mask |= URXD_OVRRUN;
	}

	del_timer_sync(&sport->timer);

	/*
	 * Update the per-port timeout.
	 */
	uart_update_timeout(port, termios->c_cflag, baud);

	/*
	 * disable interrupts and drain transmitter
	 */
	old_ucr1 = readl(sport->port.membase + UCR1);
	writel(old_ucr1 & ~(UCR1_TXMPTYEN | UCR1_RRDYEN | UCR1_RTSDEN),
			sport->port.membase + UCR1);

	while ( !(readl(sport->port.membase + USR2) & USR2_TXDC))
		barrier();

	/* then, disable everything */
	old_txrxen = readl(sport->port.membase + UCR2);
	writel(old_txrxen & ~( UCR2_TXEN | UCR2_RXEN),
			sport->port.membase + UCR2);
	old_txrxen &= (UCR2_TXEN | UCR2_RXEN);

	if (USE_IRDA(sport)) {
		/*
		 * use maximum available submodule frequency to
		 * avoid missing short pulses due to low sampling rate
		 */
		div = 1;
	} else {
		div = sport->port.uartclk / (baud * 16);
		if (div > 7)
			div = 7;
		if (!div)
			div = 1;
	}

	rational_best_approximation(16 * div * baud, sport->port.uartclk,
		1 << 16, 1 << 16, &num, &denom);

	if (port->state && port->state->port.tty) {
		tdiv64 = sport->port.uartclk;
		tdiv64 *= num;
		do_div(tdiv64, denom * 16 * div);
		tty_encode_baud_rate(sport->port.state->port.tty,
				(speed_t)tdiv64, (speed_t)tdiv64);
	}

	num -= 1;
	denom -= 1;

	ufcr = readl(sport->port.membase + UFCR);
	ufcr = (ufcr & (~UFCR_RFDIV)) | UFCR_RFDIV_REG(div);
	writel(ufcr, sport->port.membase + UFCR);

	writel(num, sport->port.membase + UBIR);
	writel(denom, sport->port.membase + UBMR);

	if (!cpu_is_mx1())
		writel(sport->port.uartclk / div / 1000,
				sport->port.membase + MX2_ONEMS);

	writel(old_ucr1, sport->port.membase + UCR1);

	/* set the parity, stop bits and data size */
	writel(ucr2 | old_txrxen, sport->port.membase + UCR2);

	if (UART_ENABLE_MS(&sport->port, termios->c_cflag))
		imx_enable_ms(&sport->port);

	spin_unlock_irqrestore(&sport->port.lock, flags);
}