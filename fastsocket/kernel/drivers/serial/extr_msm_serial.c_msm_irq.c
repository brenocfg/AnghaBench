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
struct uart_port {int /*<<< orphan*/  lock; } ;
struct msm_port {int /*<<< orphan*/  imr; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  UART_IMR ; 
 unsigned int UART_IMR_DELTA_CTS ; 
 unsigned int UART_IMR_RXLEV ; 
 unsigned int UART_IMR_RXSTALE ; 
 unsigned int UART_IMR_TXLEV ; 
 int /*<<< orphan*/  UART_MISR ; 
 struct msm_port* UART_TO_MSM (struct uart_port*) ; 
 int /*<<< orphan*/  handle_delta_cts (struct uart_port*) ; 
 int /*<<< orphan*/  handle_rx (struct uart_port*) ; 
 int /*<<< orphan*/  handle_tx (struct uart_port*) ; 
 unsigned int msm_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_write (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t msm_irq(int irq, void *dev_id)
{
	struct uart_port *port = dev_id;
	struct msm_port *msm_port = UART_TO_MSM(port);
	unsigned int misr;

	spin_lock(&port->lock);
	misr = msm_read(port, UART_MISR);
	msm_write(port, 0, UART_IMR); /* disable interrupt */

	if (misr & (UART_IMR_RXLEV | UART_IMR_RXSTALE))
		handle_rx(port);
	if (misr & UART_IMR_TXLEV)
		handle_tx(port);
	if (misr & UART_IMR_DELTA_CTS)
		handle_delta_cts(port);

	msm_write(port, msm_port->imr, UART_IMR); /* restore interrupt */
	spin_unlock(&port->lock);

	return IRQ_HANDLED;
}