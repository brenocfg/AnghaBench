#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct irq_host_ops {int /*<<< orphan*/  (* map ) (struct irq_host*,unsigned int,unsigned int) ;int /*<<< orphan*/ * match; } ;
struct TYPE_5__ {unsigned int size; unsigned int* revmap; } ;
struct TYPE_6__ {TYPE_1__ linear; } ;
struct irq_host {unsigned int revmap_type; TYPE_2__ revmap_data; int /*<<< orphan*/  inval_irq; int /*<<< orphan*/  link; struct irq_host_ops* ops; int /*<<< orphan*/  of_node; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;
struct TYPE_8__ {int /*<<< orphan*/  status; } ;
struct TYPE_7__ {unsigned int hwirq; struct irq_host* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  IRQ_HOST_MAP_LEGACY 129 
#define  IRQ_HOST_MAP_LINEAR 128 
 int /*<<< orphan*/  IRQ_NOREQUEST ; 
 unsigned int NO_IRQ ; 
 unsigned int NUM_ISA_INTERRUPTS ; 
 int /*<<< orphan*/ * default_irq_host_match ; 
 TYPE_4__* get_irq_desc (unsigned int) ; 
 int /*<<< orphan*/  irq_big_lock ; 
 int /*<<< orphan*/  irq_hosts ; 
 TYPE_3__* irq_map ; 
 int /*<<< orphan*/  kfree (struct irq_host*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mem_init_done ; 
 int /*<<< orphan*/  of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int,struct irq_host*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct irq_host*,unsigned int,unsigned int) ; 
 struct irq_host* zalloc_maybe_bootmem (unsigned int,int /*<<< orphan*/ ) ; 

struct irq_host *irq_alloc_host(struct device_node *of_node,
				unsigned int revmap_type,
				unsigned int revmap_arg,
				struct irq_host_ops *ops,
				irq_hw_number_t inval_irq)
{
	struct irq_host *host;
	unsigned int size = sizeof(struct irq_host);
	unsigned int i;
	unsigned int *rmap;
	unsigned long flags;

	/* Allocate structure and revmap table if using linear mapping */
	if (revmap_type == IRQ_HOST_MAP_LINEAR)
		size += revmap_arg * sizeof(unsigned int);
	host = zalloc_maybe_bootmem(size, GFP_KERNEL);
	if (host == NULL)
		return NULL;

	/* Fill structure */
	host->revmap_type = revmap_type;
	host->inval_irq = inval_irq;
	host->ops = ops;
	host->of_node = of_node_get(of_node);

	if (host->ops->match == NULL)
		host->ops->match = default_irq_host_match;

	spin_lock_irqsave(&irq_big_lock, flags);

	/* If it's a legacy controller, check for duplicates and
	 * mark it as allocated (we use irq 0 host pointer for that
	 */
	if (revmap_type == IRQ_HOST_MAP_LEGACY) {
		if (irq_map[0].host != NULL) {
			spin_unlock_irqrestore(&irq_big_lock, flags);
			/* If we are early boot, we can't free the structure,
			 * too bad...
			 * this will be fixed once slab is made available early
			 * instead of the current cruft
			 */
			if (mem_init_done)
				kfree(host);
			return NULL;
		}
		irq_map[0].host = host;
	}

	list_add(&host->link, &irq_hosts);
	spin_unlock_irqrestore(&irq_big_lock, flags);

	/* Additional setups per revmap type */
	switch(revmap_type) {
	case IRQ_HOST_MAP_LEGACY:
		/* 0 is always the invalid number for legacy */
		host->inval_irq = 0;
		/* setup us as the host for all legacy interrupts */
		for (i = 1; i < NUM_ISA_INTERRUPTS; i++) {
			irq_map[i].hwirq = i;
			smp_wmb();
			irq_map[i].host = host;
			smp_wmb();

			/* Clear norequest flags */
			get_irq_desc(i)->status &= ~IRQ_NOREQUEST;

			/* Legacy flags are left to default at this point,
			 * one can then use irq_create_mapping() to
			 * explicitly change them
			 */
			ops->map(host, i, i);
		}
		break;
	case IRQ_HOST_MAP_LINEAR:
		rmap = (unsigned int *)(host + 1);
		for (i = 0; i < revmap_arg; i++)
			rmap[i] = NO_IRQ;
		host->revmap_data.linear.size = revmap_arg;
		smp_wmb();
		host->revmap_data.linear.revmap = rmap;
		break;
	default:
		break;
	}

	pr_debug("irq: Allocated host of type %d @0x%p\n", revmap_type, host);

	return host;
}