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
 int /*<<< orphan*/  CR ; 
 int CR_DIS_RX ; 
 int CR_DIS_TX ; 
 int IMR_RXRDY ; 
 int IMR_TXRDY ; 
 int /*<<< orphan*/  WRITE_SC_PORT (struct uart_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sc26xx_disable_irq (struct uart_port*,int) ; 

__attribute__((used)) static void sc26xx_shutdown(struct uart_port *port)
{
	/* disable interrupst */
	sc26xx_disable_irq(port, IMR_TXRDY | IMR_RXRDY);

	/* stop tx/rx */
	WRITE_SC_PORT(port, CR, CR_DIS_TX | CR_DIS_RX);
}