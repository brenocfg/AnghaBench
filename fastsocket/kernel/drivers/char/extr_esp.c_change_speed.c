#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int flow_off; int flow_on; } ;
struct TYPE_16__ {int flags; TYPE_4__* tty; } ;
struct esp_struct {unsigned short io_port; int custom_divisor; int timeout; int read_status_mask; int ignore_status_mask; int /*<<< orphan*/  lock; TYPE_1__ config; TYPE_3__ port; } ;
struct TYPE_17__ {TYPE_2__* termios; } ;
struct TYPE_15__ {unsigned int c_cflag; } ;

/* Variables and functions */
 int ASYNC_CHECK_CD ; 
 int ASYNC_CTS_FLOW ; 
 int ASYNC_SPD_CUST ; 
 int ASYNC_SPD_MASK ; 
 int BASE_BAUD ; 
 unsigned int CLOCAL ; 
 unsigned int CMSPAR ; 
 unsigned int CRTSCTS ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 unsigned int CSIZE ; 
 unsigned int CSTOPB ; 
 int ESI_SET_BAUD ; 
 int ESI_SET_FLOW_CHARS ; 
 int ESI_SET_FLOW_CNTL ; 
 int ESI_SET_FLOW_LVL ; 
 int ESI_WRITE_UART ; 
 int HZ ; 
 scalar_t__ I_BRKINT (TYPE_4__*) ; 
 scalar_t__ I_IGNBRK (TYPE_4__*) ; 
 scalar_t__ I_IGNPAR (TYPE_4__*) ; 
 scalar_t__ I_INPCK (TYPE_4__*) ; 
 scalar_t__ I_IXOFF (TYPE_4__*) ; 
 scalar_t__ I_PARMRK (TYPE_4__*) ; 
 unsigned int PARENB ; 
 unsigned int PARODD ; 
 int START_CHAR (TYPE_4__*) ; 
 int STOP_CHAR (TYPE_4__*) ; 
 int /*<<< orphan*/  UART_ESI_CMD1 ; 
 int /*<<< orphan*/  UART_ESI_CMD2 ; 
 int UART_LCR ; 
 unsigned int UART_LCR_EPAR ; 
 unsigned int UART_LCR_PARITY ; 
 unsigned int UART_LCR_SPAR ; 
 int UART_LSR_BI ; 
 int UART_LSR_DR ; 
 int UART_LSR_FE ; 
 int UART_LSR_OE ; 
 int UART_LSR_PE ; 
 int UART_LSR_THRE ; 
 int /*<<< orphan*/  serial_out (struct esp_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_encode_baud_rate (TYPE_4__*,int,int) ; 
 int tty_get_baud_rate (TYPE_4__*) ; 

__attribute__((used)) static void change_speed(struct esp_struct *info)
{
	unsigned short port;
	int	quot = 0;
	unsigned cflag, cval;
	int	baud, bits;
	unsigned char flow1 = 0, flow2 = 0;
	unsigned long flags;

	if (!info->port.tty || !info->port.tty->termios)
		return;
	cflag = info->port.tty->termios->c_cflag;
	port = info->io_port;

	/* byte size and parity */
	switch (cflag & CSIZE) {
	case CS5: cval = 0x00; bits = 7; break;
	case CS6: cval = 0x01; bits = 8; break;
	case CS7: cval = 0x02; bits = 9; break;
	case CS8: cval = 0x03; bits = 10; break;
	default:  cval = 0x00; bits = 7; break;
	}
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
	baud = tty_get_baud_rate(info->port.tty);
	if (baud == 38400 &&
		((info->port.flags & ASYNC_SPD_MASK) == ASYNC_SPD_CUST))
		quot = info->custom_divisor;
	else {
		if (baud == 134) /* Special case since 134 is really 134.5 */
			quot = (2*BASE_BAUD / 269);
		else if (baud)
			quot = BASE_BAUD / baud;
	}
	/* If the quotient is ever zero, default to 9600 bps */
	if (!quot)
		quot = BASE_BAUD / 9600;

	if (baud) {
		/* Actual rate */
		baud = BASE_BAUD/quot;
		tty_encode_baud_rate(info->port.tty, baud, baud);
	}
	info->timeout = ((1024 * HZ * bits * quot) / BASE_BAUD) + (HZ / 50);

	/* CTS flow control flag and modem status interrupts */
	/* info->IER &= ~UART_IER_MSI; */
	if (cflag & CRTSCTS) {
		info->port.flags |= ASYNC_CTS_FLOW;
		/* info->IER |= UART_IER_MSI; */
		flow1 = 0x04;
		flow2 = 0x10;
	} else
		info->port.flags &= ~ASYNC_CTS_FLOW;
	if (cflag & CLOCAL)
		info->port.flags &= ~ASYNC_CHECK_CD;
	else
		info->port.flags |= ASYNC_CHECK_CD;

	/*
	 * Set up parity check flag
	 */
	info->read_status_mask = UART_LSR_OE | UART_LSR_THRE | UART_LSR_DR;
	if (I_INPCK(info->port.tty))
		info->read_status_mask |= UART_LSR_FE | UART_LSR_PE;
	if (I_BRKINT(info->port.tty) || I_PARMRK(info->port.tty))
		info->read_status_mask |= UART_LSR_BI;

	info->ignore_status_mask = 0;
#if 0
	/* This should be safe, but for some broken bits of hardware... */
	if (I_IGNPAR(info->port.tty)) {
		info->ignore_status_mask |= UART_LSR_PE | UART_LSR_FE;
		info->read_status_mask |= UART_LSR_PE | UART_LSR_FE;
	}
#endif
	if (I_IGNBRK(info->port.tty)) {
		info->ignore_status_mask |= UART_LSR_BI;
		info->read_status_mask |= UART_LSR_BI;
		/*
		 * If we're ignore parity and break indicators, ignore
		 * overruns too.  (For real raw support).
		 */
		if (I_IGNPAR(info->port.tty)) {
			info->ignore_status_mask |= UART_LSR_OE | \
				UART_LSR_PE | UART_LSR_FE;
			info->read_status_mask |= UART_LSR_OE | \
				UART_LSR_PE | UART_LSR_FE;
		}
	}

	if (I_IXOFF(info->port.tty))
		flow1 |= 0x81;

	spin_lock_irqsave(&info->lock, flags);
	/* set baud */
	serial_out(info, UART_ESI_CMD1, ESI_SET_BAUD);
	serial_out(info, UART_ESI_CMD2, quot >> 8);
	serial_out(info, UART_ESI_CMD2, quot & 0xff);

	/* set data bits, parity, etc. */
	serial_out(info, UART_ESI_CMD1, ESI_WRITE_UART);
	serial_out(info, UART_ESI_CMD2, UART_LCR);
	serial_out(info, UART_ESI_CMD2, cval);

	/* Enable flow control */
	serial_out(info, UART_ESI_CMD1, ESI_SET_FLOW_CNTL);
	serial_out(info, UART_ESI_CMD2, flow1);
	serial_out(info, UART_ESI_CMD2, flow2);

	/* set flow control characters (XON/XOFF only) */
	if (I_IXOFF(info->port.tty)) {
		serial_out(info, UART_ESI_CMD1, ESI_SET_FLOW_CHARS);
		serial_out(info, UART_ESI_CMD2, START_CHAR(info->port.tty));
		serial_out(info, UART_ESI_CMD2, STOP_CHAR(info->port.tty));
		serial_out(info, UART_ESI_CMD2, 0x10);
		serial_out(info, UART_ESI_CMD2, 0x21);
		switch (cflag & CSIZE) {
		case CS5:
			serial_out(info, UART_ESI_CMD2, 0x1f);
			break;
		case CS6:
			serial_out(info, UART_ESI_CMD2, 0x3f);
			break;
		case CS7:
		case CS8:
			serial_out(info, UART_ESI_CMD2, 0x7f);
			break;
		default:
			serial_out(info, UART_ESI_CMD2, 0xff);
			break;
		}
	}

	/* Set high/low water */
	serial_out(info, UART_ESI_CMD1, ESI_SET_FLOW_LVL);
	serial_out(info, UART_ESI_CMD2, info->config.flow_off >> 8);
	serial_out(info, UART_ESI_CMD2, info->config.flow_off);
	serial_out(info, UART_ESI_CMD2, info->config.flow_on >> 8);
	serial_out(info, UART_ESI_CMD2, info->config.flow_on);

	spin_unlock_irqrestore(&info->lock, flags);
}