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
typedef  int pid_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ kMemorystatusKilledFCThrashing ; 
 scalar_t__ kMemorystatusKilledVMCompressorSpaceShortage ; 
 scalar_t__ kMemorystatusKilledVMCompressorThrashing ; 
 scalar_t__ kMemorystatusKilledVMPageShortage ; 
 scalar_t__ kMemorystatusKilledZoneMapExhaustion ; 
 scalar_t__ kill_under_pressure_cause ; 
 int /*<<< orphan*/  memorystatus_thread_wake () ; 

__attribute__((used)) static boolean_t 
memorystatus_kill_process_async(pid_t victim_pid, uint32_t cause) {
	/*
	 * TODO: allow a general async path
	 *
	 * NOTE: If a new async kill cause is added, make sure to update memorystatus_thread() to
	 * add the appropriate exit reason code mapping.
	 */
	if ((victim_pid != -1) ||
			(cause != kMemorystatusKilledVMPageShortage &&
			cause != kMemorystatusKilledVMCompressorThrashing &&
			cause != kMemorystatusKilledVMCompressorSpaceShortage &&
			cause != kMemorystatusKilledFCThrashing &&
			cause != kMemorystatusKilledZoneMapExhaustion)) {
		return FALSE;
	}
    
	kill_under_pressure_cause = cause;
	memorystatus_thread_wake();
	return TRUE;
}