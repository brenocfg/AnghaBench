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
struct uart_ip22zilog_port {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP22ZILOG_FLAG_TX_STOPPED ; 

__attribute__((used)) static void ip22zilog_stop_tx(struct uart_port *port)
{
	struct uart_ip22zilog_port *up = (struct uart_ip22zilog_port *) port;

	up->flags |= IP22ZILOG_FLAG_TX_STOPPED;
}