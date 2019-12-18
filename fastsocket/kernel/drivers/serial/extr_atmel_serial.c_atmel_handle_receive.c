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
struct uart_port {int dummy; } ;
struct atmel_uart_port {scalar_t__ break_active; int /*<<< orphan*/  tasklet; } ;

/* Variables and functions */
 unsigned int ATMEL_US_ENDRX ; 
 unsigned int ATMEL_US_FRAME ; 
 unsigned int ATMEL_US_OVRE ; 
 unsigned int ATMEL_US_PARE ; 
 int /*<<< orphan*/  ATMEL_US_RSTSTA ; 
 unsigned int ATMEL_US_RXBRK ; 
 unsigned int ATMEL_US_RXRDY ; 
 unsigned int ATMEL_US_TIMEOUT ; 
 int /*<<< orphan*/  UART_PUT_CR (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_PUT_IDR (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  atmel_pdc_rxerr (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  atmel_rx_chars (struct uart_port*) ; 
 scalar_t__ atmel_use_dma_rx (struct uart_port*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 struct atmel_uart_port* to_atmel_uart_port (struct uart_port*) ; 

__attribute__((used)) static void
atmel_handle_receive(struct uart_port *port, unsigned int pending)
{
	struct atmel_uart_port *atmel_port = to_atmel_uart_port(port);

	if (atmel_use_dma_rx(port)) {
		/*
		 * PDC receive. Just schedule the tasklet and let it
		 * figure out the details.
		 *
		 * TODO: We're not handling error flags correctly at
		 * the moment.
		 */
		if (pending & (ATMEL_US_ENDRX | ATMEL_US_TIMEOUT)) {
			UART_PUT_IDR(port, (ATMEL_US_ENDRX
						| ATMEL_US_TIMEOUT));
			tasklet_schedule(&atmel_port->tasklet);
		}

		if (pending & (ATMEL_US_RXBRK | ATMEL_US_OVRE |
				ATMEL_US_FRAME | ATMEL_US_PARE))
			atmel_pdc_rxerr(port, pending);
	}

	/* Interrupt receive */
	if (pending & ATMEL_US_RXRDY)
		atmel_rx_chars(port);
	else if (pending & ATMEL_US_RXBRK) {
		/*
		 * End of break detected. If it came along with a
		 * character, atmel_rx_chars will handle it.
		 */
		UART_PUT_CR(port, ATMEL_US_RSTSTA);
		UART_PUT_IDR(port, ATMEL_US_RXBRK);
		atmel_port->break_active = 0;
	}
}