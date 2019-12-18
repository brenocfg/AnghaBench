#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* proc_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_5__ {int p_memstat_dirty; scalar_t__ p_memstat_requestedpriority; scalar_t__ p_memstat_effectivepriority; int p_memstat_state; int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 scalar_t__ JETSAM_PRIORITY_ELEVATED_INACTIVE ; 
 scalar_t__ JETSAM_PRIORITY_IDLE ; 
 int /*<<< orphan*/  MEMORYSTATUS_DEBUG (int,char*,int /*<<< orphan*/ ,int) ; 
 int P_DIRTY_AGING_IN_PROGRESS ; 
 int P_DIRTY_IDLE_EXIT_ENABLED ; 
 int P_DIRTY_IS_DIRTY ; 
 int P_MEMSTAT_USE_ELEVATED_INACTIVE_BAND ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isSysProc (TYPE_1__*) ; 
 scalar_t__ jetsam_aging_policy ; 
 scalar_t__ kJetsamAgingPolicyLegacy ; 
 int /*<<< orphan*/  memorystatus_update_priority_locked (TYPE_1__*,scalar_t__,int,int) ; 
 scalar_t__ system_procs_aging_band ; 

__attribute__((used)) static void
memorystatus_update_idle_priority_locked(proc_t p) {
	int32_t priority;

	MEMORYSTATUS_DEBUG(1, "memorystatus_update_idle_priority_locked(): pid %d dirty 0x%X\n", p->p_pid, p->p_memstat_dirty);

	assert(isSysProc(p));	

	if ((p->p_memstat_dirty & (P_DIRTY_IDLE_EXIT_ENABLED|P_DIRTY_IS_DIRTY)) == P_DIRTY_IDLE_EXIT_ENABLED) {

		priority = (p->p_memstat_dirty & P_DIRTY_AGING_IN_PROGRESS) ? system_procs_aging_band : JETSAM_PRIORITY_IDLE;
	} else {
		priority = p->p_memstat_requestedpriority;
	}
	
	if (priority != p->p_memstat_effectivepriority) {

		if ((jetsam_aging_policy == kJetsamAgingPolicyLegacy) &&
		    (priority == JETSAM_PRIORITY_IDLE)) {

			/*
			 * This process is on its way into the IDLE band. The system is
			 * using 'legacy' jetsam aging policy. That means, this process
			 * has already used up its idle-deferral aging time that is given
			 * once per its lifetime. So we need to set the INACTIVE limits
			 * explicitly because it won't be going through the demotion paths
			 * that take care to apply the limits appropriately.
			 */

			if (p->p_memstat_state & P_MEMSTAT_USE_ELEVATED_INACTIVE_BAND) {

				/*
				 * This process has the 'elevated inactive jetsam band' attribute.
				 * So, there will be no trip to IDLE after all.
				 * Instead, we pin the process in the elevated band,
				 * where its ACTIVE limits will apply.
				 */

				priority = JETSAM_PRIORITY_ELEVATED_INACTIVE;
			}

			memorystatus_update_priority_locked(p, priority, false, true);

		} else {
			memorystatus_update_priority_locked(p, priority, false, false);
		}
	}
}