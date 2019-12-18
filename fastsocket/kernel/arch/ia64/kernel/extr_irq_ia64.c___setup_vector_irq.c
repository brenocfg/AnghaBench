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
struct TYPE_2__ {int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 int IA64_NUM_VECTORS ; 
 int NR_IRQS ; 
 int /*<<< orphan*/  cpu_isset (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* irq_cfg ; 
 int irq_to_vector (int) ; 
 int* per_cpu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vector_irq ; 

void __setup_vector_irq(int cpu)
{
	int irq, vector;

	/* Clear vector_irq */
	for (vector = 0; vector < IA64_NUM_VECTORS; ++vector)
		per_cpu(vector_irq, cpu)[vector] = -1;
	/* Mark the inuse vectors */
	for (irq = 0; irq < NR_IRQS; ++irq) {
		if (!cpu_isset(cpu, irq_cfg[irq].domain))
			continue;
		vector = irq_to_vector(irq);
		per_cpu(vector_irq, cpu)[vector] = irq;
	}
}