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
typedef  TYPE_1__* proc_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_6__ {int p_memstat_dirty; scalar_t__ p_memstat_effectivepriority; int p_memstat_idledeadline; int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  MEMORYSTATUS_DEBUG (int,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int P_DIRTY_AGING_IN_PROGRESS ; 
 scalar_t__ TRUE ; 
 scalar_t__ applications_aging_band ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ isApp (TYPE_1__*) ; 
 scalar_t__ isProcessInAgingBands (TYPE_1__*) ; 
 scalar_t__ isSysProc (TYPE_1__*) ; 
 scalar_t__ jetsam_aging_policy ; 
 scalar_t__ kJetsamAgingPolicyLegacy ; 
 scalar_t__ memorystatus_scheduled_idle_demotions_apps ; 
 scalar_t__ memorystatus_scheduled_idle_demotions_sysprocs ; 
 scalar_t__ system_procs_aging_band ; 

__attribute__((used)) static void
memorystatus_invalidate_idle_demotion_locked(proc_t p, boolean_t clear_state) 
{
	boolean_t present_in_sysprocs_aging_bucket = FALSE;
	boolean_t present_in_apps_aging_bucket = FALSE;

	if (!system_procs_aging_band && !applications_aging_band) {
		return;
	}

	if ((p->p_memstat_dirty & P_DIRTY_AGING_IN_PROGRESS) == 0) {
		return;
	}

	if (isProcessInAgingBands(p)) {
		
		if (jetsam_aging_policy != kJetsamAgingPolicyLegacy) {
			assert((p->p_memstat_dirty & P_DIRTY_AGING_IN_PROGRESS) == P_DIRTY_AGING_IN_PROGRESS);
		}

		if (isSysProc(p) && system_procs_aging_band) {
			assert(p->p_memstat_effectivepriority == system_procs_aging_band);
			assert(p->p_memstat_idledeadline);
			present_in_sysprocs_aging_bucket = TRUE;

		} else if (isApp(p) && applications_aging_band) {
			assert(p->p_memstat_effectivepriority == applications_aging_band);
			assert(p->p_memstat_idledeadline);
			present_in_apps_aging_bucket = TRUE;
		}
	}

	MEMORYSTATUS_DEBUG(1, "memorystatus_invalidate_idle_demotion(): invalidating demotion to idle band for pid %d (clear_state %d, demotions %d).\n", 
	    p->p_pid, clear_state, (memorystatus_scheduled_idle_demotions_sysprocs + memorystatus_scheduled_idle_demotions_apps));
    
 
	if (clear_state) {
 		p->p_memstat_idledeadline = 0;
 		p->p_memstat_dirty &= ~P_DIRTY_AGING_IN_PROGRESS;
	}
 	
 	if (isSysProc(p) &&present_in_sysprocs_aging_bucket == TRUE) {
		memorystatus_scheduled_idle_demotions_sysprocs--;
		assert(memorystatus_scheduled_idle_demotions_sysprocs >= 0);

	} else if (isApp(p) && present_in_apps_aging_bucket == TRUE) {
		memorystatus_scheduled_idle_demotions_apps--;
		assert(memorystatus_scheduled_idle_demotions_apps >= 0);
	}

 	assert((memorystatus_scheduled_idle_demotions_sysprocs + memorystatus_scheduled_idle_demotions_apps) >= 0);
}