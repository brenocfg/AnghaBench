#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dsr; } ;
struct TYPE_9__ {TYPE_3__* state; TYPE_1__ icount; scalar_t__ membase; } ;
struct uart_amba_port {unsigned int old_status; TYPE_4__ port; } ;
struct TYPE_7__ {int /*<<< orphan*/  delta_msr_wait; } ;
struct TYPE_8__ {TYPE_2__ port; } ;

/* Variables and functions */
 scalar_t__ UART010_ICR ; 
 scalar_t__ UART01x_FR ; 
 unsigned int UART01x_FR_CTS ; 
 unsigned int UART01x_FR_DCD ; 
 unsigned int UART01x_FR_DSR ; 
 unsigned int UART01x_FR_MODEM_ANY ; 
 unsigned int readb (scalar_t__) ; 
 int /*<<< orphan*/  uart_handle_cts_change (TYPE_4__*,unsigned int) ; 
 int /*<<< orphan*/  uart_handle_dcd_change (TYPE_4__*,unsigned int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void pl010_modem_status(struct uart_amba_port *uap)
{
	unsigned int status, delta;

	writel(0, uap->port.membase + UART010_ICR);

	status = readb(uap->port.membase + UART01x_FR) & UART01x_FR_MODEM_ANY;

	delta = status ^ uap->old_status;
	uap->old_status = status;

	if (!delta)
		return;

	if (delta & UART01x_FR_DCD)
		uart_handle_dcd_change(&uap->port, status & UART01x_FR_DCD);

	if (delta & UART01x_FR_DSR)
		uap->port.icount.dsr++;

	if (delta & UART01x_FR_CTS)
		uart_handle_cts_change(&uap->port, status & UART01x_FR_CTS);

	wake_up_interruptible(&uap->port.state->port.delta_msr_wait);
}