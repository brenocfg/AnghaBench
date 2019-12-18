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
struct property {int dummy; } ;
struct node {int addr_cells; int size_cells; } ;
struct check {int dummy; } ;

/* Variables and functions */
 struct property* get_property (struct node*,char*) ; 
 void* propval_cell (struct property*) ; 

__attribute__((used)) static void fixup_addr_size_cells(struct check *c, struct node *dt,
				  struct node *node)
{
	struct property *prop;

	node->addr_cells = -1;
	node->size_cells = -1;

	prop = get_property(node, "#address-cells");
	if (prop)
		node->addr_cells = propval_cell(prop);

	prop = get_property(node, "#size-cells");
	if (prop)
		node->size_cells = propval_cell(prop);
}