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
struct TYPE_2__ {int flags; int iobase; int irq; } ;
struct uart_8250_port {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_IER ; 
 int /*<<< orphan*/  UART_IIR ; 
 int /*<<< orphan*/  UART_LSR ; 
 int /*<<< orphan*/  UART_MCR ; 
 unsigned char UART_MCR_DTR ; 
 unsigned char UART_MCR_OUT1 ; 
 unsigned char UART_MCR_OUT2 ; 
 unsigned char UART_MCR_RTS ; 
 int /*<<< orphan*/  UART_MSR ; 
 int /*<<< orphan*/  UART_RX ; 
 int /*<<< orphan*/  UART_TX ; 
 int UPF_FOURPORT ; 
 unsigned char inb_p (unsigned int) ; 
 int /*<<< orphan*/  outb_p (unsigned char,unsigned int) ; 
 int probe_irq_off (unsigned long) ; 
 unsigned long probe_irq_on () ; 
 unsigned char serial_inp (struct uart_8250_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_outp (struct uart_8250_port*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void autoconfig_irq(struct uart_8250_port *up)
{
	unsigned char save_mcr, save_ier;
	unsigned char save_ICP = 0;
	unsigned int ICP = 0;
	unsigned long irqs;
	int irq;

	if (up->port.flags & UPF_FOURPORT) {
		ICP = (up->port.iobase & 0xfe0) | 0x1f;
		save_ICP = inb_p(ICP);
		outb_p(0x80, ICP);
		(void) inb_p(ICP);
	}

	/* forget possible initially masked and pending IRQ */
	probe_irq_off(probe_irq_on());
	save_mcr = serial_inp(up, UART_MCR);
	save_ier = serial_inp(up, UART_IER);
	serial_outp(up, UART_MCR, UART_MCR_OUT1 | UART_MCR_OUT2);

	irqs = probe_irq_on();
	serial_outp(up, UART_MCR, 0);
	udelay(10);
	if (up->port.flags & UPF_FOURPORT) {
		serial_outp(up, UART_MCR,
			    UART_MCR_DTR | UART_MCR_RTS);
	} else {
		serial_outp(up, UART_MCR,
			    UART_MCR_DTR | UART_MCR_RTS | UART_MCR_OUT2);
	}
	serial_outp(up, UART_IER, 0x0f);	/* enable all intrs */
	(void)serial_inp(up, UART_LSR);
	(void)serial_inp(up, UART_RX);
	(void)serial_inp(up, UART_IIR);
	(void)serial_inp(up, UART_MSR);
	serial_outp(up, UART_TX, 0xFF);
	udelay(20);
	irq = probe_irq_off(irqs);

	serial_outp(up, UART_MCR, save_mcr);
	serial_outp(up, UART_IER, save_ier);

	if (up->port.flags & UPF_FOURPORT)
		outb_p(save_ICP, ICP);

	up->port.irq = (irq > 0) ? irq : 0;
}