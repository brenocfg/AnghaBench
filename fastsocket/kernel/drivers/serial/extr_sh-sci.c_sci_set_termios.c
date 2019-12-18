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
struct uart_port {int uartclk; scalar_t__ type; } ;
struct ktermios {int c_cflag; } ;

/* Variables and functions */
 int CREAD ; 
 int CRTSCTS ; 
 int CS7 ; 
 int CSIZE ; 
 int CSTOPB ; 
 int PARENB ; 
 int PARODD ; 
 scalar_t__ PORT_SCI ; 
 int /*<<< orphan*/  SCBRR ; 
 int SCBRR_VALUE (unsigned int,int) ; 
 int /*<<< orphan*/  SCFCR ; 
 int SCFCR_MCE ; 
 int SCFCR_RFRST ; 
 int SCFCR_TFRST ; 
 int /*<<< orphan*/  SCSCR ; 
 int SCSCR_INIT (struct uart_port*) ; 
 int /*<<< orphan*/  SCSMR ; 
 int /*<<< orphan*/  SCxSR ; 
 unsigned int SCxSR_TEND (struct uart_port*) ; 
 scalar_t__ likely (unsigned int) ; 
 int sci_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_init_pins (struct uart_port*,int) ; 
 int /*<<< orphan*/  sci_out (struct uart_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sci_start_rx (struct uart_port*,int /*<<< orphan*/ ) ; 
 unsigned int uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,int,unsigned int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void sci_set_termios(struct uart_port *port, struct ktermios *termios,
			    struct ktermios *old)
{
	unsigned int status, baud, smr_val;
	int t = -1;

	baud = uart_get_baud_rate(port, termios, old, 0, port->uartclk/16);
	if (likely(baud))
		t = SCBRR_VALUE(baud, port->uartclk);

	do {
		status = sci_in(port, SCxSR);
	} while (!(status & SCxSR_TEND(port)));

	sci_out(port, SCSCR, 0x00);	/* TE=0, RE=0, CKE1=0 */

	if (port->type != PORT_SCI)
		sci_out(port, SCFCR, SCFCR_RFRST | SCFCR_TFRST);

	smr_val = sci_in(port, SCSMR) & 3;
	if ((termios->c_cflag & CSIZE) == CS7)
		smr_val |= 0x40;
	if (termios->c_cflag & PARENB)
		smr_val |= 0x20;
	if (termios->c_cflag & PARODD)
		smr_val |= 0x30;
	if (termios->c_cflag & CSTOPB)
		smr_val |= 0x08;

	uart_update_timeout(port, termios->c_cflag, baud);

	sci_out(port, SCSMR, smr_val);

	if (t > 0) {
		if (t >= 256) {
			sci_out(port, SCSMR, (sci_in(port, SCSMR) & ~3) | 1);
			t >>= 2;
		} else
			sci_out(port, SCSMR, sci_in(port, SCSMR) & ~3);

		sci_out(port, SCBRR, t);
		udelay((1000000+(baud-1)) / baud); /* Wait one bit interval */
	}

	sci_init_pins(port, termios->c_cflag);
	sci_out(port, SCFCR, (termios->c_cflag & CRTSCTS) ? SCFCR_MCE : 0);

	sci_out(port, SCSCR, SCSCR_INIT(port));

	if ((termios->c_cflag & CREAD) != 0)
		sci_start_rx(port, 0);
}