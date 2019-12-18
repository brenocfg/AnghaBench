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
struct TYPE_2__ {int irq; } ;
struct uart_sio_port {TYPE_1__ port; } ;
struct irq_info {int /*<<< orphan*/ * head; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int,struct irq_info*) ; 
 struct irq_info* irq_lists ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serial_do_unlink (struct irq_info*,struct uart_sio_port*) ; 

__attribute__((used)) static void serial_unlink_irq_chain(struct uart_sio_port *up)
{
	struct irq_info *i = irq_lists + up->port.irq;

	BUG_ON(i->head == NULL);

	if (list_empty(i->head)) {
		free_irq(up->port.irq, i);
		free_irq(up->port.irq + 1, i);
	}

	serial_do_unlink(i, up);
}