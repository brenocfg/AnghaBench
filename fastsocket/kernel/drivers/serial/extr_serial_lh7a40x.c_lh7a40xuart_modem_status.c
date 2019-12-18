#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct uart_port_lh7a40x {unsigned int statusPrev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dsr; } ;
struct uart_port {TYPE_3__* state; TYPE_1__ icount; } ;
struct TYPE_5__ {int /*<<< orphan*/  delta_msr_wait; } ;
struct TYPE_6__ {TYPE_2__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_SET (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int CTS ; 
 unsigned int DCD ; 
 unsigned int DSR ; 
 int /*<<< orphan*/  MSEOI ; 
 int /*<<< orphan*/  UART_R_RAWISR ; 
 int /*<<< orphan*/  UART_R_STATUS ; 
 unsigned int UR (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_handle_cts_change (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  uart_handle_dcd_change (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lh7a40xuart_modem_status (struct uart_port* port)
{
	unsigned int status = UR (port, UART_R_STATUS);
	unsigned int delta
		= status ^ ((struct uart_port_lh7a40x*) port)->statusPrev;

	BIT_SET (port, UART_R_RAWISR, MSEOI); /* Clear modem status intr */

	if (!delta)		/* Only happens if we missed 2 transitions */
		return;

	((struct uart_port_lh7a40x*) port)->statusPrev = status;

	if (delta & DCD)
		uart_handle_dcd_change (port, status & DCD);

	if (delta & DSR)
		++port->icount.dsr;

	if (delta & CTS)
		uart_handle_cts_change (port, status & CTS);

	wake_up_interruptible (&port->state->port.delta_msr_wait);
}