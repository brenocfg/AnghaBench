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
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  PSERIES_RECONFIG_REMOVE ; 
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct device_node*) ; 
 int /*<<< orphan*/  of_detach_node (struct device_node*) ; 
 struct device_node* of_get_next_child (struct device_node*,int /*<<< orphan*/ *) ; 
 struct device_node* of_get_parent (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  pSeries_reconfig_chain ; 
 int /*<<< orphan*/  remove_node_proc_entries (struct device_node*) ; 

__attribute__((used)) static int pSeries_reconfig_remove_node(struct device_node *np)
{
	struct device_node *parent, *child;

	parent = of_get_parent(np);
	if (!parent)
		return -EINVAL;

	if ((child = of_get_next_child(np, NULL))) {
		of_node_put(child);
		of_node_put(parent);
		return -EBUSY;
	}

	remove_node_proc_entries(np);

	blocking_notifier_call_chain(&pSeries_reconfig_chain,
			    PSERIES_RECONFIG_REMOVE, np);
	of_detach_node(np);

	of_node_put(parent);
	of_node_put(np); /* Must decrement the refcount */
	return 0;
}