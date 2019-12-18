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
struct irq_host {scalar_t__ revmap_type; } ;
typedef  unsigned int irq_hw_number_t ;
struct TYPE_2__ {unsigned int hwirq; struct irq_host* host; } ;

/* Variables and functions */
 scalar_t__ IRQ_HOST_MAP_LEGACY ; 
 unsigned int NO_IRQ ; 
 unsigned int NUM_ISA_INTERRUPTS ; 
 struct irq_host* irq_default_host ; 
 TYPE_1__* irq_map ; 
 unsigned int irq_virq_count ; 

unsigned int irq_find_mapping(struct irq_host *host,
			      irq_hw_number_t hwirq)
{
	unsigned int i;
	unsigned int hint = hwirq % irq_virq_count;

	/* Look for default host if nececssary */
	if (host == NULL)
		host = irq_default_host;
	if (host == NULL)
		return NO_IRQ;

	/* legacy -> bail early */
	if (host->revmap_type == IRQ_HOST_MAP_LEGACY)
		return hwirq;

	/* Slow path does a linear search of the map */
	if (hint < NUM_ISA_INTERRUPTS)
		hint = NUM_ISA_INTERRUPTS;
	i = hint;
	do  {
		if (irq_map[i].host == host &&
		    irq_map[i].hwirq == hwirq)
			return i;
		i++;
		if (i >= irq_virq_count)
			i = NUM_ISA_INTERRUPTS;
	} while(i != hint);
	return NO_IRQ;
}