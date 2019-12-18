#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long uint64_t ;
typedef  int uint32_t ;
typedef  TYPE_1__* proc_t ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  scalar_t__ os_reason_t ;
typedef  int boolean_t ;
struct TYPE_13__ {scalar_t__ entry_count; } ;
struct TYPE_12__ {int p_memstat_effectivepriority; int p_memstat_state; scalar_t__ p_memstat_memlimit; int /*<<< orphan*/  task; int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int BSDDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BSD_MEMSTAT_JETSAM_HIWAT ; 
 int /*<<< orphan*/  DBG_BSD_MEMSTAT ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int FALSE ; 
 int /*<<< orphan*/  JETSAM_REASON_MEMORY_HIGHWATER ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REASON_JETSAM ; 
 scalar_t__ OS_REASON_NULL ; 
 TYPE_1__* PROC_NULL ; 
 int P_MEMSTAT_DIAG_SUSPENDED ; 
 int P_MEMSTAT_ERROR ; 
 int P_MEMSTAT_LOCKED ; 
 int P_MEMSTAT_TERMINATED ; 
 int TRUE ; 
 unsigned long long get_task_phys_footprint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kMemorystatusKilledHiwat ; 
 int kPolicyDiagnoseActive ; 
 int /*<<< orphan*/  memorystatus_available_pages ; 
 TYPE_1__* memorystatus_get_first_proc_locked (unsigned int*,int) ; 
 TYPE_1__* memorystatus_get_next_proc_locked (unsigned int*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memorystatus_init_jetsam_snapshot_locked (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int memorystatus_jetsam_policy ; 
 TYPE_7__* memorystatus_jetsam_snapshot ; 
 scalar_t__ memorystatus_jetsam_snapshot_count ; 
 int memorystatus_kill_proc (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,int*) ; 
 scalar_t__ os_reason_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_reason_free (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 
 TYPE_1__* proc_ref_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_rele (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_rele_locked (TYPE_1__*) ; 

__attribute__((used)) static boolean_t
memorystatus_kill_hiwat_proc(uint32_t *errors, boolean_t *purged)
{
	pid_t aPid = 0;
	proc_t p = PROC_NULL, next_p = PROC_NULL;
	boolean_t new_snapshot = FALSE, killed = FALSE, freed_mem = FALSE;
	unsigned int i = 0;
	uint32_t aPid_ep;
	os_reason_t jetsam_reason = OS_REASON_NULL;
	KERNEL_DEBUG_CONSTANT(BSDDBG_CODE(DBG_BSD_MEMSTAT, BSD_MEMSTAT_JETSAM_HIWAT) | DBG_FUNC_START,
		memorystatus_available_pages, 0, 0, 0, 0);
	
	jetsam_reason = os_reason_create(OS_REASON_JETSAM, JETSAM_REASON_MEMORY_HIGHWATER);
	if (jetsam_reason == OS_REASON_NULL) {
		printf("memorystatus_kill_hiwat_proc: failed to allocate exit reason\n");
	}

	proc_list_lock();
	
	next_p = memorystatus_get_first_proc_locked(&i, TRUE);
	while (next_p) {
		uint64_t footprint_in_bytes = 0;
		uint64_t memlimit_in_bytes  = 0;
		boolean_t skip = 0;

		p = next_p;
		next_p = memorystatus_get_next_proc_locked(&i, p, TRUE);
		
		aPid = p->p_pid;
		aPid_ep = p->p_memstat_effectivepriority;
		
		if (p->p_memstat_state  & (P_MEMSTAT_ERROR | P_MEMSTAT_TERMINATED)) {
			continue;
		}
		
		/* skip if no limit set */
		if (p->p_memstat_memlimit <= 0) {
			continue;
		}

		footprint_in_bytes = get_task_phys_footprint(p->task);
		memlimit_in_bytes  = (((uint64_t)p->p_memstat_memlimit) * 1024ULL * 1024ULL);	/* convert MB to bytes */
		skip = (footprint_in_bytes <= memlimit_in_bytes);

#if CONFIG_JETSAM && (DEVELOPMENT || DEBUG)
		if (!skip && (memorystatus_jetsam_policy & kPolicyDiagnoseActive)) {
			if (p->p_memstat_state & P_MEMSTAT_DIAG_SUSPENDED) {
				continue;
			}
		}
#endif /* CONFIG_JETSAM && (DEVELOPMENT || DEBUG) */

#if CONFIG_FREEZE
		if (!skip) {
			if (p->p_memstat_state & P_MEMSTAT_LOCKED) {
				skip = TRUE;
			} else {
				skip = FALSE;
			}				
		}
#endif

		if (skip) {
			continue;
		} else {

			if (memorystatus_jetsam_snapshot_count == 0) {
				memorystatus_init_jetsam_snapshot_locked(NULL,0);
				new_snapshot = TRUE;
			}
	
			if (proc_ref_locked(p) == p) {
				/*
				 * Mark as terminated so that if exit1() indicates success, but the process (for example)
				 * is blocked in task_exception_notify(), it'll be skipped if encountered again - see
				 * <rdar://problem/13553476>. This is cheaper than examining P_LEXIT, which requires the
				 * acquisition of the proc lock.
				 */
				p->p_memstat_state |= P_MEMSTAT_TERMINATED;

				proc_list_unlock();
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
		
			freed_mem = memorystatus_kill_proc(p, kMemorystatusKilledHiwat, jetsam_reason, &killed); /* purged and/or killed 'p' */

			/* Success? */
			if (freed_mem) {
				if (killed == FALSE) {
					/* purged 'p'..don't reset HWM candidate count */
					*purged = TRUE;

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
	
	KERNEL_DEBUG_CONSTANT(BSDDBG_CODE(DBG_BSD_MEMSTAT, BSD_MEMSTAT_JETSAM_HIWAT) | DBG_FUNC_END, 
			      memorystatus_available_pages, killed ? aPid : 0, 0, 0, 0);

	return killed;
}