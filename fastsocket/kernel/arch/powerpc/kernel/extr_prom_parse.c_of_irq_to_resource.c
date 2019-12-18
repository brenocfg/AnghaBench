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
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int NO_IRQ ; 
 int irq_of_parse_and_map (struct device_node*,int) ; 

int of_irq_to_resource(struct device_node *dev, int index, struct resource *r)
{
	int irq = irq_of_parse_and_map(dev, index);

	/* Only dereference the resource if both the
	 * resource and the irq are valid. */
	if (r && irq != NO_IRQ) {
		r->start = r->end = irq;
		r->flags = IORESOURCE_IRQ;
	}

	return irq;
}