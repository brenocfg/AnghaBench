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
struct uart_port {int /*<<< orphan*/  line; } ;
struct mpsc_port_info {int /*<<< orphan*/  tx_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mpsc_copy_tx_data (struct mpsc_port_info*) ; 
 int /*<<< orphan*/  mpsc_sdma_start_tx (struct mpsc_port_info*) ; 
 int /*<<< orphan*/  mpsc_unfreeze (struct mpsc_port_info*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mpsc_start_tx(struct uart_port *port)
{
	struct mpsc_port_info *pi = (struct mpsc_port_info *)port;
	unsigned long iflags;

	spin_lock_irqsave(&pi->tx_lock, iflags);

	mpsc_unfreeze(pi);
	mpsc_copy_tx_data(pi);
	mpsc_sdma_start_tx(pi);

	spin_unlock_irqrestore(&pi->tx_lock, iflags);

	pr_debug("mpsc_start_tx[%d]\n", port->line);
}