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
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  os_reason_t ;
typedef  int clock_usec_t ;
typedef  scalar_t__ clock_sec_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_14__ {scalar_t__ entry_count; } ;
struct TYPE_13__ {size_t p_memstat_effectivepriority; int p_memstat_state; char* p_name; int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int BSDDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BSD_MEMSTAT_JETSAM ; 
 int /*<<< orphan*/  DBG_BSD_MEMSTAT ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMORYSTATUS_DEBUG (int,char*,int,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  OS_LOG_DEFAULT ; 
 TYPE_1__* PROC_NULL ; 
 int P_MEMSTAT_ERROR ; 
 int P_MEMSTAT_FROZEN ; 
 int P_MEMSTAT_LOCKED ; 
 int P_MEMSTAT_TERMINATED ; 
 int P_MEMSTAT_USE_ELEVATED_INACTIVE_BAND ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  absolutetime_to_microtime (int /*<<< orphan*/ ,scalar_t__*,int*) ; 
 int /*<<< orphan*/  mach_absolute_time () ; 
 scalar_t__ memorystatus_available_pages ; 
 scalar_t__ memorystatus_do_kill (TYPE_1__*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ memorystatus_freeze_jetsam_band ; 
 TYPE_1__* memorystatus_get_first_proc_locked (unsigned int*,scalar_t__) ; 
 TYPE_1__* memorystatus_get_next_proc_locked (unsigned int*,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  memorystatus_init_jetsam_snapshot_locked (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_7__* memorystatus_jetsam_snapshot ; 
 scalar_t__ memorystatus_jetsam_snapshot_count ; 
 int /*<<< orphan*/ * memorystatus_kill_cause_name ; 
 int /*<<< orphan*/  memorystatus_update_jetsam_snapshot_entry_locked (TYPE_1__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_log_with_startup_serial (int /*<<< orphan*/ ,char*,unsigned long,size_t,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_reason_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_reason_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 
 TYPE_1__* proc_ref_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_rele (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_rele_locked (TYPE_1__*) ; 

__attribute__((used)) static boolean_t
memorystatus_kill_elevated_process(uint32_t cause, os_reason_t jetsam_reason, unsigned int band, int aggr_count, uint32_t *errors)
{
	pid_t aPid = 0;
	proc_t p = PROC_NULL, next_p = PROC_NULL;
	boolean_t new_snapshot = FALSE, killed = FALSE;
	int kill_count = 0;
	uint32_t aPid_ep;
	uint64_t killtime = 0;
        clock_sec_t     tv_sec;
        clock_usec_t    tv_usec;
        uint32_t        tv_msec;


	KERNEL_DEBUG_CONSTANT(BSDDBG_CODE(DBG_BSD_MEMSTAT, BSD_MEMSTAT_JETSAM) | DBG_FUNC_START,
		memorystatus_available_pages, 0, 0, 0, 0);

#if CONFIG_FREEZE
	boolean_t consider_frozen_only = FALSE;

	if (band == (unsigned int) memorystatus_freeze_jetsam_band) {
		consider_frozen_only = TRUE;
	}
#endif /* CONFIG_FREEZE */

	proc_list_lock();

	next_p = memorystatus_get_first_proc_locked(&band, FALSE);
	while (next_p) {

		p = next_p;
		next_p = memorystatus_get_next_proc_locked(&band, p, FALSE);

		aPid = p->p_pid;
		aPid_ep = p->p_memstat_effectivepriority;

		/*
		 * Only pick a process pinned in this elevated band
		 */
		if (!(p->p_memstat_state & P_MEMSTAT_USE_ELEVATED_INACTIVE_BAND)) {
			continue;
		}

		if (p->p_memstat_state  & (P_MEMSTAT_ERROR | P_MEMSTAT_TERMINATED)) {
			continue;
		}

#if CONFIG_FREEZE
		if (consider_frozen_only && ! (p->p_memstat_state & P_MEMSTAT_FROZEN)) {
			continue;
		}

		if (p->p_memstat_state & P_MEMSTAT_LOCKED) {
			continue;
		}
#endif /* CONFIG_FREEZE */

#if DEVELOPMENT || DEBUG
		MEMORYSTATUS_DEBUG(1, "jetsam: elevated%d process pid %d [%s] - memorystatus_available_pages: %d\n",
				   aggr_count,
				   aPid, (*p->p_name ? p->p_name : "unknown"),
				   memorystatus_available_pages);
#endif /* DEVELOPMENT || DEBUG */

		if (memorystatus_jetsam_snapshot_count == 0) {
			memorystatus_init_jetsam_snapshot_locked(NULL,0);
			new_snapshot = TRUE;
		}

		p->p_memstat_state |= P_MEMSTAT_TERMINATED;

		killtime = mach_absolute_time();
		absolutetime_to_microtime(killtime, &tv_sec, &tv_usec);
		tv_msec = tv_usec / 1000;

		memorystatus_update_jetsam_snapshot_entry_locked(p, cause, killtime);

		if (proc_ref_locked(p) == p) {

			proc_list_unlock();

                        os_log_with_startup_serial(OS_LOG_DEFAULT, "%lu.%03d memorystatus: killing_top_process_elevated%d pid %d [%s] (%s %d) - memorystatus_available_pages: %llu\n",
                               (unsigned long)tv_sec, tv_msec,
			       aggr_count,
                               aPid, (*p->p_name ? p->p_name : "unknown"),
                               memorystatus_kill_cause_name[cause], aPid_ep, (uint64_t)memorystatus_available_pages);

			/*
			 * memorystatus_do_kill drops a reference, so take another one so we can
			 * continue to use this exit reason even after memorystatus_do_kill()
			 * returns
			 */
			os_reason_ref(jetsam_reason);
			killed = memorystatus_do_kill(p, cause, jetsam_reason);

			/* Success? */
			if (killed) {
				proc_rele(p);
				kill_count++;
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
		}

		/*
		 * Failure - restart the search.
		 *
		 * We might have raced with "p" exiting on another core, resulting in no
		 * ref on "p".  Or, we may have failed to kill "p".
		 *
		 * Either way, we fall thru to here, leaving the proc in the
		 * P_MEMSTAT_TERMINATED state or P_MEMSTAT_ERROR state.
		 *
		 * And, we hold the the proc_list_lock at this point.
		 */

		next_p = memorystatus_get_first_proc_locked(&band, FALSE);
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

	return (killed);
}