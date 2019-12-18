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
struct TYPE_2__ {int ipmask; } ;
union iucv_param {TYPE_1__ set_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  IUCV_SETCONTROLMASK ; 
 int /*<<< orphan*/  IUCV_SETMASK ; 
 int /*<<< orphan*/  cpu_clear (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iucv_call_b2f0 (int /*<<< orphan*/ ,union iucv_param*) ; 
 int /*<<< orphan*/  iucv_irq_cpumask ; 
 union iucv_param** iucv_param_irq ; 
 int /*<<< orphan*/  memset (union iucv_param*,int /*<<< orphan*/ ,int) ; 
 int smp_processor_id () ; 

__attribute__((used)) static void iucv_block_cpu_almost(void *data)
{
	int cpu = smp_processor_id();
	union iucv_param *parm;

	/* Allow iucv control interrupts only */
	parm = iucv_param_irq[cpu];
	memset(parm, 0, sizeof(union iucv_param));
	parm->set_mask.ipmask = 0x08;
	iucv_call_b2f0(IUCV_SETMASK, parm);
	/* Allow iucv-severed interrupt only */
	memset(parm, 0, sizeof(union iucv_param));
	parm->set_mask.ipmask = 0x20;
	iucv_call_b2f0(IUCV_SETCONTROLMASK, parm);

	/* Clear indication that iucv interrupts are allowed for this cpu. */
	cpu_clear(cpu, iucv_irq_cpumask);
}