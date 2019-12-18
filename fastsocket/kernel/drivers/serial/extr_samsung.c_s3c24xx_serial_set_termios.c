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
struct uart_port {int flags; unsigned int custom_divisor; int read_status_mask; int ignore_status_mask; int /*<<< orphan*/  lock; } ;
struct s3c24xx_uart_port {unsigned int baudclk_rate; TYPE_1__* info; struct clk* baudclk; struct s3c24xx_uart_clksrc* clksrc; } ;
struct s3c24xx_uart_clksrc {int dummy; } ;
struct s3c2410_uartcfg {unsigned int ulcon; } ;
struct ktermios {int c_cflag; int c_iflag; } ;
struct clk {int dummy; } ;
struct TYPE_2__ {scalar_t__ has_divslot; } ;

/* Variables and functions */
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
 int /*<<< orphan*/  IS_ERR (struct clk*) ; 
 int PARENB ; 
 int PARODD ; 
 int RXSTAT_DUMMY_READ ; 
 unsigned int S3C2410_LCON_CS5 ; 
 unsigned int S3C2410_LCON_CS6 ; 
 unsigned int S3C2410_LCON_CS7 ; 
 unsigned int S3C2410_LCON_CS8 ; 
 unsigned int S3C2410_LCON_IRM ; 
 unsigned int S3C2410_LCON_PEVEN ; 
 unsigned int S3C2410_LCON_PNONE ; 
 unsigned int S3C2410_LCON_PODD ; 
 unsigned int S3C2410_LCON_STOPB ; 
 int /*<<< orphan*/  S3C2410_UBRDIV ; 
 int /*<<< orphan*/  S3C2410_UCON ; 
 int S3C2410_UERSTAT_FRAME ; 
 int S3C2410_UERSTAT_OVERRUN ; 
 int S3C2410_UERSTAT_PARITY ; 
 int /*<<< orphan*/  S3C2410_UFCON ; 
 int /*<<< orphan*/  S3C2410_ULCON ; 
 unsigned int S3C2410_UMCOM_AFC ; 
 int /*<<< orphan*/  S3C2410_UMCON ; 
 int /*<<< orphan*/  S3C2443_DIVSLOT ; 
 int UPF_SPD_CUST ; 
 int UPF_SPD_MASK ; 
 int /*<<< orphan*/  clk_disable (struct clk*) ; 
 int /*<<< orphan*/  clk_enable (struct clk*) ; 
 unsigned int clk_get_rate (struct clk*) ; 
 int /*<<< orphan*/  dbg (char*,...) ; 
 unsigned int rd_regl (struct uart_port*,int /*<<< orphan*/ ) ; 
 struct s3c2410_uartcfg* s3c24xx_port_to_cfg (struct uart_port*) ; 
 unsigned int s3c24xx_serial_getclk (struct uart_port*,struct s3c24xx_uart_clksrc**,struct clk**,unsigned int) ; 
 int /*<<< orphan*/  s3c24xx_serial_setsource (struct uart_port*,struct s3c24xx_uart_clksrc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct s3c24xx_uart_port* to_ourport (struct uart_port*) ; 
 unsigned int uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,int,unsigned int) ; 
 unsigned int* udivslot_table ; 
 int /*<<< orphan*/  wr_regl (struct uart_port*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void s3c24xx_serial_set_termios(struct uart_port *port,
				       struct ktermios *termios,
				       struct ktermios *old)
{
	struct s3c2410_uartcfg *cfg = s3c24xx_port_to_cfg(port);
	struct s3c24xx_uart_port *ourport = to_ourport(port);
	struct s3c24xx_uart_clksrc *clksrc = NULL;
	struct clk *clk = NULL;
	unsigned long flags;
	unsigned int baud, quot;
	unsigned int ulcon;
	unsigned int umcon;
	unsigned int udivslot = 0;

	/*
	 * We don't support modem control lines.
	 */
	termios->c_cflag &= ~(HUPCL | CMSPAR);
	termios->c_cflag |= CLOCAL;

	/*
	 * Ask the core to calculate the divisor for us.
	 */

	baud = uart_get_baud_rate(port, termios, old, 0, 115200*8);

	if (baud == 38400 && (port->flags & UPF_SPD_MASK) == UPF_SPD_CUST)
		quot = port->custom_divisor;
	else
		quot = s3c24xx_serial_getclk(port, &clksrc, &clk, baud);

	/* check to see if we need  to change clock source */

	if (ourport->clksrc != clksrc || ourport->baudclk != clk) {
		dbg("selecting clock %p\n", clk);
		s3c24xx_serial_setsource(port, clksrc);

		if (ourport->baudclk != NULL && !IS_ERR(ourport->baudclk)) {
			clk_disable(ourport->baudclk);
			ourport->baudclk  = NULL;
		}

		clk_enable(clk);

		ourport->clksrc = clksrc;
		ourport->baudclk = clk;
		ourport->baudclk_rate = clk ? clk_get_rate(clk) : 0;
	}

	if (ourport->info->has_divslot) {
		unsigned int div = ourport->baudclk_rate / baud;

		udivslot = udivslot_table[div & 15];
		dbg("udivslot = %04x (div %d)\n", udivslot, div & 15);
	}

	switch (termios->c_cflag & CSIZE) {
	case CS5:
		dbg("config: 5bits/char\n");
		ulcon = S3C2410_LCON_CS5;
		break;
	case CS6:
		dbg("config: 6bits/char\n");
		ulcon = S3C2410_LCON_CS6;
		break;
	case CS7:
		dbg("config: 7bits/char\n");
		ulcon = S3C2410_LCON_CS7;
		break;
	case CS8:
	default:
		dbg("config: 8bits/char\n");
		ulcon = S3C2410_LCON_CS8;
		break;
	}

	/* preserve original lcon IR settings */
	ulcon |= (cfg->ulcon & S3C2410_LCON_IRM);

	if (termios->c_cflag & CSTOPB)
		ulcon |= S3C2410_LCON_STOPB;

	umcon = (termios->c_cflag & CRTSCTS) ? S3C2410_UMCOM_AFC : 0;

	if (termios->c_cflag & PARENB) {
		if (termios->c_cflag & PARODD)
			ulcon |= S3C2410_LCON_PODD;
		else
			ulcon |= S3C2410_LCON_PEVEN;
	} else {
		ulcon |= S3C2410_LCON_PNONE;
	}

	spin_lock_irqsave(&port->lock, flags);

	dbg("setting ulcon to %08x, brddiv to %d, udivslot %08x\n",
	    ulcon, quot, udivslot);

	wr_regl(port, S3C2410_ULCON, ulcon);
	wr_regl(port, S3C2410_UBRDIV, quot);
	wr_regl(port, S3C2410_UMCON, umcon);

	if (ourport->info->has_divslot)
		wr_regl(port, S3C2443_DIVSLOT, udivslot);

	dbg("uart: ulcon = 0x%08x, ucon = 0x%08x, ufcon = 0x%08x\n",
	    rd_regl(port, S3C2410_ULCON),
	    rd_regl(port, S3C2410_UCON),
	    rd_regl(port, S3C2410_UFCON));

	/*
	 * Update the per-port timeout.
	 */
	uart_update_timeout(port, termios->c_cflag, baud);

	/*
	 * Which character status flags are we interested in?
	 */
	port->read_status_mask = S3C2410_UERSTAT_OVERRUN;
	if (termios->c_iflag & INPCK)
		port->read_status_mask |= S3C2410_UERSTAT_FRAME | S3C2410_UERSTAT_PARITY;

	/*
	 * Which character status flags should we ignore?
	 */
	port->ignore_status_mask = 0;
	if (termios->c_iflag & IGNPAR)
		port->ignore_status_mask |= S3C2410_UERSTAT_OVERRUN;
	if (termios->c_iflag & IGNBRK && termios->c_iflag & IGNPAR)
		port->ignore_status_mask |= S3C2410_UERSTAT_FRAME;

	/*
	 * Ignore all characters if CREAD is not set.
	 */
	if ((termios->c_cflag & CREAD) == 0)
		port->ignore_status_mask |= RXSTAT_DUMMY_READ;

	spin_unlock_irqrestore(&port->lock, flags);
}