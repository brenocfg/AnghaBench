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
struct TYPE_4__ {int /*<<< orphan*/  dsr; int /*<<< orphan*/  rng; } ;
struct uart_port {int /*<<< orphan*/  lock; TYPE_3__* state; TYPE_1__ icount; } ;
struct atmel_uart_port {unsigned int irq_status; unsigned int irq_status_prev; } ;
struct TYPE_5__ {int /*<<< orphan*/  delta_msr_wait; } ;
struct TYPE_6__ {TYPE_2__ port; } ;

/* Variables and functions */
 unsigned int ATMEL_US_CTS ; 
 unsigned int ATMEL_US_DCD ; 
 unsigned int ATMEL_US_DSR ; 
 unsigned int ATMEL_US_RI ; 
 int /*<<< orphan*/  atmel_rx_from_dma (struct uart_port*) ; 
 int /*<<< orphan*/  atmel_rx_from_ring (struct uart_port*) ; 
 int /*<<< orphan*/  atmel_tx_chars (struct uart_port*) ; 
 int /*<<< orphan*/  atmel_tx_dma (struct uart_port*) ; 
 scalar_t__ atmel_use_dma_rx (struct uart_port*) ; 
 scalar_t__ atmel_use_dma_tx (struct uart_port*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct atmel_uart_port* to_atmel_uart_port (struct uart_port*) ; 
 int /*<<< orphan*/  uart_handle_cts_change (struct uart_port*,int) ; 
 int /*<<< orphan*/  uart_handle_dcd_change (struct uart_port*,int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void atmel_tasklet_func(unsigned long data)
{
	struct uart_port *port = (struct uart_port *)data;
	struct atmel_uart_port *atmel_port = to_atmel_uart_port(port);
	unsigned int status;
	unsigned int status_change;

	/* The interrupt handler does not take the lock */
	spin_lock(&port->lock);

	if (atmel_use_dma_tx(port))
		atmel_tx_dma(port);
	else
		atmel_tx_chars(port);

	status = atmel_port->irq_status;
	status_change = status ^ atmel_port->irq_status_prev;

	if (status_change & (ATMEL_US_RI | ATMEL_US_DSR
				| ATMEL_US_DCD | ATMEL_US_CTS)) {
		/* TODO: All reads to CSR will clear these interrupts! */
		if (status_change & ATMEL_US_RI)
			port->icount.rng++;
		if (status_change & ATMEL_US_DSR)
			port->icount.dsr++;
		if (status_change & ATMEL_US_DCD)
			uart_handle_dcd_change(port, !(status & ATMEL_US_DCD));
		if (status_change & ATMEL_US_CTS)
			uart_handle_cts_change(port, !(status & ATMEL_US_CTS));

		wake_up_interruptible(&port->state->port.delta_msr_wait);

		atmel_port->irq_status_prev = status;
	}

	if (atmel_use_dma_rx(port))
		atmel_rx_from_dma(port);
	else
		atmel_rx_from_ring(port);

	spin_unlock(&port->lock);
}