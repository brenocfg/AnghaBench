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
struct sdio_uart_port {size_t index; int /*<<< orphan*/  open_lock; int /*<<< orphan*/  tty; scalar_t__ opened; int /*<<< orphan*/  func_lock; struct sdio_func* func; } ;
struct sdio_func {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_disable_func (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_irq (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_uart_port_put (struct sdio_uart_port*) ; 
 struct sdio_uart_port** sdio_uart_table ; 
 int /*<<< orphan*/  sdio_uart_table_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_hangup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdio_uart_port_remove(struct sdio_uart_port *port)
{
	struct sdio_func *func;

	BUG_ON(sdio_uart_table[port->index] != port);

	spin_lock(&sdio_uart_table_lock);
	sdio_uart_table[port->index] = NULL;
	spin_unlock(&sdio_uart_table_lock);

	/*
	 * We're killing a port that potentially still is in use by
	 * the tty layer. Be careful to prevent any further access
	 * to the SDIO function and arrange for the tty layer to
	 * give up on that port ASAP.
	 * Beware: the lock ordering is critical.
	 */
	mutex_lock(&port->open_lock);
	mutex_lock(&port->func_lock);
	func = port->func;
	sdio_claim_host(func);
	port->func = NULL;
	mutex_unlock(&port->func_lock);
	if (port->opened)
		tty_hangup(port->tty);
	mutex_unlock(&port->open_lock);
	sdio_release_irq(func);
	sdio_disable_func(func);
	sdio_release_host(func);

	sdio_uart_port_put(port);
}