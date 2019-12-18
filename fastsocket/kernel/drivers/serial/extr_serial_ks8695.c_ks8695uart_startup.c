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
 int /*<<< orphan*/  IRQF_DISABLED ; 
 int IRQF_NOAUTOEN ; 
 int IRQF_VALID ; 
 int /*<<< orphan*/  KS8695_IRQ_UART_LINE_STATUS ; 
 int /*<<< orphan*/  KS8695_IRQ_UART_MODEM_STATUS ; 
 int /*<<< orphan*/  KS8695_IRQ_UART_RX ; 
 int /*<<< orphan*/  KS8695_IRQ_UART_TX ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uart_port*) ; 
 int /*<<< orphan*/  ks8695uart_modem_status ; 
 int /*<<< orphan*/  ks8695uart_rx_chars ; 
 int /*<<< orphan*/  ks8695uart_tx_chars ; 
 int /*<<< orphan*/  ms_enable (struct uart_port*,int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct uart_port*) ; 
 int /*<<< orphan*/  rx_enable (struct uart_port*,int) ; 
 int /*<<< orphan*/  set_irq_flags (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tx_enable (struct uart_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ks8695uart_startup(struct uart_port *port)
{
	int retval;

	set_irq_flags(KS8695_IRQ_UART_TX, IRQF_VALID | IRQF_NOAUTOEN);
	tx_enable(port, 0);
	rx_enable(port, 1);
	ms_enable(port, 1);

	/*
	 * Allocate the IRQ
	 */
	retval = request_irq(KS8695_IRQ_UART_TX, ks8695uart_tx_chars, IRQF_DISABLED, "UART TX", port);
	if (retval)
		goto err_tx;

	retval = request_irq(KS8695_IRQ_UART_RX, ks8695uart_rx_chars, IRQF_DISABLED, "UART RX", port);
	if (retval)
		goto err_rx;

	retval = request_irq(KS8695_IRQ_UART_LINE_STATUS, ks8695uart_rx_chars, IRQF_DISABLED, "UART LineStatus", port);
	if (retval)
		goto err_ls;

	retval = request_irq(KS8695_IRQ_UART_MODEM_STATUS, ks8695uart_modem_status, IRQF_DISABLED, "UART ModemStatus", port);
	if (retval)
		goto err_ms;

	return 0;

err_ms:
	free_irq(KS8695_IRQ_UART_LINE_STATUS, port);
err_ls:
	free_irq(KS8695_IRQ_UART_RX, port);
err_rx:
	free_irq(KS8695_IRQ_UART_TX, port);
err_tx:
	return retval;
}