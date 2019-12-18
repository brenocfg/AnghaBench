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
typedef  scalar_t__ u_int ;
struct uart_port {scalar_t__ mapbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECT_POWER_ON ; 
 int /*<<< orphan*/  RS232_ON ; 
 int /*<<< orphan*/  Ser1UTCR0 ; 
 int /*<<< orphan*/  clear_cs3_bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cs3_bit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void simpad_uart_pm(struct uart_port *port, u_int state, u_int oldstate)
{
	if (port->mapbase == (u_int)&Ser1UTCR0) {
		if (state)
		{
			clear_cs3_bit(RS232_ON);
			clear_cs3_bit(DECT_POWER_ON);
		}else
		{
			set_cs3_bit(RS232_ON);
			set_cs3_bit(DECT_POWER_ON);
		}
	}
}