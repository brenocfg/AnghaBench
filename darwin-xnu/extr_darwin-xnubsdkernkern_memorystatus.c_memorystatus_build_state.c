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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  TYPE_1__* proc_t ;
struct TYPE_3__ {int p_memstat_state; int p_memstat_dirty; } ;

/* Variables and functions */
 int P_DIRTY_IDLE_EXIT_ENABLED ; 
 int P_DIRTY_IS_DIRTY ; 
 int P_DIRTY_TRACK ; 
 int P_MEMSTAT_FROZEN ; 
 int P_MEMSTAT_REFREEZE_ELIGIBLE ; 
 int P_MEMSTAT_SUSPENDED ; 
 int /*<<< orphan*/  kMemorystatusDirty ; 
 int /*<<< orphan*/  kMemorystatusFrozen ; 
 int /*<<< orphan*/  kMemorystatusSupportsIdleExit ; 
 int /*<<< orphan*/  kMemorystatusSuspended ; 
 int /*<<< orphan*/  kMemorystatusTracked ; 
 int /*<<< orphan*/  kMemorystatusWasThawed ; 

__attribute__((used)) static uint32_t
memorystatus_build_state(proc_t p) {
	uint32_t snapshot_state = 0;
    
	/* General */
	if (p->p_memstat_state & P_MEMSTAT_SUSPENDED) {
		snapshot_state |= kMemorystatusSuspended;
	}
	if (p->p_memstat_state & P_MEMSTAT_FROZEN) {
		snapshot_state |= kMemorystatusFrozen;
	}
	if (p->p_memstat_state & P_MEMSTAT_REFREEZE_ELIGIBLE) {
 		snapshot_state |= kMemorystatusWasThawed;
	}
	
	/* Tracking */
	if (p->p_memstat_dirty & P_DIRTY_TRACK) {
		snapshot_state |= kMemorystatusTracked;
	}
	if ((p->p_memstat_dirty & P_DIRTY_IDLE_EXIT_ENABLED) == P_DIRTY_IDLE_EXIT_ENABLED) {
		snapshot_state |= kMemorystatusSupportsIdleExit;
	}
	if (p->p_memstat_dirty & P_DIRTY_IS_DIRTY) {
		snapshot_state |= kMemorystatusDirty;
	}

	return snapshot_state;
}