#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  TYPE_1__* proc_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_7__ {unsigned int p_memstat_dirty; int p_listflag; int p_memstat_state; int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSDDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BSD_MEMSTAT_DIRTY_TRACK ; 
 int /*<<< orphan*/  DBG_BSD_MEMSTAT ; 
 int EBUSY ; 
 int EPERM ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMORYSTATUS_DEBUG (int,char*,char*,char*,char*,int /*<<< orphan*/ ) ; 
 int PROC_DIRTY_ALLOW_IDLE_EXIT ; 
 int PROC_DIRTY_DEFER ; 
 int PROC_DIRTY_DEFER_ALWAYS ; 
 int PROC_DIRTY_LAUNCH_IN_PROGRESS ; 
 int PROC_DIRTY_TRACK ; 
 int P_DIRTY ; 
 unsigned int P_DIRTY_AGING_IN_PROGRESS ; 
 unsigned int P_DIRTY_ALLOW_IDLE_EXIT ; 
 unsigned int P_DIRTY_DEFER ; 
 unsigned int P_DIRTY_DEFER_ALWAYS ; 
 int P_DIRTY_IDLE_EXIT_ENABLED ; 
 int P_DIRTY_IS_DIRTY ; 
 unsigned int P_DIRTY_LAUNCH_IN_PROGRESS ; 
 unsigned int P_DIRTY_TRACK ; 
 int P_LIST_EXITED ; 
 int P_MEMSTAT_INTERNAL ; 
 scalar_t__ TRUE ; 
 scalar_t__ jetsam_aging_policy ; 
 scalar_t__ kJetsamAgingPolicyLegacy ; 
 int /*<<< orphan*/  memorystatus_invalidate_idle_demotion_locked (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  memorystatus_reschedule_idle_demotion_locked () ; 
 int /*<<< orphan*/  memorystatus_schedule_idle_demotion_locked (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  memorystatus_update_idle_priority_locked (TYPE_1__*) ; 
 int memorystatus_validate_track_flags (TYPE_1__*,int) ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 

int
memorystatus_dirty_track(proc_t p, uint32_t pcontrol) {
	unsigned int old_dirty;
	boolean_t reschedule = FALSE;
	boolean_t already_deferred = FALSE;
	boolean_t defer_now = FALSE;
	int ret = 0;
    
	KERNEL_DEBUG_CONSTANT(BSDDBG_CODE(DBG_BSD_MEMSTAT, BSD_MEMSTAT_DIRTY_TRACK),
		p->p_pid, p->p_memstat_dirty, pcontrol, 0, 0);
	
	proc_list_lock();
	
	if ((p->p_listflag & P_LIST_EXITED) != 0) {
		/*
		 * Process is on its way out.
		 */
		ret = EBUSY;
		goto exit;
	}

	if (p->p_memstat_state & P_MEMSTAT_INTERNAL) {
		ret = EPERM;
		goto exit;
	}
	
	if ((ret = memorystatus_validate_track_flags(p, pcontrol)) != 0) {
		/* error  */
		goto exit;
	}

        old_dirty = p->p_memstat_dirty;

	/* These bits are cumulative, as per <rdar://problem/11159924> */
	if (pcontrol & PROC_DIRTY_TRACK) {
		p->p_memstat_dirty |= P_DIRTY_TRACK;
	}

	if (pcontrol & PROC_DIRTY_ALLOW_IDLE_EXIT) {
		p->p_memstat_dirty |= P_DIRTY_ALLOW_IDLE_EXIT;					
	}

	if (pcontrol & PROC_DIRTY_LAUNCH_IN_PROGRESS) {
		p->p_memstat_dirty |= P_DIRTY_LAUNCH_IN_PROGRESS;
	}

	if (old_dirty & P_DIRTY_AGING_IN_PROGRESS) {
		already_deferred = TRUE;
	}


	/* This can be set and cleared exactly once. */
	if (pcontrol & (PROC_DIRTY_DEFER | PROC_DIRTY_DEFER_ALWAYS)) {

		if ((pcontrol & (PROC_DIRTY_DEFER)) &&
		    !(old_dirty & P_DIRTY_DEFER)) {
			p->p_memstat_dirty |= P_DIRTY_DEFER;
		}

		if ((pcontrol & (PROC_DIRTY_DEFER_ALWAYS)) &&
		    !(old_dirty & P_DIRTY_DEFER_ALWAYS)) {
			p->p_memstat_dirty |= P_DIRTY_DEFER_ALWAYS;
		}

		defer_now = TRUE;
	}

	MEMORYSTATUS_DEBUG(1, "memorystatus_on_track_dirty(): set idle-exit %s / defer %s / dirty %s for pid %d\n",
		((p->p_memstat_dirty & P_DIRTY_IDLE_EXIT_ENABLED) == P_DIRTY_IDLE_EXIT_ENABLED) ? "Y" : "N",
		defer_now ? "Y" : "N",
		p->p_memstat_dirty & P_DIRTY ? "Y" : "N",
		p->p_pid);

	/* Kick off or invalidate the idle exit deferment if there's a state transition. */
	if (!(p->p_memstat_dirty & P_DIRTY_IS_DIRTY)) {
		if ((p->p_memstat_dirty & P_DIRTY_IDLE_EXIT_ENABLED) == P_DIRTY_IDLE_EXIT_ENABLED) {

			if (defer_now && !already_deferred) {
				
				/*
				 * Request to defer a clean process that's idle-exit enabled 
				 * and not already in the jetsam deferred band. Most likely a
				 * new launch.
				 */
				memorystatus_schedule_idle_demotion_locked(p, TRUE);
				reschedule = TRUE;

			} else if (!defer_now) {

				/*
				 * The process isn't asking for the 'aging' facility.
				 * Could be that it is:
				 */

				if (already_deferred) {
					/*
					 * already in the aging bands. Traditionally,
					 * some processes have tried to use this to
					 * opt out of the 'aging' facility.
					 */
				
					memorystatus_invalidate_idle_demotion_locked(p, TRUE);
				} else {
					/*
					 * agnostic to the 'aging' facility. In that case,
					 * we'll go ahead and opt it in because this is likely
					 * a new launch (clean process, dirty tracking enabled)
					 */
				
					memorystatus_schedule_idle_demotion_locked(p, TRUE);
				}

				reschedule = TRUE;
			}
		}
	} else {

		/*
		 * We are trying to operate on a dirty process. Dirty processes have to
		 * be removed from the deferred band. The question is do we reset the 
		 * deferred state or not?
		 *
		 * This could be a legal request like:
		 * - this process had opted into the 'aging' band
		 * - but it's now dirty and requests to opt out.
		 * In this case, we remove the process from the band and reset its
		 * state too. It'll opt back in properly when needed.
		 *
		 * OR, this request could be a user-space bug. E.g.:
		 * - this process had opted into the 'aging' band when clean
		 * - and, then issues another request to again put it into the band except
		 *   this time the process is dirty.
		 * The process going dirty, as a transition in memorystatus_dirty_set(), will pull the process out of
		 * the deferred band with its state intact. So our request below is no-op.
		 * But we do it here anyways for coverage.
		 *
		 * memorystatus_update_idle_priority_locked()
		 * single-mindedly treats a dirty process as "cannot be in the aging band".
		 */

		if (!defer_now && already_deferred) {
			memorystatus_invalidate_idle_demotion_locked(p, TRUE);
			reschedule = TRUE;
		} else {

			boolean_t reset_state = (jetsam_aging_policy != kJetsamAgingPolicyLegacy) ? TRUE : FALSE;

			memorystatus_invalidate_idle_demotion_locked(p, reset_state);
			reschedule = TRUE;
		}
	}

	memorystatus_update_idle_priority_locked(p);
	
	if (reschedule) {
		memorystatus_reschedule_idle_demotion_locked();
	}
		
	ret = 0;
	
exit:		
	proc_list_unlock();
	
	return ret;
}