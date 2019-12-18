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
struct uart_port {int dummy; } ;
struct TYPE_4__ {int irq; } ;
struct TYPE_3__ {int /*<<< orphan*/  buf; } ;
struct bfin_serial_port {scalar_t__ cts_pin; scalar_t__ rts_pin; int status_irq; TYPE_2__ port; TYPE_1__ rx_dma_buf; int /*<<< orphan*/  rx_dma_timer; int /*<<< orphan*/  rx_dma_channel; int /*<<< orphan*/  tx_dma_channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_UART2_RX ; 
 int /*<<< orphan*/  CH_UART2_TX ; 
 int /*<<< orphan*/  CH_UART3_RX ; 
 int /*<<< orphan*/  CH_UART3_TX ; 
 scalar_t__ EDSSI ; 
#define  IRQ_UART2_RX 129 
#define  IRQ_UART3_RX 128 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ UART_GET_IER (struct bfin_serial_port*) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int,struct bfin_serial_port*) ; 
 int /*<<< orphan*/  gpio_free (scalar_t__) ; 
 int gpio_to_irq (scalar_t__) ; 

__attribute__((used)) static void bfin_serial_shutdown(struct uart_port *port)
{
	struct bfin_serial_port *uart = (struct bfin_serial_port *)port;

#ifdef CONFIG_SERIAL_BFIN_DMA
	disable_dma(uart->tx_dma_channel);
	free_dma(uart->tx_dma_channel);
	disable_dma(uart->rx_dma_channel);
	free_dma(uart->rx_dma_channel);
	del_timer(&(uart->rx_dma_timer));
	dma_free_coherent(NULL, PAGE_SIZE, uart->rx_dma_buf.buf, 0);
#else
#ifdef CONFIG_BF54x
	switch (uart->port.irq) {
	case IRQ_UART3_RX:
		free_dma(CH_UART3_RX);
		free_dma(CH_UART3_TX);
		break;
	case IRQ_UART2_RX:
		free_dma(CH_UART2_RX);
		free_dma(CH_UART2_TX);
		break;
	default:
		break;
	};
#endif
	free_irq(uart->port.irq, uart);
	free_irq(uart->port.irq+1, uart);
#endif

#ifdef CONFIG_SERIAL_BFIN_CTSRTS
	if (uart->cts_pin >= 0)
		free_irq(gpio_to_irq(uart->cts_pin), uart);
	if (uart->rts_pin >= 0)
		gpio_free(uart->rts_pin);
#endif
#ifdef CONFIG_SERIAL_BFIN_HARD_CTSRTS
	if (uart->cts_pin >= 0)
		gpio_free(uart->cts_pin);
	if (uart->rts_pin >= 0)
		gpio_free(uart->rts_pin);
	if (UART_GET_IER(uart) && EDSSI)
		free_irq(uart->status_irq, uart);
#endif
}