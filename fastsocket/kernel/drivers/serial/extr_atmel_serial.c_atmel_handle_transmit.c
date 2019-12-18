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
struct atmel_uart_port {int /*<<< orphan*/  tasklet; } ;

/* Variables and functions */
 unsigned int ATMEL_US_ENDTX ; 
 unsigned int ATMEL_US_TXBUFE ; 
 unsigned int ATMEL_US_TXRDY ; 
 int /*<<< orphan*/  UART_PUT_IDR (struct uart_port*,unsigned int) ; 
 scalar_t__ atmel_use_dma_tx (struct uart_port*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 struct atmel_uart_port* to_atmel_uart_port (struct uart_port*) ; 

__attribute__((used)) static void
atmel_handle_transmit(struct uart_port *port, unsigned int pending)
{
	struct atmel_uart_port *atmel_port = to_atmel_uart_port(port);

	if (atmel_use_dma_tx(port)) {
		/* PDC transmit */
		if (pending & (ATMEL_US_ENDTX | ATMEL_US_TXBUFE)) {
			UART_PUT_IDR(port, ATMEL_US_ENDTX | ATMEL_US_TXBUFE);
			tasklet_schedule(&atmel_port->tasklet);
		}
	} else {
		/* Interrupt transmit */
		if (pending & ATMEL_US_TXRDY) {
			UART_PUT_IDR(port, ATMEL_US_TXRDY);
			tasklet_schedule(&atmel_port->tasklet);
		}
	}
}