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
typedef  int u8 ;
struct uart_port {int read_status_mask; int ignore_status_mask; int uartclk; int /*<<< orphan*/  lock; } ;
struct ktermios {unsigned int c_iflag; unsigned int c_cflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACR ; 
 unsigned int BRKINT ; 
 int /*<<< orphan*/  CR ; 
 unsigned int CREAD ; 
 int CR_DIS_RX ; 
 int CR_DIS_TX ; 
 int CR_ENA_RX ; 
 int CR_ENA_TX ; 
 int CR_RES_MR ; 
 int CR_RES_RX ; 
 int CR_RES_TX ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 unsigned int CSIZE ; 
 int /*<<< orphan*/  CSR ; 
 unsigned int CSTOPB ; 
 unsigned int IGNBRK ; 
 unsigned int INPCK ; 
 int /*<<< orphan*/  MRx ; 
 unsigned int PARENB ; 
 unsigned int PARMRK ; 
 unsigned int PARODD ; 
 int READ_SC_PORT (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SR ; 
 int SR_BREAK ; 
 int SR_FRAME ; 
 int SR_OVERRUN ; 
 int SR_PARITY ; 
 int /*<<< orphan*/  WRITE_SC (struct uart_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WRITE_SC_PORT (struct uart_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int /*<<< orphan*/ ,int) ; 
 unsigned int uart_get_divisor (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,unsigned int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void sc26xx_set_termios(struct uart_port *port, struct ktermios *termios,
			      struct ktermios *old)
{
	unsigned int baud = uart_get_baud_rate(port, termios, old, 0, 4000000);
	unsigned int quot = uart_get_divisor(port, baud);
	unsigned int iflag, cflag;
	unsigned long flags;
	u8 mr1, mr2, csr;

	spin_lock_irqsave(&port->lock, flags);

	while ((READ_SC_PORT(port, SR) & ((1 << 3) | (1 << 2))) != 0xc)
		udelay(2);

	WRITE_SC_PORT(port, CR, CR_DIS_TX | CR_DIS_RX);

	iflag = termios->c_iflag;
	cflag = termios->c_cflag;

	port->read_status_mask = SR_OVERRUN;
	if (iflag & INPCK)
		port->read_status_mask |= SR_PARITY | SR_FRAME;
	if (iflag & (BRKINT | PARMRK))
		port->read_status_mask |= SR_BREAK;

	port->ignore_status_mask = 0;
	if (iflag & IGNBRK)
		port->ignore_status_mask |= SR_BREAK;
	if ((cflag & CREAD) == 0)
		port->ignore_status_mask |= SR_BREAK | SR_FRAME |
					    SR_PARITY | SR_OVERRUN;

	switch (cflag & CSIZE) {
	case CS5:
		mr1 = 0x00;
		break;
	case CS6:
		mr1 = 0x01;
		break;
	case CS7:
		mr1 = 0x02;
		break;
	default:
	case CS8:
		mr1 = 0x03;
		break;
	}
	mr2 = 0x07;
	if (cflag & CSTOPB)
		mr2 = 0x0f;
	if (cflag & PARENB) {
		if (cflag & PARODD)
			mr1 |= (1 << 2);
	} else
		mr1 |= (2 << 3);

	switch (baud) {
	case 50:
		csr = 0x00;
		break;
	case 110:
		csr = 0x11;
		break;
	case 134:
		csr = 0x22;
		break;
	case 200:
		csr = 0x33;
		break;
	case 300:
		csr = 0x44;
		break;
	case 600:
		csr = 0x55;
		break;
	case 1200:
		csr = 0x66;
		break;
	case 2400:
		csr = 0x88;
		break;
	case 4800:
		csr = 0x99;
		break;
	default:
	case 9600:
		csr = 0xbb;
		break;
	case 19200:
		csr = 0xcc;
		break;
	}

	WRITE_SC_PORT(port, CR, CR_RES_MR);
	WRITE_SC_PORT(port, MRx, mr1);
	WRITE_SC_PORT(port, MRx, mr2);

	WRITE_SC(port, ACR, 0x80);
	WRITE_SC_PORT(port, CSR, csr);

	/* reset tx and rx */
	WRITE_SC_PORT(port, CR, CR_RES_RX);
	WRITE_SC_PORT(port, CR, CR_RES_TX);

	WRITE_SC_PORT(port, CR, CR_ENA_TX | CR_ENA_RX);
	while ((READ_SC_PORT(port, SR) & ((1 << 3) | (1 << 2))) != 0xc)
		udelay(2);

	/* XXX */
	uart_update_timeout(port, cflag,
			    (port->uartclk / (16 * quot)));

	spin_unlock_irqrestore(&port->lock, flags);
}