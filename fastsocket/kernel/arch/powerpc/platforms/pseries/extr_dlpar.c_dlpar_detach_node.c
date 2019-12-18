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
struct property {struct property* next; int /*<<< orphan*/  name; } ;
struct device_node {TYPE_1__* pde; struct property* properties; struct device_node* parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSERIES_RECONFIG_REMOVE ; 
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct device_node*) ; 
 int /*<<< orphan*/  of_detach_node (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  pSeries_reconfig_chain ; 
 int /*<<< orphan*/  remove_proc_entry (int /*<<< orphan*/ ,TYPE_1__*) ; 

int dlpar_detach_node(struct device_node *dn)
{
	struct device_node *parent = dn->parent;
	struct property *prop = dn->properties;

#ifdef CONFIG_PROC_DEVICETREE
	while (prop) {
		remove_proc_entry(prop->name, dn->pde);
		prop = prop->next;
	}

	if (dn->pde)
		remove_proc_entry(dn->pde->name, parent->pde);
#endif

	blocking_notifier_call_chain(&pSeries_reconfig_chain,
			    PSERIES_RECONFIG_REMOVE, dn);
	of_detach_node(dn);
	of_node_put(dn); /* Must decrement the refcount */

	return 0;
}