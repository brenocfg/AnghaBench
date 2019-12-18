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
struct irq_host {scalar_t__ revmap_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ IRQ_HOST_MAP_NOMAP ; 
 unsigned int NO_IRQ ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned int irq_alloc_virt (struct irq_host*,int,int /*<<< orphan*/ ) ; 
 struct irq_host* irq_default_host ; 
 scalar_t__ irq_setup_virq (struct irq_host*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

unsigned int irq_create_direct_mapping(struct irq_host *host)
{
	unsigned int virq;

	if (host == NULL)
		host = irq_default_host;

	BUG_ON(host == NULL);
	WARN_ON(host->revmap_type != IRQ_HOST_MAP_NOMAP);

	virq = irq_alloc_virt(host, 1, 0);
	if (virq == NO_IRQ) {
		pr_debug("irq: create_direct virq allocation failed\n");
		return NO_IRQ;
	}

	pr_debug("irq: create_direct obtained virq %d\n", virq);

	if (irq_setup_virq(host, virq, virq))
		return NO_IRQ;

	return virq;
}