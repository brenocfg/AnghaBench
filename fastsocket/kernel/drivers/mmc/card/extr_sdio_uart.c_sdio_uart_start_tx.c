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
struct sdio_uart_port {int ier; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_IER ; 
 int UART_IER_THRI ; 
 int /*<<< orphan*/  sdio_out (struct sdio_uart_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sdio_uart_start_tx(struct sdio_uart_port *port)
{
	if (!(port->ier & UART_IER_THRI)) {
		port->ier |= UART_IER_THRI;
		sdio_out(port, UART_IER, port->ier);
	}
}