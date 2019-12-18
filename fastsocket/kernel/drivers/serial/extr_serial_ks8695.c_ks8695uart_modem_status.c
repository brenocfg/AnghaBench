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
struct TYPE_6__ {int /*<<< orphan*/  rng; int /*<<< orphan*/  dsr; } ;
struct uart_port {TYPE_2__* state; TYPE_3__ icount; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  delta_msr_wait; } ;
struct TYPE_5__ {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned int UART_GET_MSR (struct uart_port*) ; 
 unsigned int URMS_URDCTS ; 
 unsigned int URMS_URDDCD ; 
 unsigned int URMS_URDDST ; 
 unsigned int URMS_URTERI ; 
 int /*<<< orphan*/  uart_handle_cts_change (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  uart_handle_dcd_change (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t ks8695uart_modem_status(int irq, void *dev_id)
{
	struct uart_port *port = dev_id;
	unsigned int status;

	/*
	 * clear modem interrupt by reading MSR
	 */
	status = UART_GET_MSR(port);

	if (status & URMS_URDDCD)
		uart_handle_dcd_change(port, status & URMS_URDDCD);

	if (status & URMS_URDDST)
		port->icount.dsr++;

	if (status & URMS_URDCTS)
		uart_handle_cts_change(port, status & URMS_URDCTS);

	if (status & URMS_URTERI)
		port->icount.rng++;

	wake_up_interruptible(&port->state->port.delta_msr_wait);

	return IRQ_HANDLED;
}