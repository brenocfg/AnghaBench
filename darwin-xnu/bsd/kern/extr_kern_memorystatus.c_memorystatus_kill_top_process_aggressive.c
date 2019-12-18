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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  size_t uint32_t ;
typedef  TYPE_1__* proc_t ;
typedef  int pid_t ;
typedef  scalar_t__ os_reason_t ;
typedef  scalar_t__ int32_t ;
typedef  int clock_usec_t ;
typedef  scalar_t__ clock_sec_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_14__ {scalar_t__ entry_count; } ;
struct TYPE_13__ {int p_listflag; scalar_t__ p_memstat_effectivepriority; char* p_name; int p_pid; int p_memstat_state; } ;

/* Variables and functions */
 unsigned int AGGRESSIVE_JETSAM_LENIENT_MODE_THRESHOLD ; 
 int BSDDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BSD_MEMSTAT_JETSAM ; 
 int /*<<< orphan*/  DBG_BSD_MEMSTAT ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 scalar_t__ FALSE ; 
 scalar_t__ JETSAM_PRIORITY_FOREGROUND ; 
 scalar_t__ JETSAM_PRIORITY_IDLE ; 
 int /*<<< orphan*/  JETSAM_SORT_DEFAULT ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMORYSTATUS_DEBUG (int,char*,int,int,char*,...) ; 
 int /*<<< orphan*/  OS_REASON_JETSAM ; 
 scalar_t__ OS_REASON_NULL ; 
 TYPE_1__* PROC_NULL ; 
 int P_LIST_EXITED ; 
 int P_MEMSTAT_DIAG_SUSPENDED ; 
 int P_MEMSTAT_ERROR ; 
 int P_MEMSTAT_FOREGROUND ; 
 int P_MEMSTAT_TERMINATED ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  absolutetime_to_microtime (int /*<<< orphan*/ ,scalar_t__*,int*) ; 
 int kPolicyDiagnoseActive ; 
 int /*<<< orphan*/  mach_absolute_time () ; 
 scalar_t__ memorystatus_aggressive_jetsam_lenient ; 
 scalar_t__ memorystatus_available_pages ; 
 scalar_t__ memorystatus_do_kill (TYPE_1__*,size_t,scalar_t__) ; 
 TYPE_1__* memorystatus_get_first_proc_locked (unsigned int*,scalar_t__) ; 
 TYPE_1__* memorystatus_get_next_proc_locked (unsigned int*,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  memorystatus_init_jetsam_snapshot_locked (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int memorystatus_jetsam_policy ; 
 TYPE_7__* memorystatus_jetsam_snapshot ; 
 scalar_t__ memorystatus_jetsam_snapshot_count ; 
 int /*<<< orphan*/ * memorystatus_kill_cause_name ; 
 unsigned int memorystatus_level ; 
 int /*<<< orphan*/  memorystatus_sort_bucket (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memorystatus_update_jetsam_snapshot_entry_locked (TYPE_1__*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ os_reason_create (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  os_reason_free (scalar_t__) ; 
 int /*<<< orphan*/  os_reason_ref (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 
 TYPE_1__* proc_ref_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_rele (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_rele_locked (TYPE_1__*) ; 

__attribute__((used)) static boolean_t
memorystatus_kill_top_process_aggressive(uint32_t cause, int aggr_count,
					 int32_t priority_max, uint32_t *errors)
{
	pid_t aPid;
	proc_t p = PROC_NULL, next_p = PROC_NULL;
	boolean_t new_snapshot = FALSE, killed = FALSE;
	int kill_count = 0;
	unsigned int i = 0;
	int32_t aPid_ep = 0;
	unsigned int memorystatus_level_snapshot = 0;
	uint64_t killtime = 0;
        clock_sec_t     tv_sec;
        clock_usec_t    tv_usec;
        uint32_t        tv_msec;
	os_reason_t jetsam_reason = OS_REASON_NULL;

	KERNEL_DEBUG_CONSTANT(BSDDBG_CODE(DBG_BSD_MEMSTAT, BSD_MEMSTAT_JETSAM) | DBG_FUNC_START,
		memorystatus_available_pages, priority_max, 0, 0, 0);

	memorystatus_sort_bucket(JETSAM_PRIORITY_FOREGROUND, JETSAM_SORT_DEFAULT);

	jetsam_reason = os_reason_create(OS_REASON_JETSAM, cause);
	if (jetsam_reason == OS_REASON_NULL) {
		printf("memorystatus_kill_top_process_aggressive: failed to allocate exit reason\n");
	}

	proc_list_lock();

	next_p = memorystatus_get_first_proc_locked(&i, TRUE);
	while (next_p) {
#if DEVELOPMENT || DEBUG
		int activeProcess;
		int procSuspendedForDiagnosis;
#endif /* DEVELOPMENT || DEBUG */

		if (((next_p->p_listflag & P_LIST_EXITED) != 0) ||
		    ((unsigned int)(next_p->p_memstat_effectivepriority) != i)) {

			/*
			 * We have raced with next_p running on another core.
			 * It may be exiting or it may have moved to a different
			 * jetsam priority band.  This means we have lost our
			 * place in line while traversing the jetsam list.  We
			 * attempt to recover by rewinding to the beginning of the band
			 * we were already traversing.  By doing this, we do not guarantee
			 * that no process escapes this aggressive march, but we can make
			 * skipping an entire range of processes less likely. (PR-21069019)
			 */

			MEMORYSTATUS_DEBUG(1, "memorystatus: aggressive%d: rewinding band %d, %s(%d) moved or exiting.\n",
					   aggr_count, i, (*next_p->p_name ? next_p->p_name : "unknown"), next_p->p_pid);

			next_p = memorystatus_get_first_proc_locked(&i, TRUE);
			continue;
		}

		p = next_p;
		next_p = memorystatus_get_next_proc_locked(&i, p, TRUE);

		if (p->p_memstat_effectivepriority > priority_max) {
			/* 
			 * Bail out of this killing spree if we have
			 * reached beyond the priority_max jetsam band.
 			 * That is, we kill up to and through the 
			 * priority_max jetsam band.
			 */
			proc_list_unlock();
			goto exit;
		}
		
#if DEVELOPMENT || DEBUG
		activeProcess = p->p_memstat_state & P_MEMSTAT_FOREGROUND;
		procSuspendedForDiagnosis = p->p_memstat_state & P_MEMSTAT_DIAG_SUSPENDED;
#endif /* DEVELOPMENT || DEBUG */
		
		aPid = p->p_pid;
		aPid_ep = p->p_memstat_effectivepriority;

		if (p->p_memstat_state & (P_MEMSTAT_ERROR | P_MEMSTAT_TERMINATED)) {
			continue;
		}
		    
#if CONFIG_JETSAM && (DEVELOPMENT || DEBUG)
		if ((memorystatus_jetsam_policy & kPolicyDiagnoseActive) && procSuspendedForDiagnosis) {
			printf("jetsam: continuing after ignoring proc suspended already for diagnosis - %d\n", aPid);
			continue;
		}
#endif /* CONFIG_JETSAM && (DEVELOPMENT || DEBUG) */

		/*
		 * Capture a snapshot if none exists.
		 */
		if (memorystatus_jetsam_snapshot_count == 0) {
			memorystatus_init_jetsam_snapshot_locked(NULL,0);
			new_snapshot = TRUE;
		}
		        
		/* 
		 * Mark as terminated so that if exit1() indicates success, but the process (for example)
		 * is blocked in task_exception_notify(), it'll be skipped if encountered again - see 
		 * <rdar://problem/13553476>. This is cheaper than examining P_LEXIT, which requires the 
		 * acquisition of the proc lock.
		 */
		p->p_memstat_state |= P_MEMSTAT_TERMINATED;

		killtime = mach_absolute_time();
		absolutetime_to_microtime(killtime, &tv_sec, &tv_usec);
		tv_msec = tv_usec / 1000;
		        
		/* Shift queue, update stats */
		memorystatus_update_jetsam_snapshot_entry_locked(p, cause, killtime);

		/*
		 * In order to kill the target process, we will drop the proc_list_lock.
		 * To guaranteee that p and next_p don't disappear out from under the lock,
		 * we must take a ref on both.
		 * If we cannot get a reference, then it's likely we've raced with
		 * that process exiting on another core.
		 */
		if (proc_ref_locked(p) == p) {
			if (next_p) {
				while (next_p && (proc_ref_locked(next_p) != next_p)) {
					proc_t temp_p;

					 /*
					  * We must have raced with next_p exiting on another core.
					  * Recover by getting the next eligible process in the band.
					  */

					MEMORYSTATUS_DEBUG(1, "memorystatus: aggressive%d: skipping %d [%s] (exiting?)\n",
					       aggr_count, next_p->p_pid, (*next_p->p_name ? next_p->p_name : "(unknown)"));

					temp_p = next_p;
					next_p = memorystatus_get_next_proc_locked(&i, temp_p, TRUE);
				 }
			}
			proc_list_unlock();

			printf("%lu.%03d memorystatus: %s%d pid %d [%s] (%s %d) - memorystatus_available_pages: %llu\n",
			       (unsigned long)tv_sec, tv_msec,
			       ((aPid_ep == JETSAM_PRIORITY_IDLE) ? "killing_idle_process_aggressive" : "killing_top_process_aggressive"),
			       aggr_count, aPid, (*p->p_name ? p->p_name : "unknown"),
			       memorystatus_kill_cause_name[cause], aPid_ep, (uint64_t)memorystatus_available_pages);

			memorystatus_level_snapshot = memorystatus_level;

			/*
			 * memorystatus_do_kill() drops a reference, so take another one so we can
			 * continue to use this exit reason even after memorystatus_do_kill()
			 * returns.
			 */
			os_reason_ref(jetsam_reason);
			killed = memorystatus_do_kill(p, cause, jetsam_reason);

			/* Success? */
			if (killed) {
				proc_rele(p);
				kill_count++;
				p = NULL;
				killed = FALSE;

				/* 
				 * Continue the killing spree.
				 */
				proc_list_lock();
				if (next_p) {
					proc_rele_locked(next_p);
				}

				if (aPid_ep == JETSAM_PRIORITY_FOREGROUND && memorystatus_aggressive_jetsam_lenient == TRUE) {
					if (memorystatus_level > memorystatus_level_snapshot && ((memorystatus_level - memorystatus_level_snapshot) >= AGGRESSIVE_JETSAM_LENIENT_MODE_THRESHOLD)) {
#if DEVELOPMENT || DEBUG
						printf("Disabling Lenient mode after one-time deployment.\n");
#endif /* DEVELOPMENT || DEBUG */
						memorystatus_aggressive_jetsam_lenient = FALSE;
						break;
					}
				}

				continue;
			}
					
			/*
			 * Failure - first unwind the state,
			 * then fall through to restart the search.
			 */
			proc_list_lock();
			proc_rele_locked(p);
			if (next_p) {
				proc_rele_locked(next_p);
			}
			p->p_memstat_state &= ~P_MEMSTAT_TERMINATED;
			p->p_memstat_state |= P_MEMSTAT_ERROR;
			*errors += 1;
			p = NULL;
		}

		/*
		 * Failure - restart the search at the beginning of
		 * the band we were already traversing.
		 *
		 * We might have raced with "p" exiting on another core, resulting in no
		 * ref on "p".  Or, we may have failed to kill "p".
		 *
		 * Either way, we fall thru to here, leaving the proc in the 
		 * P_MEMSTAT_TERMINATED or P_MEMSTAT_ERROR state.
		 *
		 * And, we hold the the proc_list_lock at this point.
		 */

		next_p = memorystatus_get_first_proc_locked(&i, TRUE);
	}
	
	proc_list_unlock();
	
exit:
	os_reason_free(jetsam_reason);

	/* Clear snapshot if freshly captured and no target was found */
	if (new_snapshot && (kill_count == 0)) {
	    proc_list_lock();
	    memorystatus_jetsam_snapshot->entry_count = memorystatus_jetsam_snapshot_count = 0;
	    proc_list_unlock();
	}
	
	KERNEL_DEBUG_CONSTANT(BSDDBG_CODE(DBG_BSD_MEMSTAT, BSD_MEMSTAT_JETSAM) | DBG_FUNC_END,
			      memorystatus_available_pages, killed ? aPid : 0, kill_count, 0, 0);

	if (kill_count > 0) {
		return(TRUE);
	}
	else {
		return(FALSE);
	}
}