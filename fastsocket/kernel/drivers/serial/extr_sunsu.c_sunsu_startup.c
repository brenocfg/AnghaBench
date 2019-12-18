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
struct TYPE_4__ {size_t type; int flags; int iobase; int /*<<< orphan*/  lock; int /*<<< orphan*/  mctrl; int /*<<< orphan*/  irq; int /*<<< orphan*/  line; } ;
struct uart_sunsu_port {size_t su_type; int ier; TYPE_2__ port; scalar_t__ acr; } ;
struct uart_port {int dummy; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 size_t PORT_16C950 ; 
 size_t SU_PORT_PORT ; 
 int /*<<< orphan*/  TIOCM_OUT2 ; 
 int UART_CLEAR_FIFO ; 
 int /*<<< orphan*/  UART_CSR ; 
 int /*<<< orphan*/  UART_EFR ; 
 int UART_EFR_ECB ; 
 int /*<<< orphan*/  UART_FCR ; 
 int UART_FCR_CLEAR_RCVR ; 
 int UART_FCR_CLEAR_XMIT ; 
 int UART_FCR_ENABLE_FIFO ; 
 int /*<<< orphan*/  UART_IER ; 
 int UART_IER_RDI ; 
 int UART_IER_RLSI ; 
 int /*<<< orphan*/  UART_IIR ; 
 int /*<<< orphan*/  UART_LCR ; 
 int UART_LCR_WLEN8 ; 
 int /*<<< orphan*/  UART_LSR ; 
 int /*<<< orphan*/  UART_MSR ; 
 int /*<<< orphan*/  UART_RX ; 
 int UPF_BUGGY_UART ; 
 int UPF_FOURPORT ; 
 int /*<<< orphan*/  enable_rsa (struct uart_sunsu_port*) ; 
 int /*<<< orphan*/  inb_p (unsigned int) ; 
 int /*<<< orphan*/  outb_p (int,unsigned int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uart_sunsu_port*) ; 
 int /*<<< orphan*/  serial_icr_write (struct uart_sunsu_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int serial_inp (struct uart_sunsu_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_outp (struct uart_sunsu_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * su_typev ; 
 int /*<<< orphan*/  sunsu_kbd_ms_interrupt ; 
 int /*<<< orphan*/  sunsu_serial_interrupt ; 
 int /*<<< orphan*/  sunsu_set_mctrl (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* uart_config ; 

__attribute__((used)) static int sunsu_startup(struct uart_port *port)
{
	struct uart_sunsu_port *up = (struct uart_sunsu_port *) port;
	unsigned long flags;
	int retval;

	if (up->port.type == PORT_16C950) {
		/* Wake up and initialize UART */
		up->acr = 0;
		serial_outp(up, UART_LCR, 0xBF);
		serial_outp(up, UART_EFR, UART_EFR_ECB);
		serial_outp(up, UART_IER, 0);
		serial_outp(up, UART_LCR, 0);
		serial_icr_write(up, UART_CSR, 0); /* Reset the UART */
		serial_outp(up, UART_LCR, 0xBF);
		serial_outp(up, UART_EFR, UART_EFR_ECB);
		serial_outp(up, UART_LCR, 0);
	}

#ifdef CONFIG_SERIAL_8250_RSA
	/*
	 * If this is an RSA port, see if we can kick it up to the
	 * higher speed clock.
	 */
	enable_rsa(up);
#endif

	/*
	 * Clear the FIFO buffers and disable them.
	 * (they will be reenabled in set_termios())
	 */
	if (uart_config[up->port.type].flags & UART_CLEAR_FIFO) {
		serial_outp(up, UART_FCR, UART_FCR_ENABLE_FIFO);
		serial_outp(up, UART_FCR, UART_FCR_ENABLE_FIFO |
				UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT);
		serial_outp(up, UART_FCR, 0);
	}

	/*
	 * Clear the interrupt registers.
	 */
	(void) serial_inp(up, UART_LSR);
	(void) serial_inp(up, UART_RX);
	(void) serial_inp(up, UART_IIR);
	(void) serial_inp(up, UART_MSR);

	/*
	 * At this point, there's no way the LSR could still be 0xff;
	 * if it is, then bail out, because there's likely no UART
	 * here.
	 */
	if (!(up->port.flags & UPF_BUGGY_UART) &&
	    (serial_inp(up, UART_LSR) == 0xff)) {
		printk("ttyS%d: LSR safety check engaged!\n", up->port.line);
		return -ENODEV;
	}

	if (up->su_type != SU_PORT_PORT) {
		retval = request_irq(up->port.irq, sunsu_kbd_ms_interrupt,
				     IRQF_SHARED, su_typev[up->su_type], up);
	} else {
		retval = request_irq(up->port.irq, sunsu_serial_interrupt,
				     IRQF_SHARED, su_typev[up->su_type], up);
	}
	if (retval) {
		printk("su: Cannot register IRQ %d\n", up->port.irq);
		return retval;
	}

	/*
	 * Now, initialize the UART
	 */
	serial_outp(up, UART_LCR, UART_LCR_WLEN8);

	spin_lock_irqsave(&up->port.lock, flags);

	up->port.mctrl |= TIOCM_OUT2;

	sunsu_set_mctrl(&up->port, up->port.mctrl);
	spin_unlock_irqrestore(&up->port.lock, flags);

	/*
	 * Finally, enable interrupts.  Note: Modem status interrupts
	 * are set via set_termios(), which will be occurring imminently
	 * anyway, so we don't enable them here.
	 */
	up->ier = UART_IER_RLSI | UART_IER_RDI;
	serial_outp(up, UART_IER, up->ier);

	if (up->port.flags & UPF_FOURPORT) {
		unsigned int icp;
		/*
		 * Enable interrupts on the AST Fourport board
		 */
		icp = (up->port.iobase & 0xfe0) | 0x01f;
		outb_p(0x80, icp);
		(void) inb_p(icp);
	}

	/*
	 * And clear the interrupt registers again for luck.
	 */
	(void) serial_inp(up, UART_LSR);
	(void) serial_inp(up, UART_RX);
	(void) serial_inp(up, UART_IIR);
	(void) serial_inp(up, UART_MSR);

	return 0;
}