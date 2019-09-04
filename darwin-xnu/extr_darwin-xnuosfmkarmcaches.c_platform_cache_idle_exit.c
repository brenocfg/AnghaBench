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

void
platform_cache_idle_exit(
	void)
{
#if defined (ARMA7)
	uint32_t actlr_value = 0;

	/* Flush L1 caches and TLB before rejoining the coherency domain */
	FlushPoU_Dcache();
	/*
	 * If we're only using a single CPU, we can avoid flushing the
	 * I-cache or the TLB, as neither program text nor pagetables
	 * should have been changed during the idle period.  We still
	 * want to flush the D-cache to PoU (above), as memory contents
	 * may have been changed by DMA.
	 */
	if (!up_style_idle_exit || (real_ncpus > 1)) {
		InvalidatePoU_Icache();
		flush_core_tlb();
	}

	/* Rejoin the coherency domain */
	__asm__ volatile("mrc p15, 0, %0, c1, c0, 1\n"
	                 : "=r"(actlr_value));

	actlr_value |= 0x40;

	__asm__ volatile("mcr p15, 0, %0, c1, c0, 1\n"
	                 "isb\n"
	                 :: "r"(actlr_value));

#if __ARM_SMP__
	uint32_t sctlr_value = 0;

	/* Enable dcache allocation. */
	__asm__ volatile("mrc p15, 0, %0, c1, c0, 0\n"
	                 : "=r"(sctlr_value));

	sctlr_value |= SCTLR_DCACHE;

	__asm__ volatile("mcr p15, 0, %0, c1, c0, 0\n"
	                 "isb"
	                 :: "r"(sctlr_value));
	getCpuDatap()->cpu_CLW_active = 1;
#endif
#endif
}