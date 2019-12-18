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
struct irq_map_entry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tree; } ;
struct irq_host {scalar_t__ revmap_type; TYPE_1__ revmap_data; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 scalar_t__ IRQ_HOST_MAP_TREE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned int irq_find_mapping (struct irq_host*,int /*<<< orphan*/ ) ; 
 struct irq_map_entry* irq_map ; 
 struct irq_map_entry* radix_tree_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int revmap_trees_allocated ; 

unsigned int irq_radix_revmap_lookup(struct irq_host *host,
				     irq_hw_number_t hwirq)
{
	struct irq_map_entry *ptr;
	unsigned int virq;

	WARN_ON(host->revmap_type != IRQ_HOST_MAP_TREE);

	/*
	 * Check if the radix tree exists and has bee initialized.
	 * If not, we fallback to slow mode
	 */
	if (revmap_trees_allocated < 2)
		return irq_find_mapping(host, hwirq);

	/* Now try to resolve */
	/*
	 * No rcu_read_lock(ing) needed, the ptr returned can't go under us
	 * as it's referencing an entry in the static irq_map table.
	 */
	ptr = radix_tree_lookup(&host->revmap_data.tree, hwirq);

	/*
	 * If found in radix tree, then fine.
	 * Else fallback to linear lookup - this should not happen in practice
	 * as it means that we failed to insert the node in the radix tree.
	 */
	if (ptr)
		virq = ptr - irq_map;
	else
		virq = irq_find_mapping(host, hwirq);

	return virq;
}