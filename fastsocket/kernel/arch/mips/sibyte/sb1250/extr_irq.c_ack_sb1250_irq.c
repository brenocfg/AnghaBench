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
typedef  scalar_t__ uint32_t ;
typedef  unsigned int u64 ;

/* Variables and functions */
 int /*<<< orphan*/  A_IMR_REGISTER (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOADDR (int /*<<< orphan*/ ) ; 
 int NR_CPUS ; 
 int /*<<< orphan*/  R_IMR_LDT_INTERRUPT ; 
 int /*<<< orphan*/  R_IMR_LDT_INTERRUPT_CLR ; 
 unsigned int __raw_readq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writeq (unsigned int,int /*<<< orphan*/ ) ; 
 int cpu_logical_map (int) ; 
 scalar_t__ ldt_eoi_space ; 
 int* sb1250_irq_owner ; 
 int /*<<< orphan*/  sb1250_mask_irq (int,unsigned int) ; 

__attribute__((used)) static void ack_sb1250_irq(unsigned int irq)
{
#ifdef CONFIG_SIBYTE_HAS_LDT
	u64 pending;

	/*
	 * If the interrupt was an HT interrupt, now is the time to
	 * clear it.  NOTE: we assume the HT bridge was set up to
	 * deliver the interrupts to all CPUs (which makes affinity
	 * changing easier for us)
	 */
	pending = __raw_readq(IOADDR(A_IMR_REGISTER(sb1250_irq_owner[irq],
						    R_IMR_LDT_INTERRUPT)));
	pending &= ((u64)1 << (irq));
	if (pending) {
		int i;
		for (i=0; i<NR_CPUS; i++) {
			int cpu;
#ifdef CONFIG_SMP
			cpu = cpu_logical_map(i);
#else
			cpu = i;
#endif
			/*
			 * Clear for all CPUs so an affinity switch
			 * doesn't find an old status
			 */
			__raw_writeq(pending,
				     IOADDR(A_IMR_REGISTER(cpu,
						R_IMR_LDT_INTERRUPT_CLR)));
		}

		/*
		 * Generate EOI.  For Pass 1 parts, EOI is a nop.  For
		 * Pass 2, the LDT world may be edge-triggered, but
		 * this EOI shouldn't hurt.  If they are
		 * level-sensitive, the EOI is required.
		 */
		*(uint32_t *)(ldt_eoi_space+(irq<<16)+(7<<2)) = 0;
	}
#endif
	sb1250_mask_irq(sb1250_irq_owner[irq], irq);
}