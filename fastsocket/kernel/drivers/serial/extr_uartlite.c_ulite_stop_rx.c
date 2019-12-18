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
struct uart_port {int ignore_status_mask; } ;

/* Variables and functions */
 int ULITE_STATUS_FRAME ; 
 int ULITE_STATUS_OVERRUN ; 
 int ULITE_STATUS_PARITY ; 
 int ULITE_STATUS_RXVALID ; 

__attribute__((used)) static void ulite_stop_rx(struct uart_port *port)
{
	/* don't forward any more data (like !CREAD) */
	port->ignore_status_mask = ULITE_STATUS_RXVALID | ULITE_STATUS_PARITY
		| ULITE_STATUS_FRAME | ULITE_STATUS_OVERRUN;
}