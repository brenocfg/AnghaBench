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
 int /*<<< orphan*/  A_IMR_REGISTER (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_IMR_INTERRUPT_STATUS_BASE ; 
 unsigned long long __raw_readq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_IRQ (scalar_t__) ; 
 scalar_t__ fls64 (unsigned long long) ; 
 unsigned int smp_processor_id () ; 

__attribute__((used)) static inline void dispatch_ip2(void)
{
	unsigned int cpu = smp_processor_id();
	unsigned long long mask;

	/*
	 * Default...we've hit an IP[2] interrupt, which means we've got to
	 * check the 1250 interrupt registers to figure out what to do.  Need
	 * to detect which CPU we're on, now that smp_affinity is supported.
	 */
	mask = __raw_readq(IOADDR(A_IMR_REGISTER(cpu,
				  R_IMR_INTERRUPT_STATUS_BASE)));
	if (mask)
		do_IRQ(fls64(mask) - 1);
}