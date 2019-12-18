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
struct TYPE_2__ {int /*<<< orphan*/  dest_logical; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_DEST_ALLBUT ; 
 int BITS_PER_LONG ; 
 int NMI_VECTOR ; 
 int /*<<< orphan*/  __default_send_IPI_shortcut (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _flat_send_IPI_mask (unsigned long,int) ; 
 TYPE_1__* apic ; 
 int /*<<< orphan*/  clear_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 unsigned long* cpumask_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of (int) ; 
 int num_online_cpus () ; 
 int smp_processor_id () ; 

__attribute__((used)) static void flat_send_IPI_allbutself(int vector)
{
	int cpu = smp_processor_id();
#ifdef	CONFIG_HOTPLUG_CPU
	int hotplug = 1;
#else
	int hotplug = 0;
#endif
	if (hotplug || vector == NMI_VECTOR) {
		if (!cpumask_equal(cpu_online_mask, cpumask_of(cpu))) {
			unsigned long mask = cpumask_bits(cpu_online_mask)[0];

			if (cpu < BITS_PER_LONG)
				clear_bit(cpu, &mask);

			_flat_send_IPI_mask(mask, vector);
		}
	} else if (num_online_cpus() > 1) {
		__default_send_IPI_shortcut(APIC_DEST_ALLBUT,
					    vector, apic->dest_logical);
	}
}