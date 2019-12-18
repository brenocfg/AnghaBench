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
struct TYPE_2__ {int /*<<< orphan*/  tree; } ;
struct irq_host {scalar_t__ revmap_type; TYPE_1__ revmap_data; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 scalar_t__ IRQ_HOST_MAP_TREE ; 
 unsigned int NO_IRQ ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/ * irq_map ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radix_tree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int revmap_trees_allocated ; 
 int /*<<< orphan*/  revmap_trees_mutex ; 
 int /*<<< orphan*/  smp_rmb () ; 

void irq_radix_revmap_insert(struct irq_host *host, unsigned int virq,
			     irq_hw_number_t hwirq)
{

	WARN_ON(host->revmap_type != IRQ_HOST_MAP_TREE);

	/*
	 * Check if the radix tree exists yet.
	 * If not, then the irq will be inserted into the tree when it gets
	 * initialized.
	 */
	smp_rmb();
	if (revmap_trees_allocated < 1)
		return;

	if (virq != NO_IRQ) {
		mutex_lock(&revmap_trees_mutex);
		radix_tree_insert(&host->revmap_data.tree, hwirq,
				  &irq_map[virq]);
		mutex_unlock(&revmap_trees_mutex);
	}
}