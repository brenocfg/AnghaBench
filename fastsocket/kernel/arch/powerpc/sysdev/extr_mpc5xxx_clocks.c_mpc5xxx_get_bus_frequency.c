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
struct device_node {int dummy; } ;

/* Variables and functions */
 struct device_node* of_get_parent (struct device_node*) ; 
 unsigned int* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

unsigned int
mpc5xxx_get_bus_frequency(struct device_node *node)
{
	struct device_node *np;
	const unsigned int *p_bus_freq = NULL;

	of_node_get(node);
	while (node) {
		p_bus_freq = of_get_property(node, "bus-frequency", NULL);
		if (p_bus_freq)
			break;

		np = of_get_parent(node);
		of_node_put(node);
		node = np;
	}
	if (node)
		of_node_put(node);

	return p_bus_freq ? *p_bus_freq : 0;
}