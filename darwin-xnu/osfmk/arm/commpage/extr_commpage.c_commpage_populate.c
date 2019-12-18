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
typedef  scalar_t__ vm_address_t ;
typedef  int uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  scalar_t__ clock_usec_t ;
typedef  int clock_sec_t ;
struct TYPE_2__ {scalar_t__ max_mem; scalar_t__ logical_cpu_max; scalar_t__ physical_cpu_max; } ;

/* Variables and functions */
 scalar_t__ PAGE_SHIFT ; 
 scalar_t__ PE_i_can_has_debugger (int /*<<< orphan*/ *) ; 
 scalar_t__ SIXTEENK_PAGE_SHIFT ; 
 int USEC_PER_SEC ; 
 scalar_t__ _COMM_PAGE_APPROX_TIME ; 
 scalar_t__ _COMM_PAGE_APPROX_TIME_SUPPORTED ; 
 scalar_t__ _COMM_PAGE_BASE_ADDRESS ; 
 scalar_t__ _COMM_PAGE_CACHE_LINESIZE ; 
 scalar_t__ _COMM_PAGE_CONT_HWCLOCK ; 
 scalar_t__ _COMM_PAGE_CPUFAMILY ; 
 scalar_t__ _COMM_PAGE_DEV_FIRM ; 
 scalar_t__ _COMM_PAGE_KERNEL_PAGE_SHIFT ; 
 scalar_t__ _COMM_PAGE_LOGICAL_CPUS ; 
 scalar_t__ _COMM_PAGE_MEMORY_SIZE ; 
 scalar_t__ _COMM_PAGE_PHYSICAL_CPUS ; 
 scalar_t__ _COMM_PAGE_RW_OFFSET ; 
 scalar_t__ _COMM_PAGE_SPIN_COUNT ; 
 scalar_t__ _COMM_PAGE_THIS_VERSION ; 
 scalar_t__ _COMM_PAGE_USER_PAGE_SHIFT_32 ; 
 scalar_t__ _COMM_PAGE_USER_PAGE_SHIFT_64 ; 
 scalar_t__ _COMM_PAGE_USER_TIMEBASE ; 
 scalar_t__ _COMM_PAGE_VERSION ; 
 int _cpu_capabilities ; 
 int /*<<< orphan*/  atm_get_diagnostic_config () ; 
 int /*<<< orphan*/  clock_get_boottime_microtime (int*,scalar_t__*) ; 
 scalar_t__ commPagePtr ; 
 int /*<<< orphan*/  commpage_init_cpu_capabilities () ; 
 int /*<<< orphan*/  commpage_set_timestamp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  commpage_update_active_cpus () ; 
 int /*<<< orphan*/  commpage_update_atm_diagnostic_config (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  commpage_update_boottime (scalar_t__) ; 
 int /*<<< orphan*/  commpage_update_kdebug_state () ; 
 int /*<<< orphan*/  commpage_update_mach_continuous_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  commpage_update_timebase () ; 
 int cpuid_get_cpufamily () ; 
 int kCache128 ; 
 int kCache32 ; 
 int kCache64 ; 
 TYPE_1__ machine_info ; 
 scalar_t__ page_shift ; 
 scalar_t__ page_shift_user32 ; 
 int /*<<< orphan*/  pmap_create_sharedpage () ; 
 int /*<<< orphan*/  sharedpage_rw_addr ; 
 int user_cont_hwclock_allowed () ; 
 int user_timebase_allowed () ; 

void
commpage_populate(
	void)
{
	uint16_t	c2;
	int cpufamily;

	sharedpage_rw_addr = pmap_create_sharedpage();
	commPagePtr = (vm_address_t)_COMM_PAGE_BASE_ADDRESS;

	*((uint16_t*)(_COMM_PAGE_VERSION+_COMM_PAGE_RW_OFFSET)) = (uint16_t) _COMM_PAGE_THIS_VERSION;

	commpage_init_cpu_capabilities();
	commpage_set_timestamp(0, 0, 0, 0, 0);

	if (_cpu_capabilities & kCache32)
		c2 = 32;
	else if (_cpu_capabilities & kCache64)
		c2 = 64;
	else if (_cpu_capabilities & kCache128)
		c2 = 128;
	else
		c2 = 0;

	*((uint16_t*)(_COMM_PAGE_CACHE_LINESIZE+_COMM_PAGE_RW_OFFSET)) = c2;
	*((uint32_t*)(_COMM_PAGE_SPIN_COUNT+_COMM_PAGE_RW_OFFSET)) = 1;

	commpage_update_active_cpus();
	cpufamily = cpuid_get_cpufamily();

	/* machine_info valid after ml_get_max_cpus() */
	*((uint8_t*)(_COMM_PAGE_PHYSICAL_CPUS+_COMM_PAGE_RW_OFFSET)) = (uint8_t) machine_info.physical_cpu_max;
	*((uint8_t*)(_COMM_PAGE_LOGICAL_CPUS+_COMM_PAGE_RW_OFFSET))= (uint8_t) machine_info.logical_cpu_max;
	*((uint64_t*)(_COMM_PAGE_MEMORY_SIZE+_COMM_PAGE_RW_OFFSET)) = machine_info.max_mem;
	*((uint32_t*)(_COMM_PAGE_CPUFAMILY+_COMM_PAGE_RW_OFFSET)) = (uint32_t)cpufamily;
	*((uint32_t*)(_COMM_PAGE_DEV_FIRM+_COMM_PAGE_RW_OFFSET)) = (uint32_t)PE_i_can_has_debugger(NULL);
	*((uint8_t*)(_COMM_PAGE_USER_TIMEBASE+_COMM_PAGE_RW_OFFSET)) = user_timebase_allowed();
	*((uint8_t*)(_COMM_PAGE_CONT_HWCLOCK+_COMM_PAGE_RW_OFFSET)) = user_cont_hwclock_allowed();
	*((uint8_t*)(_COMM_PAGE_KERNEL_PAGE_SHIFT+_COMM_PAGE_RW_OFFSET)) = (uint8_t) page_shift;

#if __arm64__
	*((uint8_t*)(_COMM_PAGE_USER_PAGE_SHIFT_32+_COMM_PAGE_RW_OFFSET)) = (uint8_t) page_shift_user32;
	*((uint8_t*)(_COMM_PAGE_USER_PAGE_SHIFT_64+_COMM_PAGE_RW_OFFSET)) = (uint8_t) SIXTEENK_PAGE_SHIFT;
#elif (__ARM_ARCH_7K__ >= 2) && defined(PLATFORM_WatchOS)
	/* enforce 16KB alignment for watch targets with new ABI */
	*((uint8_t*)(_COMM_PAGE_USER_PAGE_SHIFT_32+_COMM_PAGE_RW_OFFSET)) = (uint8_t) SIXTEENK_PAGE_SHIFT;
	*((uint8_t*)(_COMM_PAGE_USER_PAGE_SHIFT_64+_COMM_PAGE_RW_OFFSET)) = (uint8_t) SIXTEENK_PAGE_SHIFT;
#else /* __arm64__ */
	*((uint8_t*)(_COMM_PAGE_USER_PAGE_SHIFT_32+_COMM_PAGE_RW_OFFSET)) = (uint8_t) PAGE_SHIFT;
	*((uint8_t*)(_COMM_PAGE_USER_PAGE_SHIFT_64+_COMM_PAGE_RW_OFFSET)) = (uint8_t) PAGE_SHIFT;
#endif /* __arm64__ */

	commpage_update_timebase();
	commpage_update_mach_continuous_time(0);

	clock_sec_t secs;
	clock_usec_t microsecs;
	clock_get_boottime_microtime(&secs, &microsecs);
	commpage_update_boottime(secs * USEC_PER_SEC + microsecs);

	/* 
	 * set commpage approximate time to zero for initialization. 
	 * scheduler shall populate correct value before running user thread
	 */
	*((uint64_t *)(_COMM_PAGE_APPROX_TIME+ _COMM_PAGE_RW_OFFSET)) = 0;
#ifdef CONFIG_MACH_APPROXIMATE_TIME
	*((uint8_t *)(_COMM_PAGE_APPROX_TIME_SUPPORTED+_COMM_PAGE_RW_OFFSET)) = 1;
#else
	*((uint8_t *)(_COMM_PAGE_APPROX_TIME_SUPPORTED+_COMM_PAGE_RW_OFFSET)) = 0;
#endif

	commpage_update_kdebug_state();

#if CONFIG_ATM
	commpage_update_atm_diagnostic_config(atm_get_diagnostic_config());
#endif

}