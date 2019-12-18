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
struct resource {int start; int end; int /*<<< orphan*/  flags; } ;
struct of_irq {int* specifier; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int NO_IRQ ; 
 int of_irq_map_one (struct device_node*,int,struct of_irq*) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

int of_irq_to_resource(struct device_node *dev, int index, struct resource *r)
{
	struct of_irq out_irq;
	int irq;
	int res;

	res = of_irq_map_one(dev, index, &out_irq);

	/* Get irq for the device */
	if (res) {
		pr_debug("IRQ not found... code = %d", res);
		return NO_IRQ;
	}
	/* Assuming single interrupt controller... */
	irq = out_irq.specifier[0];

	pr_debug("IRQ found = %d", irq);

	/* Only dereference the resource if both the
	 * resource and the irq are valid. */
	if (r && irq != NO_IRQ) {
		r->start = r->end = irq;
		r->flags = IORESOURCE_IRQ;
	}

	return irq;
}