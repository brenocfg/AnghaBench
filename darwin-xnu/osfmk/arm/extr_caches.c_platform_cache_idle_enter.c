#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int uint32_t ;
struct TYPE_3__ {scalar_t__ cpu_CLWClean_req; scalar_t__ cpu_CLWFlush_req; scalar_t__ cpu_CLW_active; } ;
typedef  TYPE_1__ cpu_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  CleanPoC_DcacheRegion (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CleanPoU_Dcache () ; 
 int /*<<< orphan*/  FlushPoU_Dcache () ; 
 TYPE_1__* getCpuDatap () ; 
 int /*<<< orphan*/  platform_cache_disable () ; 
 int real_ncpus ; 
 scalar_t__ up_style_idle_exit ; 

void
platform_cache_idle_enter(
	void)
{
#if	__ARM_SMP__
	platform_cache_disable();

	/*
	 * If we're only using a single CPU, just write back any
	 * dirty cachelines.  We can avoid doing housekeeping
	 * on CPU data that would normally be modified by other
	 * CPUs.
	 */
	if (up_style_idle_exit && (real_ncpus == 1))
		CleanPoU_Dcache();
	else {
		FlushPoU_Dcache();

#if (__ARM_ARCH__ < 8)
		cpu_data_t	*cpu_data_ptr = getCpuDatap();
		cpu_data_ptr->cpu_CLW_active = 0;
		__asm__ volatile("dmb ish");
		cpu_data_ptr->cpu_CLWFlush_req = 0;
		cpu_data_ptr->cpu_CLWClean_req = 0;
		CleanPoC_DcacheRegion((vm_offset_t) cpu_data_ptr, sizeof(cpu_data_t));
#endif /* (__ARM_ARCH__ < 8) */
	}
#else
	CleanPoU_Dcache();
#endif

#if	 defined (__ARM_SMP__) && defined (ARMA7)
	uint32_t actlr_value = 0;

	/* Leave the coherency domain */
	__asm__ volatile("clrex\n"
	                 "mrc p15, 0, %0, c1, c0, 1\n"
	                 : "=r"(actlr_value));

	actlr_value &= ~0x40;

	__asm__ volatile("mcr p15, 0, %0, c1, c0, 1\n"
	                 /* Ensures any pending fwd request gets serviced and ends up */
	                 "dsb\n"
	                 /* Forces the processor to re-fetch, so any pending fwd request gets into the core */
	                 "isb\n"
	                 /* Ensures the second possible pending fwd request ends up. */
	                 "dsb\n"
	                 :: "r"(actlr_value));
#endif
}