#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  TYPE_1__* proc_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_6__ {int p_memstat_state; int p_memstat_dirty; int p_memstat_idledeadline; int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  MEMORYSTATUS_DEBUG (int,char*,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 
 int P_DIRTY_AGING_IN_PROGRESS ; 
 int P_DIRTY_IDLE_EXIT_ENABLED ; 
 int P_MEMSTAT_USE_ELEVATED_INACTIVE_BAND ; 
 scalar_t__ TRUE ; 
 scalar_t__ applications_aging_band ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ isApp (TYPE_1__*) ; 
 scalar_t__ isProcessInAgingBands (TYPE_1__*) ; 
 scalar_t__ isSysProc (TYPE_1__*) ; 
 scalar_t__ jetsam_aging_policy ; 
 scalar_t__ kJetsamAgingPolicyLegacy ; 
 scalar_t__ kJetsamAgingPolicyNone ; 
 int mach_absolute_time () ; 
 int memorystatus_apps_idle_delay_time ; 
 scalar_t__ memorystatus_scheduled_idle_demotions_apps ; 
 scalar_t__ memorystatus_scheduled_idle_demotions_sysprocs ; 
 int memorystatus_sysprocs_idle_delay_time ; 
 scalar_t__ system_procs_aging_band ; 

__attribute__((used)) static void
memorystatus_schedule_idle_demotion_locked(proc_t p, boolean_t set_state) 
{	
	boolean_t present_in_sysprocs_aging_bucket = FALSE;
	boolean_t present_in_apps_aging_bucket = FALSE;
	uint64_t  idle_delay_time = 0;

	if (jetsam_aging_policy == kJetsamAgingPolicyNone) {
		return;
	}

	if (p->p_memstat_state & P_MEMSTAT_USE_ELEVATED_INACTIVE_BAND) {
		/*
		 * This process isn't going to be making the trip to the lower bands.
		 */
		return;
	}

	if (isProcessInAgingBands(p)){
		
		if (jetsam_aging_policy != kJetsamAgingPolicyLegacy) {
			assert((p->p_memstat_dirty & P_DIRTY_AGING_IN_PROGRESS) != P_DIRTY_AGING_IN_PROGRESS);
		}

		if (isSysProc(p) && system_procs_aging_band) {
			present_in_sysprocs_aging_bucket = TRUE;

		} else if (isApp(p) && applications_aging_band) {
			present_in_apps_aging_bucket = TRUE;
		}
	}

	assert(!present_in_sysprocs_aging_bucket);
	assert(!present_in_apps_aging_bucket);

	MEMORYSTATUS_DEBUG(1, "memorystatus_schedule_idle_demotion_locked: scheduling demotion to idle band for pid %d (dirty:0x%x, set_state %d, demotions %d).\n", 
	    p->p_pid, p->p_memstat_dirty, set_state, (memorystatus_scheduled_idle_demotions_sysprocs + memorystatus_scheduled_idle_demotions_apps));

	if(isSysProc(p)) {
		assert((p->p_memstat_dirty & P_DIRTY_IDLE_EXIT_ENABLED) == P_DIRTY_IDLE_EXIT_ENABLED);
	}

	idle_delay_time = (isSysProc(p)) ? memorystatus_sysprocs_idle_delay_time : memorystatus_apps_idle_delay_time;

	if (set_state) {
		p->p_memstat_dirty |= P_DIRTY_AGING_IN_PROGRESS;
		p->p_memstat_idledeadline = mach_absolute_time() + idle_delay_time;
	}
	
	assert(p->p_memstat_idledeadline);
	
 	if (isSysProc(p) && present_in_sysprocs_aging_bucket == FALSE) {
		memorystatus_scheduled_idle_demotions_sysprocs++;

	} else if (isApp(p) && present_in_apps_aging_bucket == FALSE) {
		memorystatus_scheduled_idle_demotions_apps++;
	}
}