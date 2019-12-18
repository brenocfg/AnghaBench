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
struct uart_sunzilog_port {int /*<<< orphan*/  flags; } ;
struct uart_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUNZILOG_FLAG_TX_STOPPED ; 

__attribute__((used)) static void sunzilog_stop_tx(struct uart_port *port)
{
	struct uart_sunzilog_port *up = (struct uart_sunzilog_port *) port;

	up->flags |= SUNZILOG_FLAG_TX_STOPPED;
}