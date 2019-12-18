#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t size; unsigned int* revmap; } ;
struct TYPE_8__ {int /*<<< orphan*/  tree; TYPE_2__ linear; } ;
struct irq_host {int revmap_type; size_t inval_irq; TYPE_3__ revmap_data; TYPE_1__* ops; } ;
typedef  size_t irq_hw_number_t ;
struct TYPE_10__ {int /*<<< orphan*/  status; } ;
struct TYPE_9__ {size_t hwirq; struct irq_host* host; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* unmap ) (struct irq_host*,unsigned int) ;} ;

/* Variables and functions */
 int IRQ_HOST_MAP_LEGACY ; 
#define  IRQ_HOST_MAP_LINEAR 129 
#define  IRQ_HOST_MAP_TREE 128 
 int /*<<< orphan*/  IRQ_NOREQUEST ; 
 unsigned int NO_IRQ ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 TYPE_5__* get_irq_desc (unsigned int) ; 
 int /*<<< orphan*/  irq_free_virt (unsigned int,int) ; 
 TYPE_4__* irq_map ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radix_tree_delete (int /*<<< orphan*/ *,size_t) ; 
 int revmap_trees_allocated ; 
 int /*<<< orphan*/  revmap_trees_mutex ; 
 int /*<<< orphan*/  set_irq_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  stub1 (struct irq_host*,unsigned int) ; 
 int /*<<< orphan*/  synchronize_irq (unsigned int) ; 

void irq_dispose_mapping(unsigned int virq)
{
	struct irq_host *host;
	irq_hw_number_t hwirq;

	if (virq == NO_IRQ)
		return;

	host = irq_map[virq].host;
	WARN_ON (host == NULL);
	if (host == NULL)
		return;

	/* Never unmap legacy interrupts */
	if (host->revmap_type == IRQ_HOST_MAP_LEGACY)
		return;

	/* remove chip and handler */
	set_irq_chip_and_handler(virq, NULL, NULL);

	/* Make sure it's completed */
	synchronize_irq(virq);

	/* Tell the PIC about it */
	if (host->ops->unmap)
		host->ops->unmap(host, virq);
	smp_mb();

	/* Clear reverse map */
	hwirq = irq_map[virq].hwirq;
	switch(host->revmap_type) {
	case IRQ_HOST_MAP_LINEAR:
		if (hwirq < host->revmap_data.linear.size)
			host->revmap_data.linear.revmap[hwirq] = NO_IRQ;
		break;
	case IRQ_HOST_MAP_TREE:
		/*
		 * Check if radix tree allocated yet, if not then nothing to
		 * remove.
		 */
		smp_rmb();
		if (revmap_trees_allocated < 1)
			break;
		mutex_lock(&revmap_trees_mutex);
		radix_tree_delete(&host->revmap_data.tree, hwirq);
		mutex_unlock(&revmap_trees_mutex);
		break;
	}

	/* Destroy map */
	smp_mb();
	irq_map[virq].hwirq = host->inval_irq;

	/* Set some flags */
	get_irq_desc(virq)->status |= IRQ_NOREQUEST;

	/* Free it */
	irq_free_virt(virq, 1);
}