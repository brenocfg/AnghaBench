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

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned int*) ; 
 unsigned int DMTE0_IRQ ; 
 unsigned int DMTE6_IRQ ; 
 unsigned int* dmte_irq_map ; 

__attribute__((used)) static inline unsigned int get_dmte_irq(unsigned int chan)
{
	unsigned int irq = 0;
	if (chan < ARRAY_SIZE(dmte_irq_map))
		irq = dmte_irq_map[chan];

#if defined(CONFIG_SH_DMA_IRQ_MULTI)
	if (irq > DMTE6_IRQ)
		return DMTE6_IRQ;
	return DMTE0_IRQ;
#else
	return irq;
#endif
}