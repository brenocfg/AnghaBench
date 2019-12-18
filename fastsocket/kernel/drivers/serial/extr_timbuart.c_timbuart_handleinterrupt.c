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
struct TYPE_2__ {scalar_t__ membase; } ;
struct timbuart_port {int /*<<< orphan*/  tasklet; TYPE_1__ port; int /*<<< orphan*/  last_ier; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ TIMBUART_IER ; 
 scalar_t__ TIMBUART_IPR ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 scalar_t__ ioread8 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t timbuart_handleinterrupt(int irq, void *devid)
{
	struct timbuart_port *uart = (struct timbuart_port *)devid;

	if (ioread8(uart->port.membase + TIMBUART_IPR)) {
		uart->last_ier = ioread32(uart->port.membase + TIMBUART_IER);

		/* disable interrupts, the tasklet enables them again */
		iowrite32(0, uart->port.membase + TIMBUART_IER);

		/* fire off bottom half */
		tasklet_schedule(&uart->tasklet);

		return IRQ_HANDLED;
	} else
		return IRQ_NONE;
}