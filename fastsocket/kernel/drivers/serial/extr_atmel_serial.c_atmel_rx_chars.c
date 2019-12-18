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
struct atmel_uart_port {int break_active; int /*<<< orphan*/  tasklet; } ;

/* Variables and functions */
 unsigned int ATMEL_US_FRAME ; 
 unsigned int ATMEL_US_OVRE ; 
 unsigned int ATMEL_US_PARE ; 
 int /*<<< orphan*/  ATMEL_US_RSTSTA ; 
 unsigned int ATMEL_US_RXBRK ; 
 unsigned int ATMEL_US_RXRDY ; 
 unsigned int UART_GET_CHAR (struct uart_port*) ; 
 unsigned int UART_GET_CSR (struct uart_port*) ; 
 int /*<<< orphan*/  UART_PUT_CR (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_PUT_IDR (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  UART_PUT_IER (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  atmel_buffer_rx_char (struct uart_port*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 struct atmel_uart_port* to_atmel_uart_port (struct uart_port*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void atmel_rx_chars(struct uart_port *port)
{
	struct atmel_uart_port *atmel_port = to_atmel_uart_port(port);
	unsigned int status, ch;

	status = UART_GET_CSR(port);
	while (status & ATMEL_US_RXRDY) {
		ch = UART_GET_CHAR(port);

		/*
		 * note that the error handling code is
		 * out of the main execution path
		 */
		if (unlikely(status & (ATMEL_US_PARE | ATMEL_US_FRAME
				       | ATMEL_US_OVRE | ATMEL_US_RXBRK)
			     || atmel_port->break_active)) {

			/* clear error */
			UART_PUT_CR(port, ATMEL_US_RSTSTA);

			if (status & ATMEL_US_RXBRK
			    && !atmel_port->break_active) {
				atmel_port->break_active = 1;
				UART_PUT_IER(port, ATMEL_US_RXBRK);
			} else {
				/*
				 * This is either the end-of-break
				 * condition or we've received at
				 * least one character without RXBRK
				 * being set. In both cases, the next
				 * RXBRK will indicate start-of-break.
				 */
				UART_PUT_IDR(port, ATMEL_US_RXBRK);
				status &= ~ATMEL_US_RXBRK;
				atmel_port->break_active = 0;
			}
		}

		atmel_buffer_rx_char(port, status, ch);
		status = UART_GET_CSR(port);
	}

	tasklet_schedule(&atmel_port->tasklet);
}