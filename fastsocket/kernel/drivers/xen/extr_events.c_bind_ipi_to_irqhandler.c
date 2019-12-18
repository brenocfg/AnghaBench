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
typedef  int /*<<< orphan*/  irq_handler_t ;
typedef  enum ipi_vector { ____Placeholder_ipi_vector } ipi_vector ;

/* Variables and functions */
 unsigned long IRQF_NO_SUSPEND ; 
 int bind_ipi_to_irq (int,unsigned int) ; 
 int request_irq (int,int /*<<< orphan*/ ,unsigned long,char const*,void*) ; 
 int /*<<< orphan*/  unbind_from_irq (int) ; 

int bind_ipi_to_irqhandler(enum ipi_vector ipi,
			   unsigned int cpu,
			   irq_handler_t handler,
			   unsigned long irqflags,
			   const char *devname,
			   void *dev_id)
{
	int irq, retval;

	irq = bind_ipi_to_irq(ipi, cpu);
	if (irq < 0)
		return irq;

	irqflags |= IRQF_NO_SUSPEND;
	retval = request_irq(irq, handler, irqflags, devname, dev_id);
	if (retval != 0) {
		unbind_from_irq(irq);
		return retval;
	}

	return irq;
}