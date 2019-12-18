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
typedef  int /*<<< orphan*/  tx_enabled ;
struct uart_port {int dummy; } ;
struct s3c24xx_uart_port {scalar_t__ rx_claimed; int /*<<< orphan*/  rx_irq; scalar_t__ tx_claimed; int /*<<< orphan*/  tx_irq; } ;
typedef  int /*<<< orphan*/  rx_enabled ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct s3c24xx_uart_port*) ; 
 struct s3c24xx_uart_port* to_ourport (struct uart_port*) ; 

__attribute__((used)) static void s3c24xx_serial_shutdown(struct uart_port *port)
{
	struct s3c24xx_uart_port *ourport = to_ourport(port);

	if (ourport->tx_claimed) {
		free_irq(ourport->tx_irq, ourport);
		tx_enabled(port) = 0;
		ourport->tx_claimed = 0;
	}

	if (ourport->rx_claimed) {
		free_irq(ourport->rx_irq, ourport);
		ourport->rx_claimed = 0;
		rx_enabled(port) = 0;
	}
}