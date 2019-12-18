#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ type; } ;
struct uart_sunsu_port {int /*<<< orphan*/  acr; TYPE_1__ port; } ;
struct uart_port {int dummy; } ;

/* Variables and functions */
 scalar_t__ PORT_16C950 ; 
 int /*<<< orphan*/  UART_ACR ; 
 int /*<<< orphan*/  UART_ACR_TXDIS ; 
 int /*<<< orphan*/  __stop_tx (struct uart_sunsu_port*) ; 
 int /*<<< orphan*/  serial_icr_write (struct uart_sunsu_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sunsu_stop_tx(struct uart_port *port)
{
	struct uart_sunsu_port *up = (struct uart_sunsu_port *) port;

	__stop_tx(up);

	/*
	 * We really want to stop the transmitter from sending.
	 */
	if (up->port.type == PORT_16C950) {
		up->acr |= UART_ACR_TXDIS;
		serial_icr_write(up, UART_ACR, up->acr);
	}
}