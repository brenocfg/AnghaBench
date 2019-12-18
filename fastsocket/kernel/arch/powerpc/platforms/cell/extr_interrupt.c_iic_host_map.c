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
struct irq_host {int dummy; } ;
typedef  int irq_hw_number_t ;

/* Variables and functions */
#define  IIC_IRQ_TYPE_IOEXC 129 
#define  IIC_IRQ_TYPE_IPI 128 
 int IIC_IRQ_TYPE_MASK ; 
 int /*<<< orphan*/  handle_iic_irq ; 
 int /*<<< orphan*/  handle_percpu_irq ; 
 int /*<<< orphan*/  iic_chip ; 
 int /*<<< orphan*/  iic_ioexc_chip ; 
 int /*<<< orphan*/  set_irq_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iic_host_map(struct irq_host *h, unsigned int virq,
			irq_hw_number_t hw)
{
	switch (hw & IIC_IRQ_TYPE_MASK) {
	case IIC_IRQ_TYPE_IPI:
		set_irq_chip_and_handler(virq, &iic_chip, handle_percpu_irq);
		break;
	case IIC_IRQ_TYPE_IOEXC:
		set_irq_chip_and_handler(virq, &iic_ioexc_chip,
					 handle_iic_irq);
		break;
	default:
		set_irq_chip_and_handler(virq, &iic_chip, handle_iic_irq);
	}
	return 0;
}