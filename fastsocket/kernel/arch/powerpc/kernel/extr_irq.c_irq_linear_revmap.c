#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t size; unsigned int* revmap; } ;
struct TYPE_4__ {TYPE_1__ linear; } ;
struct irq_host {scalar_t__ revmap_type; TYPE_2__ revmap_data; } ;
typedef  size_t irq_hw_number_t ;

/* Variables and functions */
 scalar_t__ IRQ_HOST_MAP_LINEAR ; 
 unsigned int NO_IRQ ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned int irq_find_mapping (struct irq_host*,size_t) ; 
 scalar_t__ unlikely (int) ; 

unsigned int irq_linear_revmap(struct irq_host *host,
			       irq_hw_number_t hwirq)
{
	unsigned int *revmap;

	WARN_ON(host->revmap_type != IRQ_HOST_MAP_LINEAR);

	/* Check revmap bounds */
	if (unlikely(hwirq >= host->revmap_data.linear.size))
		return irq_find_mapping(host, hwirq);

	/* Check if revmap was allocated */
	revmap = host->revmap_data.linear.revmap;
	if (unlikely(revmap == NULL))
		return irq_find_mapping(host, hwirq);

	/* Fill up revmap with slow path if no mapping found */
	if (unlikely(revmap[hwirq] == NO_IRQ))
		revmap[hwirq] = irq_find_mapping(host, hwirq);

	return revmap[hwirq];
}