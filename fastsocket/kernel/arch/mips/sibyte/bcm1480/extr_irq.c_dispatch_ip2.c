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

/* Variables and functions */
 unsigned long A_BCM1480_IMR_MAPPER (unsigned int) ; 
 int /*<<< orphan*/  IOADDR (scalar_t__) ; 
 scalar_t__ R_BCM1480_IMR_INTERRUPT_STATUS_BASE_H ; 
 scalar_t__ R_BCM1480_IMR_INTERRUPT_STATUS_BASE_L ; 
 unsigned long long __raw_readq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_IRQ (scalar_t__) ; 
 scalar_t__ fls64 (unsigned long long) ; 
 unsigned int smp_processor_id () ; 

__attribute__((used)) static inline void dispatch_ip2(void)
{
	unsigned long long mask_h, mask_l;
	unsigned int cpu = smp_processor_id();
	unsigned long base;

	/*
	 * Default...we've hit an IP[2] interrupt, which means we've got to
	 * check the 1480 interrupt registers to figure out what to do.  Need
	 * to detect which CPU we're on, now that smp_affinity is supported.
	 */
	base = A_BCM1480_IMR_MAPPER(cpu);
	mask_h = __raw_readq(
		IOADDR(base + R_BCM1480_IMR_INTERRUPT_STATUS_BASE_H));
	mask_l = __raw_readq(
		IOADDR(base + R_BCM1480_IMR_INTERRUPT_STATUS_BASE_L));

	if (mask_h) {
		if (mask_h ^ 1)
			do_IRQ(fls64(mask_h) - 1);
		else if (mask_l)
			do_IRQ(63 + fls64(mask_l));
	}
}