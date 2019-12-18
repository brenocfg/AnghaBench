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
struct TYPE_4__ {int tx; } ;
struct uart_port {int /*<<< orphan*/  dev; TYPE_2__ icount; TYPE_1__* state; } ;
struct circ_buf {int tail; int /*<<< orphan*/  head; } ;
struct atmel_dma_buffer {int ofs; scalar_t__ dma_addr; int /*<<< orphan*/  dma_size; } ;
struct atmel_uart_port {struct atmel_dma_buffer pdc_tx; } ;
struct TYPE_3__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_PDC_TXTDIS ; 
 int /*<<< orphan*/  ATMEL_PDC_TXTEN ; 
 int ATMEL_US_ENDTX ; 
 int ATMEL_US_TXBUFE ; 
 int CIRC_CNT_TO_END (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ UART_GET_TCR (struct uart_port*) ; 
 int /*<<< orphan*/  UART_PUT_IER (struct uart_port*,int) ; 
 int /*<<< orphan*/  UART_PUT_PTCR (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_PUT_TCR (struct uart_port*,int) ; 
 int /*<<< orphan*/  UART_PUT_TPR (struct uart_port*,scalar_t__) ; 
 int UART_XMIT_SIZE ; 
 scalar_t__ WAKEUP_CHARS ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct atmel_uart_port* to_atmel_uart_port (struct uart_port*) ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 int /*<<< orphan*/  uart_circ_empty (struct circ_buf*) ; 
 int /*<<< orphan*/  uart_tx_stopped (struct uart_port*) ; 
 int /*<<< orphan*/  uart_write_wakeup (struct uart_port*) ; 

__attribute__((used)) static void atmel_tx_dma(struct uart_port *port)
{
	struct atmel_uart_port *atmel_port = to_atmel_uart_port(port);
	struct circ_buf *xmit = &port->state->xmit;
	struct atmel_dma_buffer *pdc = &atmel_port->pdc_tx;
	int count;

	/* nothing left to transmit? */
	if (UART_GET_TCR(port))
		return;

	xmit->tail += pdc->ofs;
	xmit->tail &= UART_XMIT_SIZE - 1;

	port->icount.tx += pdc->ofs;
	pdc->ofs = 0;

	/* more to transmit - setup next transfer */

	/* disable PDC transmit */
	UART_PUT_PTCR(port, ATMEL_PDC_TXTDIS);

	if (!uart_circ_empty(xmit) && !uart_tx_stopped(port)) {
		dma_sync_single_for_device(port->dev,
					   pdc->dma_addr,
					   pdc->dma_size,
					   DMA_TO_DEVICE);

		count = CIRC_CNT_TO_END(xmit->head, xmit->tail, UART_XMIT_SIZE);
		pdc->ofs = count;

		UART_PUT_TPR(port, pdc->dma_addr + xmit->tail);
		UART_PUT_TCR(port, count);
		/* re-enable PDC transmit and interrupts */
		UART_PUT_PTCR(port, ATMEL_PDC_TXTEN);
		UART_PUT_IER(port, ATMEL_US_ENDTX | ATMEL_US_TXBUFE);
	}

	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(port);
}