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
 unsigned int* dmte_irq_map ; 

__attribute__((used)) static unsigned int get_dmae_irq(unsigned int id)
{
	unsigned int irq = 0;
	if (id < ARRAY_SIZE(dmte_irq_map))
		irq = dmte_irq_map[id];
	return irq;
}