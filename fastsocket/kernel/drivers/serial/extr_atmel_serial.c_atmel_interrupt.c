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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_ISR_PASS_LIMIT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned int UART_GET_CSR (struct uart_port*) ; 
 unsigned int UART_GET_IMR (struct uart_port*) ; 
 int /*<<< orphan*/  atmel_handle_receive (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  atmel_handle_status (struct uart_port*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  atmel_handle_transmit (struct uart_port*,unsigned int) ; 

__attribute__((used)) static irqreturn_t atmel_interrupt(int irq, void *dev_id)
{
	struct uart_port *port = dev_id;
	unsigned int status, pending, pass_counter = 0;

	do {
		status = UART_GET_CSR(port);
		pending = status & UART_GET_IMR(port);
		if (!pending)
			break;

		atmel_handle_receive(port, pending);
		atmel_handle_status(port, pending, status);
		atmel_handle_transmit(port, pending);
	} while (pass_counter++ < ATMEL_ISR_PASS_LIMIT);

	return pass_counter ? IRQ_HANDLED : IRQ_NONE;
}