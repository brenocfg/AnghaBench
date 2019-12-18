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
struct of_device {int num_irqs; unsigned int* irqs; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 struct of_device* of_find_device_by_node (struct device_node*) ; 

unsigned int irq_of_parse_and_map(struct device_node *node, int index)
{
	struct of_device *op = of_find_device_by_node(node);

	if (!op || index >= op->num_irqs)
		return 0;

	return op->irqs[index];
}