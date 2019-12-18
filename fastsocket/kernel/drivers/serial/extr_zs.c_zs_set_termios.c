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
struct zs_scc {int /*<<< orphan*/  zlock; struct zs_port* zport; } ;
struct zs_port {int* regs; int clk_mode; struct zs_scc* scc; } ;
struct uart_port {int uartclk; int read_status_mask; int ignore_status_mask; } ;
struct ktermios {int c_cflag; int c_iflag; } ;

/* Variables and functions */
 int BRKINT ; 
 int /*<<< orphan*/  BUG () ; 
 int CLOCAL ; 
 int CREAD ; 
 int CRTSCTS ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 int CSIZE ; 
 int CSTOPB ; 
 unsigned int CTSIE ; 
 unsigned int DCDIE ; 
 int FRM_ERR ; 
 int IGNBRK ; 
 int IGNPAR ; 
 int INPCK ; 
 int PARENB ; 
 int PARMRK ; 
 int PARODD ; 
 int PAR_ENA ; 
 int PAR_ERR ; 
 int PAR_EVEN ; 
 int Rx5 ; 
 int Rx6 ; 
 int Rx7 ; 
 int Rx8 ; 
 unsigned int RxENABLE ; 
 int RxNBITS_MASK ; 
 int Rx_BRK ; 
 int Rx_OVR ; 
 int SB1 ; 
 int SB2 ; 
 int SB_MASK ; 
 int Tx5 ; 
 int Tx6 ; 
 int Tx7 ; 
 int Tx8 ; 
 int TxNBITS_MASK ; 
 int X16CLK ; 
 int X1CLK ; 
 int X32CLK ; 
 int X64CLK ; 
 int XCLK_MASK ; 
 unsigned int ZS_BPS_TO_BRG (unsigned int,int) ; 
 size_t ZS_CHAN_A ; 
 int /*<<< orphan*/  irqs_disabled_flags (unsigned long) ; 
 int /*<<< orphan*/  load_zsregs (struct zs_port*,unsigned int*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct zs_port* to_zport (struct uart_port*) ; 
 unsigned int uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,int,unsigned int) ; 
 int /*<<< orphan*/  zs_raw_xor_mctrl (struct zs_port*) ; 

__attribute__((used)) static void zs_set_termios(struct uart_port *uport, struct ktermios *termios,
			   struct ktermios *old_termios)
{
	struct zs_port *zport = to_zport(uport);
	struct zs_scc *scc = zport->scc;
	struct zs_port *zport_a = &scc->zport[ZS_CHAN_A];
	int irq;
	unsigned int baud, brg;
	unsigned long flags;

	spin_lock_irqsave(&scc->zlock, flags);
	irq = !irqs_disabled_flags(flags);

	/* Byte size.  */
	zport->regs[3] &= ~RxNBITS_MASK;
	zport->regs[5] &= ~TxNBITS_MASK;
	switch (termios->c_cflag & CSIZE) {
	case CS5:
		zport->regs[3] |= Rx5;
		zport->regs[5] |= Tx5;
		break;
	case CS6:
		zport->regs[3] |= Rx6;
		zport->regs[5] |= Tx6;
		break;
	case CS7:
		zport->regs[3] |= Rx7;
		zport->regs[5] |= Tx7;
		break;
	case CS8:
	default:
		zport->regs[3] |= Rx8;
		zport->regs[5] |= Tx8;
		break;
	}

	/* Parity and stop bits.  */
	zport->regs[4] &= ~(XCLK_MASK | SB_MASK | PAR_ENA | PAR_EVEN);
	if (termios->c_cflag & CSTOPB)
		zport->regs[4] |= SB2;
	else
		zport->regs[4] |= SB1;
	if (termios->c_cflag & PARENB)
		zport->regs[4] |= PAR_ENA;
	if (!(termios->c_cflag & PARODD))
		zport->regs[4] |= PAR_EVEN;
	switch (zport->clk_mode) {
	case 64:
		zport->regs[4] |= X64CLK;
		break;
	case 32:
		zport->regs[4] |= X32CLK;
		break;
	case 16:
		zport->regs[4] |= X16CLK;
		break;
	case 1:
		zport->regs[4] |= X1CLK;
		break;
	default:
		BUG();
	}

	baud = uart_get_baud_rate(uport, termios, old_termios, 0,
				  uport->uartclk / zport->clk_mode / 4);

	brg = ZS_BPS_TO_BRG(baud, uport->uartclk / zport->clk_mode);
	zport->regs[12] = brg & 0xff;
	zport->regs[13] = (brg >> 8) & 0xff;

	uart_update_timeout(uport, termios->c_cflag, baud);

	uport->read_status_mask = Rx_OVR;
	if (termios->c_iflag & INPCK)
		uport->read_status_mask |= FRM_ERR | PAR_ERR;
	if (termios->c_iflag & (BRKINT | PARMRK))
		uport->read_status_mask |= Rx_BRK;

	uport->ignore_status_mask = 0;
	if (termios->c_iflag & IGNPAR)
		uport->ignore_status_mask |= FRM_ERR | PAR_ERR;
	if (termios->c_iflag & IGNBRK) {
		uport->ignore_status_mask |= Rx_BRK;
		if (termios->c_iflag & IGNPAR)
			uport->ignore_status_mask |= Rx_OVR;
	}

	if (termios->c_cflag & CREAD)
		zport->regs[3] |= RxENABLE;
	else
		zport->regs[3] &= ~RxENABLE;

	if (zport != zport_a) {
		if (!(termios->c_cflag & CLOCAL)) {
			zport->regs[15] |= DCDIE;
		} else
			zport->regs[15] &= ~DCDIE;
		if (termios->c_cflag & CRTSCTS) {
			zport->regs[15] |= CTSIE;
		} else
			zport->regs[15] &= ~CTSIE;
		zs_raw_xor_mctrl(zport);
	}

	/* Load up the new values.  */
	load_zsregs(zport, zport->regs, irq);

	spin_unlock_irqrestore(&scc->zlock, flags);
}