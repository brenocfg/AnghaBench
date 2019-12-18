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
struct device_node {struct device_node* parent; } ;

/* Variables and functions */
 int OF_ROOT_NODE_ADDR_CELLS_DEFAULT ; 
 int* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 

int of_n_addr_cells(struct device_node *np)
{
	const int *ip;

	do {
		if (np->parent)
			np = np->parent;
		ip = of_get_property(np, "#address-cells", NULL);
		if (ip)
			return *ip;
	} while (np->parent);
	/* No #address-cells property for the root node */
	return OF_ROOT_NODE_ADDR_CELLS_DEFAULT;
}