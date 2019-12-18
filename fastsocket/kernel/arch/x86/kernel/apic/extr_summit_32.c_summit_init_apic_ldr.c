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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ APIC_CLUSTER (scalar_t__) ; 
 int /*<<< orphan*/  APIC_DFR ; 
 int /*<<< orphan*/  APIC_LDR ; 
 unsigned long APIC_LDR_MASK ; 
 scalar_t__ BAD_APICID ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long SET_APIC_LOGICAL_ID (unsigned long) ; 
 unsigned long SUMMIT_APIC_DFR_VALUE ; 
 int XAPIC_DEST_CPUS_SHIFT ; 
 unsigned long apic_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apic_write (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__* cpu_2_logical_apicid ; 
 int /*<<< orphan*/  hard_smp_processor_id () ; 
 int nr_cpu_ids ; 

__attribute__((used)) static void summit_init_apic_ldr(void)
{
	unsigned long val, id;
	int count = 0;
	u8 my_id = (u8)hard_smp_processor_id();
	u8 my_cluster = APIC_CLUSTER(my_id);
#ifdef CONFIG_SMP
	u8 lid;
	int i;

	/* Create logical APIC IDs by counting CPUs already in cluster. */
	for (count = 0, i = nr_cpu_ids; --i >= 0; ) {
		lid = cpu_2_logical_apicid[i];
		if (lid != BAD_APICID && APIC_CLUSTER(lid) == my_cluster)
			++count;
	}
#endif
	/* We only have a 4 wide bitmap in cluster mode.  If a deranged
	 * BIOS puts 5 CPUs in one APIC cluster, we're hosed. */
	BUG_ON(count >= XAPIC_DEST_CPUS_SHIFT);
	id = my_cluster | (1UL << count);
	apic_write(APIC_DFR, SUMMIT_APIC_DFR_VALUE);
	val = apic_read(APIC_LDR) & ~APIC_LDR_MASK;
	val |= SET_APIC_LOGICAL_ID(id);
	apic_write(APIC_LDR, val);
}