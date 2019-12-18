#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int cpu; } ;
struct TYPE_3__ {int /*<<< orphan*/  affinity; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_evtchn_mask (unsigned int) ; 
 unsigned int cpu_from_irq (int) ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of (unsigned int) ; 
 int* evtchn_to_irq ; 
 TYPE_2__* irq_info ; 
 TYPE_1__* irq_to_desc (int) ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bind_evtchn_to_cpu(unsigned int chn, unsigned int cpu)
{
	int irq = evtchn_to_irq[chn];

	BUG_ON(irq == -1);
#ifdef CONFIG_SMP
	cpumask_copy(irq_to_desc(irq)->affinity, cpumask_of(cpu));
#endif

	clear_bit(chn, cpu_evtchn_mask(cpu_from_irq(irq)));
	set_bit(chn, cpu_evtchn_mask(cpu));

	irq_info[irq].cpu = cpu;
}