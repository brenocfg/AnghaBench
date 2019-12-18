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
struct TYPE_2__ {int flags; int iobase; int /*<<< orphan*/  irq; int /*<<< orphan*/  lock; int /*<<< orphan*/  mctrl; } ;
struct uart_sunsu_port {TYPE_1__ port; scalar_t__ ier; } ;
struct uart_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIOCM_OUT1 ; 
 int /*<<< orphan*/  TIOCM_OUT2 ; 
 int /*<<< orphan*/  UART_FCR ; 
 int UART_FCR_CLEAR_RCVR ; 
 int UART_FCR_CLEAR_XMIT ; 
 int UART_FCR_ENABLE_FIFO ; 
 int /*<<< orphan*/  UART_IER ; 
 int /*<<< orphan*/  UART_LCR ; 
 int UART_LCR_SBC ; 
 int /*<<< orphan*/  UART_RX ; 
 int UPF_FOURPORT ; 
 int /*<<< orphan*/  disable_rsa (struct uart_sunsu_port*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uart_sunsu_port*) ; 
 int /*<<< orphan*/  inb (int) ; 
 int /*<<< orphan*/  serial_in (struct uart_sunsu_port*,int /*<<< orphan*/ ) ; 
 int serial_inp (struct uart_sunsu_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_out (struct uart_sunsu_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  serial_outp (struct uart_sunsu_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sunsu_set_mctrl (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sunsu_shutdown(struct uart_port *port)
{
	struct uart_sunsu_port *up = (struct uart_sunsu_port *) port;
	unsigned long flags;

	/*
	 * Disable interrupts from this port
	 */
	up->ier = 0;
	serial_outp(up, UART_IER, 0);

	spin_lock_irqsave(&up->port.lock, flags);
	if (up->port.flags & UPF_FOURPORT) {
		/* reset interrupts on the AST Fourport board */
		inb((up->port.iobase & 0xfe0) | 0x1f);
		up->port.mctrl |= TIOCM_OUT1;
	} else
		up->port.mctrl &= ~TIOCM_OUT2;

	sunsu_set_mctrl(&up->port, up->port.mctrl);
	spin_unlock_irqrestore(&up->port.lock, flags);

	/*
	 * Disable break condition and FIFOs
	 */
	serial_out(up, UART_LCR, serial_inp(up, UART_LCR) & ~UART_LCR_SBC);
	serial_outp(up, UART_FCR, UART_FCR_ENABLE_FIFO |
				  UART_FCR_CLEAR_RCVR |
				  UART_FCR_CLEAR_XMIT);
	serial_outp(up, UART_FCR, 0);

#ifdef CONFIG_SERIAL_8250_RSA
	/*
	 * Reset the RSA board back to 115kbps compat mode.
	 */
	disable_rsa(up);
#endif

	/*
	 * Read data port to reset things.
	 */
	(void) serial_in(up, UART_RX);

	free_irq(up->port.irq, up);
}