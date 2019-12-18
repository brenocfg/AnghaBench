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
struct cpumask {int dummy; } ;

/* Variables and functions */
 unsigned int cpumask_first (struct cpumask const*) ; 
 int rebind_irq_to_cpu (unsigned int,unsigned int) ; 

__attribute__((used)) static int set_affinity_irq(unsigned irq, const struct cpumask *dest)
{
	unsigned tcpu = cpumask_first(dest);

	return rebind_irq_to_cpu(irq, tcpu);
}