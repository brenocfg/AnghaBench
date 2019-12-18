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
struct uart_port {int dummy; } ;
struct serial_struct {scalar_t__ irq; int baud_base; } ;
struct sci_port {scalar_t__* irqs; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t SCIx_TXI_IRQ ; 
 scalar_t__ nr_irqs ; 
 struct sci_port* to_sci_port (struct uart_port*) ; 

__attribute__((used)) static int sci_verify_port(struct uart_port *port, struct serial_struct *ser)
{
	struct sci_port *s = to_sci_port(port);

	if (ser->irq != s->irqs[SCIx_TXI_IRQ] || ser->irq > nr_irqs)
		return -EINVAL;
	if (ser->baud_base < 2400)
		/* No paper tape reader for Mitch.. */
		return -EINVAL;

	return 0;
}