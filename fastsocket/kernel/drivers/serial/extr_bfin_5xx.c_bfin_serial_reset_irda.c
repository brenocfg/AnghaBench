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
struct uart_port {int line; } ;

/* Variables and functions */
 unsigned short IREN ; 
 unsigned short RPOLC ; 
 int /*<<< orphan*/  SSYNC () ; 
 unsigned short UART_GET_GCTL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UART_PUT_GCTL (int /*<<< orphan*/ *,unsigned short) ; 
 int /*<<< orphan*/ * bfin_serial_ports ; 

__attribute__((used)) static void bfin_serial_reset_irda(struct uart_port *port)
{
	int line = port->line;
	unsigned short val;

	val = UART_GET_GCTL(&bfin_serial_ports[line]);
	val &= ~(IREN | RPOLC);
	UART_PUT_GCTL(&bfin_serial_ports[line], val);
	SSYNC();
	val |= (IREN | RPOLC);
	UART_PUT_GCTL(&bfin_serial_ports[line], val);
	SSYNC();
}