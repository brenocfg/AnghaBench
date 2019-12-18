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
typedef  union iucv_param {int dummy; } iucv_param ;

/* Variables and functions */
 int /*<<< orphan*/  IUCV_RETRIEVE_BUFFER ; 
 int /*<<< orphan*/  cpu_clear (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_isset (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iucv_block_cpu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iucv_buffer_cpumask ; 
 int /*<<< orphan*/  iucv_call_b2f0 (int /*<<< orphan*/ ,union iucv_param*) ; 
 union iucv_param** iucv_param_irq ; 
 int smp_processor_id () ; 

__attribute__((used)) static void iucv_retrieve_cpu(void *data)
{
	int cpu = smp_processor_id();
	union iucv_param *parm;

	if (!cpu_isset(cpu, iucv_buffer_cpumask))
		return;

	/* Block iucv interrupts. */
	iucv_block_cpu(NULL);

	/* Retrieve interrupt buffer. */
	parm = iucv_param_irq[cpu];
	iucv_call_b2f0(IUCV_RETRIEVE_BUFFER, parm);

	/* Clear indication that an iucv buffer exists for this cpu. */
	cpu_clear(cpu, iucv_buffer_cpumask);
}