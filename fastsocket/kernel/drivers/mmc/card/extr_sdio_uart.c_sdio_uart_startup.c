#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned char* buf; } ;
struct sdio_uart_port {int ier; TYPE_3__ xmit; int /*<<< orphan*/  func; TYPE_1__* tty; int /*<<< orphan*/  mctrl; } ;
struct TYPE_5__ {int c_cflag; } ;
struct TYPE_4__ {int hw_stopped; int /*<<< orphan*/  flags; TYPE_2__* termios; } ;

/* Variables and functions */
 int CBAUD ; 
 int CRTSCTS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int TIOCM_CTS ; 
 int TIOCM_DTR ; 
 int /*<<< orphan*/  TIOCM_OUT2 ; 
 int TIOCM_RTS ; 
 int /*<<< orphan*/  TTY_IO_ERROR ; 
 int /*<<< orphan*/  UART_FCR ; 
 int UART_FCR_CLEAR_RCVR ; 
 int UART_FCR_CLEAR_XMIT ; 
 int UART_FCR_ENABLE_FIFO ; 
 int UART_IER_RDI ; 
 int UART_IER_RLSI ; 
 int UART_IER_RTOIE ; 
 int UART_IER_UUE ; 
 int /*<<< orphan*/  UART_IIR ; 
 int /*<<< orphan*/  UART_LCR ; 
 int UART_LCR_WLEN8 ; 
 int /*<<< orphan*/  UART_LSR ; 
 int /*<<< orphan*/  UART_MSR ; 
 int /*<<< orphan*/  UART_RX ; 
 unsigned long __get_free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  circ_clear (TYPE_3__*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int sdio_claim_irq (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  sdio_disable_func (int /*<<< orphan*/ ) ; 
 int sdio_enable_func (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_in (struct sdio_uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_out (struct sdio_uart_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdio_uart_change_speed (struct sdio_uart_port*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int sdio_uart_claim_func (struct sdio_uart_port*) ; 
 int sdio_uart_get_mctrl (struct sdio_uart_port*) ; 
 int /*<<< orphan*/  sdio_uart_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_uart_release_func (struct sdio_uart_port*) ; 
 int /*<<< orphan*/  sdio_uart_set_mctrl (struct sdio_uart_port*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sdio_uart_startup(struct sdio_uart_port *port)
{
	unsigned long page;
	int ret;

	/*
	 * Set the TTY IO error marker - we will only clear this
	 * once we have successfully opened the port.
	 */
	set_bit(TTY_IO_ERROR, &port->tty->flags);

	/* Initialise and allocate the transmit buffer. */
	page = __get_free_page(GFP_KERNEL);
	if (!page)
		return -ENOMEM;
	port->xmit.buf = (unsigned char *)page;
	circ_clear(&port->xmit);

	ret = sdio_uart_claim_func(port);
	if (ret)
		goto err1;
	ret = sdio_enable_func(port->func);
	if (ret)
		goto err2;
	ret = sdio_claim_irq(port->func, sdio_uart_irq);
	if (ret)
		goto err3;

	/*
	 * Clear the FIFO buffers and disable them.
	 * (they will be reenabled in sdio_change_speed())
	 */
	sdio_out(port, UART_FCR, UART_FCR_ENABLE_FIFO);
	sdio_out(port, UART_FCR, UART_FCR_ENABLE_FIFO |
			UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT);
	sdio_out(port, UART_FCR, 0);

	/*
	 * Clear the interrupt registers.
	 */
	(void) sdio_in(port, UART_LSR);
	(void) sdio_in(port, UART_RX);
	(void) sdio_in(port, UART_IIR);
	(void) sdio_in(port, UART_MSR);

	/*
	 * Now, initialize the UART
	 */
	sdio_out(port, UART_LCR, UART_LCR_WLEN8);

	port->ier = UART_IER_RLSI | UART_IER_RDI | UART_IER_RTOIE | UART_IER_UUE;
	port->mctrl = TIOCM_OUT2;

	sdio_uart_change_speed(port, port->tty->termios, NULL);

	if (port->tty->termios->c_cflag & CBAUD)
		sdio_uart_set_mctrl(port, TIOCM_RTS | TIOCM_DTR);

	if (port->tty->termios->c_cflag & CRTSCTS)
		if (!(sdio_uart_get_mctrl(port) & TIOCM_CTS))
			port->tty->hw_stopped = 1;

	clear_bit(TTY_IO_ERROR, &port->tty->flags);

	/* Kick the IRQ handler once while we're still holding the host lock */
	sdio_uart_irq(port->func);

	sdio_uart_release_func(port);
	return 0;

err3:
	sdio_disable_func(port->func);
err2:
	sdio_uart_release_func(port);
err1:
	free_page((unsigned long)port->xmit.buf);
	return ret;
}