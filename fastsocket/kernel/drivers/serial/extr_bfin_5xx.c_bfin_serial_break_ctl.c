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
typedef  int /*<<< orphan*/  u16 ;
struct uart_port {int dummy; } ;
struct bfin_serial_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SB ; 
 int /*<<< orphan*/  SSYNC () ; 
 int /*<<< orphan*/  UART_GET_LCR (struct bfin_serial_port*) ; 
 int /*<<< orphan*/  UART_PUT_LCR (struct bfin_serial_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bfin_serial_break_ctl(struct uart_port *port, int break_state)
{
	struct bfin_serial_port *uart = (struct bfin_serial_port *)port;
	u16 lcr = UART_GET_LCR(uart);
	if (break_state)
		lcr |= SB;
	else
		lcr &= ~SB;
	UART_PUT_LCR(uart, lcr);
	SSYNC();
}