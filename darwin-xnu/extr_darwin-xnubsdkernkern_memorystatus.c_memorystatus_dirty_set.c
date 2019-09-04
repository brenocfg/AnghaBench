#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  TYPE_1__* proc_t ;
typedef  int boolean_t ;
struct TYPE_13__ {int p_memstat_dirty; int p_listflag; int p_memstat_state; scalar_t__ p_memstat_idledeadline; int p_memstat_memlimit; int /*<<< orphan*/  p_memstat_effectivepriority; int /*<<< orphan*/  p_pid; int /*<<< orphan*/  task; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSDDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BSD_MEMSTAT_DIRTY_SET ; 
 int /*<<< orphan*/  CACHE_ACTIVE_LIMITS_LOCKED (TYPE_1__*,int) ; 
 int /*<<< orphan*/  CACHE_INACTIVE_LIMITS_LOCKED (TYPE_1__*,int) ; 
 int /*<<< orphan*/  DBG_BSD_MEMSTAT ; 
 int EALREADY ; 
 int EBUSY ; 
 int EINVAL ; 
 int EPERM ; 
 int FALSE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMORYSTATUS_DEBUG (int,char*,int,int,char*,int,...) ; 
 int P_DIRTY ; 
 int P_DIRTY_AGING_IN_PROGRESS ; 
 int P_DIRTY_ALLOW_IDLE_EXIT ; 
 int P_DIRTY_DEFER_ALWAYS ; 
 int P_DIRTY_IDLE_EXIT_ENABLED ; 
 int P_DIRTY_IS_DIRTY ; 
 int P_DIRTY_MARKED ; 
 int P_DIRTY_SHUTDOWN ; 
 int P_DIRTY_TERMINATED ; 
 int P_DIRTY_TRACK ; 
 int P_LIST_EXITED ; 
 int P_MEMSTAT_FATAL_MEMLIMIT ; 
 int P_MEMSTAT_INTERNAL ; 
 int /*<<< orphan*/  SIGKILL ; 
 int TRUE ; 
 scalar_t__ jetsam_aging_policy ; 
 scalar_t__ kJetsamAgingPolicyLegacy ; 
 scalar_t__ mach_absolute_time () ; 
 int /*<<< orphan*/  memorystatus_dirty_count ; 
 scalar_t__ memorystatus_highwater_enabled ; 
 int /*<<< orphan*/  memorystatus_invalidate_idle_demotion_locked (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memorystatus_reschedule_idle_demotion_locked () ; 
 int /*<<< orphan*/  memorystatus_schedule_idle_demotion_locked (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memorystatus_update_idle_priority_locked (TYPE_1__*) ; 
 int proc_jetsam_state_is_active_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 
 TYPE_1__* proc_ref_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_rele_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  psignal (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_set_phys_footprint_limit_internal (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int) ; 

int
memorystatus_dirty_set(proc_t p, boolean_t self, uint32_t pcontrol) {
	int ret;
	boolean_t kill = false;
	boolean_t reschedule = FALSE;
	boolean_t was_dirty = FALSE;
	boolean_t now_dirty = FALSE;

	MEMORYSTATUS_DEBUG(1, "memorystatus_dirty_set(): %d %d 0x%x 0x%x\n", self, p->p_pid, pcontrol, p->p_memstat_dirty);
	KERNEL_DEBUG_CONSTANT(BSDDBG_CODE(DBG_BSD_MEMSTAT, BSD_MEMSTAT_DIRTY_SET), p->p_pid, self, pcontrol, 0, 0);

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

	if (p->p_memstat_dirty & P_DIRTY_IS_DIRTY)
		was_dirty = TRUE;

	if (!(p->p_memstat_dirty & P_DIRTY_TRACK)) {
		/* Dirty tracking not enabled */
		ret = EINVAL;			
	} else if (pcontrol && (p->p_memstat_dirty & P_DIRTY_TERMINATED)) {
		/* 
		 * Process is set to be terminated and we're attempting to mark it dirty.
		 * Set for termination and marking as clean is OK - see <rdar://problem/10594349>.
		 */
		ret = EBUSY;		
	} else {
		int flag = (self == TRUE) ? P_DIRTY : P_DIRTY_SHUTDOWN;
		if (pcontrol && !(p->p_memstat_dirty & flag)) {
			/* Mark the process as having been dirtied at some point */
			p->p_memstat_dirty |= (flag | P_DIRTY_MARKED);
			memorystatus_dirty_count++;
			ret = 0;
		} else if ((pcontrol == 0) && (p->p_memstat_dirty & flag)) {
			if ((flag == P_DIRTY_SHUTDOWN) && (!(p->p_memstat_dirty & P_DIRTY))) {
				/* Clearing the dirty shutdown flag, and the process is otherwise clean - kill */
				p->p_memstat_dirty |= P_DIRTY_TERMINATED;
				kill = true;
			} else if ((flag == P_DIRTY) && (p->p_memstat_dirty & P_DIRTY_TERMINATED)) {
				/* Kill previously terminated processes if set clean */
				kill = true;						
			}
			p->p_memstat_dirty &= ~flag;
			memorystatus_dirty_count--;
			ret = 0;
		} else {
			/* Already set */
			ret = EALREADY;
		}
	}

	if (ret != 0) {
		goto exit;
	}

	if (p->p_memstat_dirty & P_DIRTY_IS_DIRTY)
		now_dirty = TRUE;

	if ((was_dirty == TRUE && now_dirty == FALSE) ||
	    (was_dirty == FALSE && now_dirty == TRUE)) {

		/* Manage idle exit deferral, if applied */
		if ((p->p_memstat_dirty & P_DIRTY_IDLE_EXIT_ENABLED) == P_DIRTY_IDLE_EXIT_ENABLED) {

			/*
			 * Legacy mode: P_DIRTY_AGING_IN_PROGRESS means the process is in the aging band OR it might be heading back
			 * there once it's clean again. For the legacy case, this only applies if it has some protection window left.
			 * P_DIRTY_DEFER: one-time protection window given at launch
			 * P_DIRTY_DEFER_ALWAYS: protection window given for every dirty->clean transition. Like non-legacy mode.
			 *
			 * Non-Legacy mode: P_DIRTY_AGING_IN_PROGRESS means the process is in the aging band. It will always stop over
			 * in that band on it's way to IDLE.
			 */

			if (p->p_memstat_dirty & P_DIRTY_IS_DIRTY) {
				/*
				 * New dirty process i.e. "was_dirty == FALSE && now_dirty == TRUE"
				 *
				 * The process will move from its aging band to its higher requested
				 * jetsam band. 
				 */
				boolean_t reset_state = (jetsam_aging_policy != kJetsamAgingPolicyLegacy) ? TRUE : FALSE;

				memorystatus_invalidate_idle_demotion_locked(p, reset_state);
				reschedule = TRUE;
			} else {

				/*
				 * Process is back from "dirty" to "clean".
				 */

				if (jetsam_aging_policy == kJetsamAgingPolicyLegacy) {
					if (((p->p_memstat_dirty & P_DIRTY_DEFER_ALWAYS) == FALSE) &&
					    (mach_absolute_time() >= p->p_memstat_idledeadline)) {
						/*
						 * The process' hasn't enrolled in the "always defer after dirty"
						 * mode and its deadline has expired. It currently
						 * does not reside in any of the aging buckets.
						 * 
						 * It's on its way to the JETSAM_PRIORITY_IDLE 
						 * bucket via memorystatus_update_idle_priority_locked()
						 * below.
						 
						 * So all we need to do is reset all the state on the
						 * process that's related to the aging bucket i.e.
						 * the AGING_IN_PROGRESS flag and the timer deadline.
						 */

						memorystatus_invalidate_idle_demotion_locked(p, TRUE);
						reschedule = TRUE;
					} else {
						/*
						 * Process enrolled in "always stop in deferral band after dirty" OR
						 * it still has some protection window left and so
						 * we just re-arm the timer without modifying any
						 * state on the process iff it still wants into that band.
						 */

						if (p->p_memstat_dirty & P_DIRTY_DEFER_ALWAYS) {
							memorystatus_schedule_idle_demotion_locked(p, TRUE);
							reschedule = TRUE;
						} else if (p->p_memstat_dirty & P_DIRTY_AGING_IN_PROGRESS) {
							memorystatus_schedule_idle_demotion_locked(p, FALSE);
							reschedule = TRUE;
						}
					}
				} else {

					memorystatus_schedule_idle_demotion_locked(p, TRUE);
					reschedule = TRUE;
				}
			}
		}

		memorystatus_update_idle_priority_locked(p);

		if (memorystatus_highwater_enabled) {
			boolean_t ledger_update_needed = TRUE;
			boolean_t use_active;
			boolean_t is_fatal;
			/* 
			 * We are in this path because this process transitioned between 
			 * dirty <--> clean state.  Update the cached memory limits.
			 */

			if (proc_jetsam_state_is_active_locked(p) == TRUE) {
				/*
				 * process is pinned in elevated band
				 * or
				 * process is dirty
				 */
				CACHE_ACTIVE_LIMITS_LOCKED(p, is_fatal);
				use_active = TRUE;
				ledger_update_needed = TRUE;
			} else {
				/*
				 * process is clean...but if it has opted into pressured-exit
				 * we don't apply the INACTIVE limit till the process has aged
				 * out and is entering the IDLE band.
				 * See memorystatus_update_priority_locked() for that.
				 */
			
				if (p->p_memstat_dirty & P_DIRTY_ALLOW_IDLE_EXIT) {
					ledger_update_needed = FALSE;
				} else {
					CACHE_INACTIVE_LIMITS_LOCKED(p, is_fatal);
					use_active = FALSE;
					ledger_update_needed = TRUE;
				}
			}

			/*
			 * Enforce the new limits by writing to the ledger.
			 *
			 * This is a hot path and holding the proc_list_lock while writing to the ledgers,
			 * (where the task lock is taken) is bad.  So, we temporarily drop the proc_list_lock.
			 * We aren't traversing the jetsam bucket list here, so we should be safe.
			 * See rdar://21394491.
			 */

			if (ledger_update_needed && proc_ref_locked(p) == p) {
				int ledger_limit;
				if (p->p_memstat_memlimit > 0) {
					ledger_limit = p->p_memstat_memlimit;
				} else {
					ledger_limit = -1;
				}
				proc_list_unlock();
				task_set_phys_footprint_limit_internal(p->task, ledger_limit, NULL, use_active, is_fatal);
				proc_list_lock();
				proc_rele_locked(p);

				MEMORYSTATUS_DEBUG(3, "memorystatus_dirty_set: new limit on pid %d (%dMB %s) priority(%d) dirty?=0x%x %s\n",
					   p->p_pid, (p->p_memstat_memlimit > 0 ? p->p_memstat_memlimit : -1),
					   (p->p_memstat_state & P_MEMSTAT_FATAL_MEMLIMIT ? "F " : "NF"), p->p_memstat_effectivepriority, p->p_memstat_dirty,
					   (p->p_memstat_dirty ? ((p->p_memstat_dirty & P_DIRTY) ? "isdirty" : "isclean") : ""));
			}

		}
	
		/* If the deferral state changed, reschedule the demotion timer */
		if (reschedule) {
			memorystatus_reschedule_idle_demotion_locked();
		}
	}

	if (kill) {
		if (proc_ref_locked(p) == p) {
			proc_list_unlock();
			psignal(p, SIGKILL);
			proc_list_lock();
			proc_rele_locked(p);
		}
	}
	
exit:
	proc_list_unlock();

	return ret;
}