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
struct ipu_irq_map {unsigned int source; } ;

/* Variables and functions */
 int CONFIG_MX3_IPU_IRQS ; 
 struct ipu_irq_map* irq_map ; 

__attribute__((used)) static struct ipu_irq_map *src2map(unsigned int src)
{
	int i;

	for (i = 0; i < CONFIG_MX3_IPU_IRQS; i++)
		if (irq_map[i].source == src)
			return irq_map + i;

	return NULL;
}