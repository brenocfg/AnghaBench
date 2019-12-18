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
struct TYPE_6__ {unsigned int rx; } ;
struct uart_port {int /*<<< orphan*/  lock; TYPE_3__ icount; int /*<<< orphan*/  dev; TYPE_2__* state; } ;
struct tty_struct {int dummy; } ;
struct atmel_uart_port {int pdc_rx_idx; struct atmel_dma_buffer* pdc_rx; } ;
struct atmel_dma_buffer {unsigned int dma_size; unsigned int dma_addr; unsigned int ofs; scalar_t__ buf; } ;
struct TYPE_4__ {struct tty_struct* tty; } ;
struct TYPE_5__ {TYPE_1__ port; } ;

/* Variables and functions */
 int ATMEL_US_ENDRX ; 
 int /*<<< orphan*/  ATMEL_US_STTTO ; 
 int ATMEL_US_TIMEOUT ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 unsigned int UART_GET_RPR (struct uart_port*) ; 
 int /*<<< orphan*/  UART_PUT_CR (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_PUT_IER (struct uart_port*,int) ; 
 int /*<<< orphan*/  UART_PUT_RNCR (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  UART_PUT_RNPR (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct atmel_uart_port* to_atmel_uart_port (struct uart_port*) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_insert_flip_string (struct tty_struct*,scalar_t__,unsigned int) ; 

__attribute__((used)) static void atmel_rx_from_dma(struct uart_port *port)
{
	struct atmel_uart_port *atmel_port = to_atmel_uart_port(port);
	struct tty_struct *tty = port->state->port.tty;
	struct atmel_dma_buffer *pdc;
	int rx_idx = atmel_port->pdc_rx_idx;
	unsigned int head;
	unsigned int tail;
	unsigned int count;

	do {
		/* Reset the UART timeout early so that we don't miss one */
		UART_PUT_CR(port, ATMEL_US_STTTO);

		pdc = &atmel_port->pdc_rx[rx_idx];
		head = UART_GET_RPR(port) - pdc->dma_addr;
		tail = pdc->ofs;

		/* If the PDC has switched buffers, RPR won't contain
		 * any address within the current buffer. Since head
		 * is unsigned, we just need a one-way comparison to
		 * find out.
		 *
		 * In this case, we just need to consume the entire
		 * buffer and resubmit it for DMA. This will clear the
		 * ENDRX bit as well, so that we can safely re-enable
		 * all interrupts below.
		 */
		head = min(head, pdc->dma_size);

		if (likely(head != tail)) {
			dma_sync_single_for_cpu(port->dev, pdc->dma_addr,
					pdc->dma_size, DMA_FROM_DEVICE);

			/*
			 * head will only wrap around when we recycle
			 * the DMA buffer, and when that happens, we
			 * explicitly set tail to 0. So head will
			 * always be greater than tail.
			 */
			count = head - tail;

			tty_insert_flip_string(tty, pdc->buf + pdc->ofs, count);

			dma_sync_single_for_device(port->dev, pdc->dma_addr,
					pdc->dma_size, DMA_FROM_DEVICE);

			port->icount.rx += count;
			pdc->ofs = head;
		}

		/*
		 * If the current buffer is full, we need to check if
		 * the next one contains any additional data.
		 */
		if (head >= pdc->dma_size) {
			pdc->ofs = 0;
			UART_PUT_RNPR(port, pdc->dma_addr);
			UART_PUT_RNCR(port, pdc->dma_size);

			rx_idx = !rx_idx;
			atmel_port->pdc_rx_idx = rx_idx;
		}
	} while (head >= pdc->dma_size);

	/*
	 * Drop the lock here since it might end up calling
	 * uart_start(), which takes the lock.
	 */
	spin_unlock(&port->lock);
	tty_flip_buffer_push(tty);
	spin_lock(&port->lock);

	UART_PUT_IER(port, ATMEL_US_ENDRX | ATMEL_US_TIMEOUT);
}