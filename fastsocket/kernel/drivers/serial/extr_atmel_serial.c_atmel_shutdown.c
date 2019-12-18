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
struct uart_port {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct atmel_dma_buffer {int /*<<< orphan*/  dma_size; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  buf; } ;
struct atmel_uart_port {struct atmel_dma_buffer pdc_tx; struct atmel_dma_buffer* pdc_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_US_RSTSTA ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  UART_PUT_CR (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_PUT_IDR (struct uart_port*,int) ; 
 int /*<<< orphan*/  atmel_close_hook (struct uart_port*) ; 
 int /*<<< orphan*/  atmel_stop_rx (struct uart_port*) ; 
 int /*<<< orphan*/  atmel_stop_tx (struct uart_port*) ; 
 scalar_t__ atmel_use_dma_rx (struct uart_port*) ; 
 scalar_t__ atmel_use_dma_tx (struct uart_port*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uart_port*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct atmel_uart_port* to_atmel_uart_port (struct uart_port*) ; 

__attribute__((used)) static void atmel_shutdown(struct uart_port *port)
{
	struct atmel_uart_port *atmel_port = to_atmel_uart_port(port);
	/*
	 * Ensure everything is stopped.
	 */
	atmel_stop_rx(port);
	atmel_stop_tx(port);

	/*
	 * Shut-down the DMA.
	 */
	if (atmel_use_dma_rx(port)) {
		int i;

		for (i = 0; i < 2; i++) {
			struct atmel_dma_buffer *pdc = &atmel_port->pdc_rx[i];

			dma_unmap_single(port->dev,
					 pdc->dma_addr,
					 pdc->dma_size,
					 DMA_FROM_DEVICE);
			kfree(pdc->buf);
		}
	}
	if (atmel_use_dma_tx(port)) {
		struct atmel_dma_buffer *pdc = &atmel_port->pdc_tx;

		dma_unmap_single(port->dev,
				 pdc->dma_addr,
				 pdc->dma_size,
				 DMA_TO_DEVICE);
	}

	/*
	 * Disable all interrupts, port and break condition.
	 */
	UART_PUT_CR(port, ATMEL_US_RSTSTA);
	UART_PUT_IDR(port, -1);

	/*
	 * Free the interrupt
	 */
	free_irq(port->irq, port);

	/*
	 * If there is a specific "close" function (to unregister
	 * control line interrupts)
	 */
	if (atmel_close_hook)
		atmel_close_hook(port);
}