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

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_PDC_TXTDIS ; 
 int ATMEL_US_ENDTX ; 
 int ATMEL_US_TXBUFE ; 
 int ATMEL_US_TXRDY ; 
 int /*<<< orphan*/  UART_PUT_IDR (struct uart_port*,int) ; 
 int /*<<< orphan*/  UART_PUT_PTCR (struct uart_port*,int /*<<< orphan*/ ) ; 
 scalar_t__ atmel_use_dma_tx (struct uart_port*) ; 

__attribute__((used)) static void atmel_stop_tx(struct uart_port *port)
{
	if (atmel_use_dma_tx(port)) {
		/* disable PDC transmit */
		UART_PUT_PTCR(port, ATMEL_PDC_TXTDIS);
		UART_PUT_IDR(port, ATMEL_US_ENDTX | ATMEL_US_TXBUFE);
	} else
		UART_PUT_IDR(port, ATMEL_US_TXRDY);
}