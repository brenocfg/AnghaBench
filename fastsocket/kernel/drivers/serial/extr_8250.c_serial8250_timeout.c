#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  timeout; } ;
struct uart_8250_port {TYPE_1__ port; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_IIR ; 
 unsigned int UART_IIR_NO_INT ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ poll_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial8250_handle_port (struct uart_8250_port*) ; 
 unsigned int serial_in (struct uart_8250_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void serial8250_timeout(unsigned long data)
{
	struct uart_8250_port *up = (struct uart_8250_port *)data;
	unsigned int iir;

	iir = serial_in(up, UART_IIR);
	if (!(iir & UART_IIR_NO_INT))
		serial8250_handle_port(up);
	mod_timer(&up->timer, jiffies + poll_timeout(up->port.timeout));
}