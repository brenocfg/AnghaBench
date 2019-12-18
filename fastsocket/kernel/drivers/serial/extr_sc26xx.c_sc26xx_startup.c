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
 int CR_ENA_RX ; 
 int CR_ENA_TX ; 
 int CR_RES_RX ; 
 int CR_RES_TX ; 
 int IMR_RXRDY ; 
 int IMR_TXRDY ; 
 int /*<<< orphan*/  OPCR ; 
 int /*<<< orphan*/  WRITE_SC (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_SC_PORT (struct uart_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sc26xx_disable_irq (struct uart_port*,int) ; 
 int /*<<< orphan*/  sc26xx_enable_irq (struct uart_port*,int) ; 

__attribute__((used)) static int sc26xx_startup(struct uart_port *port)
{
	sc26xx_disable_irq(port, IMR_TXRDY | IMR_RXRDY);
	WRITE_SC(port, OPCR, 0);

	/* reset tx and rx */
	WRITE_SC_PORT(port, CR, CR_RES_RX);
	WRITE_SC_PORT(port, CR, CR_RES_TX);

	/* start rx/tx */
	WRITE_SC_PORT(port, CR, CR_ENA_TX | CR_ENA_RX);

	/* enable irqs */
	sc26xx_enable_irq(port, IMR_RXRDY);
	return 0;
}