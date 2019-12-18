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
typedef  int /*<<< orphan*/  ulong ;
typedef  int /*<<< orphan*/  u32 ;
struct uart_port {int /*<<< orphan*/  uartclk; } ;
struct TYPE_2__ {int read_status_mask; int ignore_status_mask; int /*<<< orphan*/  lock; } ;
struct mpsc_port_info {int c_iflag; int c_cflag; int rcv_data; TYPE_1__ port; } ;
struct ktermios {int c_iflag; int c_cflag; } ;

/* Variables and functions */
 int BRKINT ; 
 int CMSPAR ; 
 int CREAD ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 int CSIZE ; 
 int CSTOPB ; 
 int IGNBRK ; 
 int IGNPAR ; 
 int INPCK ; 
 int /*<<< orphan*/  MPSC_CHR_2_PAR_EVEN ; 
 int /*<<< orphan*/  MPSC_CHR_2_PAR_MARK ; 
 int /*<<< orphan*/  MPSC_CHR_2_PAR_ODD ; 
 int /*<<< orphan*/  MPSC_CHR_2_PAR_SPACE ; 
 int /*<<< orphan*/  MPSC_MPCR_CL_5 ; 
 int /*<<< orphan*/  MPSC_MPCR_CL_6 ; 
 int /*<<< orphan*/  MPSC_MPCR_CL_7 ; 
 int /*<<< orphan*/  MPSC_MPCR_CL_8 ; 
 int /*<<< orphan*/  MPSC_MPCR_SBL_1 ; 
 int /*<<< orphan*/  MPSC_MPCR_SBL_2 ; 
 int PARENB ; 
 int PARMRK ; 
 int PARODD ; 
 int SDMA_DESC_CMDSTAT_BR ; 
 int SDMA_DESC_CMDSTAT_FR ; 
 int SDMA_DESC_CMDSTAT_OR ; 
 int SDMA_DESC_CMDSTAT_PE ; 
 int /*<<< orphan*/  mpsc_set_baudrate (struct mpsc_port_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpsc_set_char_length (struct mpsc_port_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpsc_set_parity (struct mpsc_port_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpsc_set_stop_bit_length (struct mpsc_port_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpsc_start_rx (struct mpsc_port_info*) ; 
 int /*<<< orphan*/  mpsc_stop_rx (struct uart_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mpsc_set_termios(struct uart_port *port, struct ktermios *termios,
		 struct ktermios *old)
{
	struct mpsc_port_info *pi = (struct mpsc_port_info *)port;
	u32 baud;
	ulong flags;
	u32 chr_bits, stop_bits, par;

	pi->c_iflag = termios->c_iflag;
	pi->c_cflag = termios->c_cflag;

	switch (termios->c_cflag & CSIZE) {
	case CS5:
		chr_bits = MPSC_MPCR_CL_5;
		break;
	case CS6:
		chr_bits = MPSC_MPCR_CL_6;
		break;
	case CS7:
		chr_bits = MPSC_MPCR_CL_7;
		break;
	case CS8:
	default:
		chr_bits = MPSC_MPCR_CL_8;
		break;
	}

	if (termios->c_cflag & CSTOPB)
		stop_bits = MPSC_MPCR_SBL_2;
	else
		stop_bits = MPSC_MPCR_SBL_1;

	par = MPSC_CHR_2_PAR_EVEN;
	if (termios->c_cflag & PARENB)
		if (termios->c_cflag & PARODD)
			par = MPSC_CHR_2_PAR_ODD;
#ifdef	CMSPAR
		if (termios->c_cflag & CMSPAR) {
			if (termios->c_cflag & PARODD)
				par = MPSC_CHR_2_PAR_MARK;
			else
				par = MPSC_CHR_2_PAR_SPACE;
		}
#endif

	baud = uart_get_baud_rate(port, termios, old, 0, port->uartclk);

	spin_lock_irqsave(&pi->port.lock, flags);

	uart_update_timeout(port, termios->c_cflag, baud);

	mpsc_set_char_length(pi, chr_bits);
	mpsc_set_stop_bit_length(pi, stop_bits);
	mpsc_set_parity(pi, par);
	mpsc_set_baudrate(pi, baud);

	/* Characters/events to read */
	pi->port.read_status_mask = SDMA_DESC_CMDSTAT_OR;

	if (termios->c_iflag & INPCK)
		pi->port.read_status_mask |= SDMA_DESC_CMDSTAT_PE
			| SDMA_DESC_CMDSTAT_FR;

	if (termios->c_iflag & (BRKINT | PARMRK))
		pi->port.read_status_mask |= SDMA_DESC_CMDSTAT_BR;

	/* Characters/events to ignore */
	pi->port.ignore_status_mask = 0;

	if (termios->c_iflag & IGNPAR)
		pi->port.ignore_status_mask |= SDMA_DESC_CMDSTAT_PE
			| SDMA_DESC_CMDSTAT_FR;

	if (termios->c_iflag & IGNBRK) {
		pi->port.ignore_status_mask |= SDMA_DESC_CMDSTAT_BR;

		if (termios->c_iflag & IGNPAR)
			pi->port.ignore_status_mask |= SDMA_DESC_CMDSTAT_OR;
	}

	if ((termios->c_cflag & CREAD)) {
		if (!pi->rcv_data) {
			pi->rcv_data = 1;
			mpsc_start_rx(pi);
		}
	} else if (pi->rcv_data) {
		mpsc_stop_rx(port);
		pi->rcv_data = 0;
	}

	spin_unlock_irqrestore(&pi->port.lock, flags);
}