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
 int /*<<< orphan*/  cpu_set (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iucv_call_b2f0 (int /*<<< orphan*/ ,union iucv_param*) ; 
 int /*<<< orphan*/  iucv_irq_cpumask ; 
 union iucv_param** iucv_param_irq ; 
 int /*<<< orphan*/  memset (union iucv_param*,int /*<<< orphan*/ ,int) ; 
 int smp_processor_id () ; 

__attribute__((used)) static void iucv_allow_cpu(void *data)
{
	int cpu = smp_processor_id();
	union iucv_param *parm;

	/*
	 * Enable all iucv interrupts.
	 * ipmask contains bits for the different interrupts
	 *	0x80 - Flag to allow nonpriority message pending interrupts
	 *	0x40 - Flag to allow priority message pending interrupts
	 *	0x20 - Flag to allow nonpriority message completion interrupts
	 *	0x10 - Flag to allow priority message completion interrupts
	 *	0x08 - Flag to allow IUCV control interrupts
	 */
	parm = iucv_param_irq[cpu];
	memset(parm, 0, sizeof(union iucv_param));
	parm->set_mask.ipmask = 0xf8;
	iucv_call_b2f0(IUCV_SETMASK, parm);

	/*
	 * Enable all iucv control interrupts.
	 * ipmask contains bits for the different interrupts
	 *	0x80 - Flag to allow pending connections interrupts
	 *	0x40 - Flag to allow connection complete interrupts
	 *	0x20 - Flag to allow connection severed interrupts
	 *	0x10 - Flag to allow connection quiesced interrupts
	 *	0x08 - Flag to allow connection resumed interrupts
	 */
	memset(parm, 0, sizeof(union iucv_param));
	parm->set_mask.ipmask = 0xf8;
	iucv_call_b2f0(IUCV_SETCONTROLMASK, parm);
	/* Set indication that iucv interrupts are allowed for this cpu. */
	cpu_set(cpu, iucv_irq_cpumask);
}