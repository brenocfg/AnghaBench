#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  TYPE_1__* proc_t ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  os_reason_t ;
typedef  scalar_t__ int32_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_14__ {scalar_t__ entry_count; } ;
struct TYPE_13__ {scalar_t__ p_memstat_effectivepriority; int p_memstat_state; int p_pid; } ;

/* Variables and functions */
 int BSDDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BSD_MEMSTAT_JETSAM ; 
 int /*<<< orphan*/  DBG_BSD_MEMSTAT ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 scalar_t__ FALSE ; 
 scalar_t__ JETSAM_PRIORITY_FOREGROUND ; 
 scalar_t__ JETSAM_PRIORITY_IDLE ; 
 scalar_t__ JETSAM_PRIORITY_MAX ; 
 int /*<<< orphan*/  JETSAM_SORT_DEFAULT ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* PROC_NULL ; 
 int P_MEMSTAT_DIAG_SUSPENDED ; 
 int P_MEMSTAT_ERROR ; 
 int P_MEMSTAT_LOCKED ; 
 int P_MEMSTAT_TERMINATED ; 
 scalar_t__ TRUE ; 
 TYPE_1__* current_proc () ; 
 scalar_t__ kMemorystatusKilledVnodes ; 
 scalar_t__ kMemorystatusKilledZoneMapExhaustion ; 
 int kPolicyDiagnoseActive ; 
 scalar_t__ max_kill_priority ; 
 int /*<<< orphan*/  memorystatus_available_pages ; 
 TYPE_1__* memorystatus_get_first_proc_locked (unsigned int*,scalar_t__) ; 
 TYPE_1__* memorystatus_get_next_proc_locked (unsigned int*,TYPE_1__*,scalar_t__) ; 
 scalar_t__ memorystatus_idle_snapshot ; 
 int /*<<< orphan*/  memorystatus_init_jetsam_snapshot_locked (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int memorystatus_jetsam_policy ; 
 TYPE_7__* memorystatus_jetsam_snapshot ; 
 scalar_t__ memorystatus_jetsam_snapshot_count ; 
 scalar_t__ memorystatus_kill_proc (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  memorystatus_sort_bucket (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_reason_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 
 TYPE_1__* proc_ref_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_rele (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_rele_locked (TYPE_1__*) ; 

__attribute__((used)) static boolean_t
memorystatus_kill_top_process(boolean_t any, boolean_t sort_flag, uint32_t cause, os_reason_t jetsam_reason,
			      int32_t *priority, uint32_t *errors)
{
	pid_t aPid;
	proc_t p = PROC_NULL, next_p = PROC_NULL;
	boolean_t new_snapshot = FALSE, force_new_snapshot = FALSE, killed = FALSE, freed_mem = FALSE;
	unsigned int i = 0;
	uint32_t aPid_ep;
	int32_t		local_max_kill_prio = JETSAM_PRIORITY_IDLE;

#ifndef CONFIG_FREEZE
#pragma unused(any)
#endif
	
	KERNEL_DEBUG_CONSTANT(BSDDBG_CODE(DBG_BSD_MEMSTAT, BSD_MEMSTAT_JETSAM) | DBG_FUNC_START,
		memorystatus_available_pages, 0, 0, 0, 0);


#if CONFIG_JETSAM
	if (sort_flag == TRUE) {
		(void)memorystatus_sort_bucket(JETSAM_PRIORITY_FOREGROUND, JETSAM_SORT_DEFAULT);
	}

	local_max_kill_prio = max_kill_priority;

	force_new_snapshot = FALSE;

#else /* CONFIG_JETSAM */

	if (sort_flag == TRUE) {
		(void)memorystatus_sort_bucket(JETSAM_PRIORITY_IDLE, JETSAM_SORT_DEFAULT);
	}

	/*
	 * On macos, we currently only have 2 reasons to be here:
	 *
	 * kMemorystatusKilledZoneMapExhaustion
	 * AND
	 * kMemorystatusKilledVMCompressorSpaceShortage
	 *
	 * If we are here because of kMemorystatusKilledZoneMapExhaustion, we will consider
	 * any and all processes as eligible kill candidates since we need to avoid a panic.
	 *
	 * Since this function can be called async. it is harder to toggle the max_kill_priority
	 * value before and after a call. And so we use this local variable to set the upper band
	 * on the eligible kill bands.
	 */
	if (cause == kMemorystatusKilledZoneMapExhaustion) {
		local_max_kill_prio = JETSAM_PRIORITY_MAX;
	} else {
		local_max_kill_prio = max_kill_priority;
	}

	/*
	 * And, because we are here under extreme circumstances, we force a snapshot even for
	 * IDLE kills.
	 */
	force_new_snapshot = TRUE;

#endif /* CONFIG_JETSAM */

	proc_list_lock();

	next_p = memorystatus_get_first_proc_locked(&i, TRUE);
	while (next_p && (next_p->p_memstat_effectivepriority <= local_max_kill_prio)) {
#if DEVELOPMENT || DEBUG
		int procSuspendedForDiagnosis;
#endif /* DEVELOPMENT || DEBUG */
        
		p = next_p;
		next_p = memorystatus_get_next_proc_locked(&i, p, TRUE);
		
#if DEVELOPMENT || DEBUG
		procSuspendedForDiagnosis = p->p_memstat_state & P_MEMSTAT_DIAG_SUSPENDED;
#endif /* DEVELOPMENT || DEBUG */
		
		aPid = p->p_pid;
		aPid_ep = p->p_memstat_effectivepriority;

		if (p->p_memstat_state & (P_MEMSTAT_ERROR | P_MEMSTAT_TERMINATED)) {
			continue;   /* with lock held */
		}
		    
#if CONFIG_JETSAM && (DEVELOPMENT || DEBUG)
		if ((memorystatus_jetsam_policy & kPolicyDiagnoseActive) && procSuspendedForDiagnosis) {
			printf("jetsam: continuing after ignoring proc suspended already for diagnosis - %d\n", aPid);
			continue;
		}
#endif /* CONFIG_JETSAM && (DEVELOPMENT || DEBUG) */

		if (cause == kMemorystatusKilledVnodes)
		{
			/*
			 * If the system runs out of vnodes, we systematically jetsam
			 * processes in hopes of stumbling onto a vnode gain that helps
			 * the system recover.  The process that happens to trigger
			 * this path has no known relationship to the vnode shortage.
			 * Deadlock avoidance: attempt to safeguard the caller.
			 */

			if (p == current_proc()) {
				/* do not jetsam the current process */
				continue;
			}
		}

#if CONFIG_FREEZE
		boolean_t skip;
		boolean_t reclaim_proc = !(p->p_memstat_state & P_MEMSTAT_LOCKED);
		if (any || reclaim_proc) {
			skip = FALSE;
		} else {
			skip = TRUE;
		}
			
		if (skip) {
			continue;
		} else
#endif
		{
			if (proc_ref_locked(p) == p) {
				/*
				 * Mark as terminated so that if exit1() indicates success, but the process (for example)
				 * is blocked in task_exception_notify(), it'll be skipped if encountered again - see
				 * <rdar://problem/13553476>. This is cheaper than examining P_LEXIT, which requires the
				 * acquisition of the proc lock.
				 */
				p->p_memstat_state |= P_MEMSTAT_TERMINATED;

			} else {
				/*
				 * We need to restart the search again because
				 * proc_ref_locked _can_ drop the proc_list lock
				 * and we could have lost our stored next_p via
				 * an exit() on another core.
				 */
				i = 0;
				next_p = memorystatus_get_first_proc_locked(&i, TRUE);
				continue;
			}

		        /*
		         * Capture a snapshot if none exists and:
			 * - we are forcing a new snapshot creation, either because:
			 * 	- on a particular platform we need these snapshots every time, OR
			 *	- a boot-arg/embedded device tree property has been set.
		         * - priority was not requested (this is something other than an ambient kill)
		         * - the priority was requested *and* the targeted process is not at idle priority
		         */
                	if ((memorystatus_jetsam_snapshot_count == 0) && 
			    (force_new_snapshot || memorystatus_idle_snapshot || ((!priority) || (priority && (aPid_ep != JETSAM_PRIORITY_IDLE))))) {
				memorystatus_init_jetsam_snapshot_locked(NULL,0);
                		new_snapshot = TRUE;
                	}

			proc_list_unlock();

			freed_mem = memorystatus_kill_proc(p, cause, jetsam_reason, &killed); /* purged and/or killed 'p' */
			/* Success? */
			if (freed_mem) {
				if (killed) {
					if (priority) {
						*priority = aPid_ep;
					}
				} else {
					/* purged */
					proc_list_lock();
					p->p_memstat_state &= ~P_MEMSTAT_TERMINATED;
					proc_list_unlock();
				}
				proc_rele(p);
				goto exit;
			}
		
			/*
			 * Failure - first unwind the state,
			 * then fall through to restart the search.
			 */
			proc_list_lock();
			proc_rele_locked(p);
			p->p_memstat_state &= ~P_MEMSTAT_TERMINATED;
			p->p_memstat_state |= P_MEMSTAT_ERROR;
			*errors += 1;

			i = 0;
			next_p = memorystatus_get_first_proc_locked(&i, TRUE);
		}
	}
	
	proc_list_unlock();
	
exit:
	os_reason_free(jetsam_reason);

	/* Clear snapshot if freshly captured and no target was found */
	if (new_snapshot && !killed) {
		proc_list_lock();
		memorystatus_jetsam_snapshot->entry_count = memorystatus_jetsam_snapshot_count = 0;
		proc_list_unlock();
	}
	
	KERNEL_DEBUG_CONSTANT(BSDDBG_CODE(DBG_BSD_MEMSTAT, BSD_MEMSTAT_JETSAM) | DBG_FUNC_END,
			      memorystatus_available_pages, killed ? aPid : 0, 0, 0, 0);

	return killed;
}