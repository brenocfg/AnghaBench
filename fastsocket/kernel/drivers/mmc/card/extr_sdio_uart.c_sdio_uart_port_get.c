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
struct sdio_uart_port {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 unsigned int UART_NR ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 struct sdio_uart_port** sdio_uart_table ; 
 int /*<<< orphan*/  sdio_uart_table_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct sdio_uart_port *sdio_uart_port_get(unsigned index)
{
	struct sdio_uart_port *port;

	if (index >= UART_NR)
		return NULL;

	spin_lock(&sdio_uart_table_lock);
	port = sdio_uart_table[index];
	if (port)
		kref_get(&port->kref);
	spin_unlock(&sdio_uart_table_lock);

	return port;
}