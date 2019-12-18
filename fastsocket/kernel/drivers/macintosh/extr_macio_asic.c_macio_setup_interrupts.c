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
struct resource {unsigned int start; int /*<<< orphan*/  name; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; struct device_node* node; } ;
struct macio_dev {int n_interrupts; TYPE_1__ ofdev; struct resource* interrupt; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int MACIO_DEV_COUNT_IRQS ; 
 unsigned int NO_IRQ ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 unsigned int irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 scalar_t__ macio_resource_quirks (struct device_node*,struct resource*,int) ; 
 int /*<<< orphan*/  memset (struct resource*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void macio_setup_interrupts(struct macio_dev *dev)
{
	struct device_node *np = dev->ofdev.node;
	unsigned int irq;
	int i = 0, j = 0;

	for (;;) {
		struct resource *res;

		if (j >= MACIO_DEV_COUNT_IRQS)
			break;
		res = &dev->interrupt[j];
		irq = irq_of_parse_and_map(np, i++);
		if (irq == NO_IRQ)
			break;
		res->start = irq;
		res->flags = IORESOURCE_IRQ;
		res->name = dev_name(&dev->ofdev.dev);
		if (macio_resource_quirks(np, res, i - 1)) {
			memset(res, 0, sizeof(struct resource));
			continue;
		} else
			j++;
	}
	dev->n_interrupts = j;
}