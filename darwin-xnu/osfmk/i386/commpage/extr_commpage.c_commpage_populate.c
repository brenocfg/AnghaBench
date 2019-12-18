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
typedef  int /*<<< orphan*/  vm_offset_t ;

/* Variables and functions */
 int INTEL_PGBYTES ; 
 int /*<<< orphan*/  VM_PROT_READ ; 
 int _COMM_PAGE32_AREA_USED ; 
 int /*<<< orphan*/  _COMM_PAGE32_BASE_ADDRESS ; 
 int /*<<< orphan*/  _COMM_PAGE32_START_ADDRESS ; 
 int _COMM_PAGE64_AREA_USED ; 
 int /*<<< orphan*/  _COMM_PAGE64_BASE_ADDRESS ; 
 int _cpu_capabilities ; 
 int /*<<< orphan*/  atm_get_diagnostic_config () ; 
 scalar_t__ commPagePtr32 ; 
 scalar_t__ commPagePtr64 ; 
 int /*<<< orphan*/  commpage32_map ; 
 int /*<<< orphan*/  commpage64_map ; 
 int /*<<< orphan*/  commpage_active_cpus_lock ; 
 int /*<<< orphan*/  commpage_boottime_init () ; 
 int /*<<< orphan*/  commpage_init_cpu_capabilities () ; 
 int /*<<< orphan*/  commpage_mach_approximate_time_init () ; 
 int /*<<< orphan*/  commpage_mach_continuous_time_init () ; 
 int /*<<< orphan*/  commpage_populate_one (int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  commpage_update_active_cpus () ; 
 int /*<<< orphan*/  commpage_update_atm_diagnostic_config (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  commpage_update_kdebug_state () ; 
 int /*<<< orphan*/  gtod_time_data32 ; 
 int /*<<< orphan*/  gtod_time_data64 ; 
 int k64Bit ; 
 int /*<<< orphan*/  pmap_commpage32_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmap_commpage64_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtc_nanotime_init_commpage () ; 
 int /*<<< orphan*/  simple_lock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_data32 ; 
 int /*<<< orphan*/  time_data64 ; 

void
commpage_populate( void )
{
	commpage_init_cpu_capabilities();
	
	commpage_populate_one(	commpage32_map, 
				&commPagePtr32,
				_COMM_PAGE32_AREA_USED,
				_COMM_PAGE32_BASE_ADDRESS,
				&time_data32,
				&gtod_time_data32,
				"commpage 32-bit",
				VM_PROT_READ);
#ifndef __LP64__
	pmap_commpage32_init((vm_offset_t) commPagePtr32, _COMM_PAGE32_BASE_ADDRESS, 
			   _COMM_PAGE32_AREA_USED/INTEL_PGBYTES);
#endif			   
	time_data64 = time_data32;			/* if no 64-bit commpage, point to 32-bit */
	gtod_time_data64 = gtod_time_data32;

	if (_cpu_capabilities & k64Bit) {
		commpage_populate_one(	commpage64_map, 
					&commPagePtr64,
					_COMM_PAGE64_AREA_USED,
					_COMM_PAGE32_START_ADDRESS, /* commpage address are relative to 32-bit commpage placement */
					&time_data64,
					&gtod_time_data64,
					"commpage 64-bit",
					VM_PROT_READ);
#ifndef __LP64__
		pmap_commpage64_init((vm_offset_t) commPagePtr64, _COMM_PAGE64_BASE_ADDRESS, 
				   _COMM_PAGE64_AREA_USED/INTEL_PGBYTES);
#endif
	}

	simple_lock_init(&commpage_active_cpus_lock, 0);

	commpage_update_active_cpus();
	commpage_mach_approximate_time_init();
	commpage_mach_continuous_time_init();
	commpage_boottime_init();
	rtc_nanotime_init_commpage();
	commpage_update_kdebug_state();
#if CONFIG_ATM
	commpage_update_atm_diagnostic_config(atm_get_diagnostic_config());
#endif
}