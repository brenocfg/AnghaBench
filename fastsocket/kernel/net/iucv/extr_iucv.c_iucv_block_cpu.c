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
 int /*<<< orphan*/  IUCV_SETMASK ; 
 int /*<<< orphan*/  cpu_clear (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iucv_call_b2f0 (int /*<<< orphan*/ ,union iucv_param*) ; 
 int /*<<< orphan*/  iucv_irq_cpumask ; 
 union iucv_param** iucv_param_irq ; 
 int /*<<< orphan*/  memset (union iucv_param*,int /*<<< orphan*/ ,int) ; 
 int smp_processor_id () ; 

__attribute__((used)) static void iucv_block_cpu(void *data)
{
	int cpu = smp_processor_id();
	union iucv_param *parm;

	/* Disable all iucv interrupts. */
	parm = iucv_param_irq[cpu];
	memset(parm, 0, sizeof(union iucv_param));
	iucv_call_b2f0(IUCV_SETMASK, parm);

	/* Clear indication that iucv interrupts are allowed for this cpu. */
	cpu_clear(cpu, iucv_irq_cpumask);
}