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
struct of_irq {int /*<<< orphan*/  size; int /*<<< orphan*/  specifier; int /*<<< orphan*/  controller; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 unsigned int NO_IRQ ; 
 unsigned int irq_create_of_mapping (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ of_irq_map_one (struct device_node*,int,struct of_irq*) ; 

unsigned int irq_of_parse_and_map(struct device_node *dev, int index)
{
	struct of_irq oirq;

	if (of_irq_map_one(dev, index, &oirq))
		return NO_IRQ;

	return irq_create_of_mapping(oirq.controller, oirq.specifier,
				     oirq.size);
}