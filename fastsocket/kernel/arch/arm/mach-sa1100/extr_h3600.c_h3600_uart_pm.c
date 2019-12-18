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
typedef  int /*<<< orphan*/  u_int ;
struct uart_port {scalar_t__ mapbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPAQ_EGPIO_IR_ON ; 
 int /*<<< orphan*/  IPAQ_EGPIO_RS232_ON ; 
 scalar_t__ _Ser2UTCR0 ; 
 scalar_t__ _Ser3UTCR0 ; 
 int /*<<< orphan*/  assign_h3600_egpio (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void h3600_uart_pm(struct uart_port *port, u_int state, u_int oldstate)
{
	if (port->mapbase == _Ser2UTCR0) { /* TODO: REMOVE THIS */
		assign_h3600_egpio(IPAQ_EGPIO_IR_ON, !state);
	} else if (port->mapbase == _Ser3UTCR0) {
		assign_h3600_egpio(IPAQ_EGPIO_RS232_ON, !state);
	}
}