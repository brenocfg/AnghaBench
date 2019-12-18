#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  TYPE_1__* proc_t ;
struct TYPE_10__ {scalar_t__ count; int /*<<< orphan*/  list; } ;
typedef  TYPE_2__ memstat_bucket_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_9__ {int p_memstat_state; size_t p_memstat_effectivepriority; scalar_t__ p_memstat_idle_start; scalar_t__ p_memstat_freeze_sharedanon_pages; scalar_t__ p_memstat_idle_delta; int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int ESRCH ; 
 scalar_t__ FALSE ; 
 size_t JETSAM_PRIORITY_IDLE ; 
 int /*<<< orphan*/  MEMORYSTATUS_DEBUG (int,char*,int /*<<< orphan*/ ) ; 
 int P_MEMSTAT_FROZEN ; 
 int P_MEMSTAT_INTERNAL ; 
 int P_MEMSTAT_REFREEZE_ELIGIBLE ; 
 int P_MEMSTAT_SUSPENDED ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 size_t applications_aging_band ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ isApp (TYPE_1__*) ; 
 scalar_t__ isSysProc (TYPE_1__*) ; 
 scalar_t__ mach_absolute_time () ; 
 int /*<<< orphan*/  memorystatus_check_levels_locked () ; 
 int /*<<< orphan*/  memorystatus_frozen_count ; 
 int /*<<< orphan*/  memorystatus_frozen_shared_mb ; 
 int /*<<< orphan*/  memorystatus_invalidate_idle_demotion_locked (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  memorystatus_list_count ; 
 int /*<<< orphan*/  memorystatus_refreeze_eligible_count ; 
 int /*<<< orphan*/  memorystatus_reschedule_idle_demotion_locked () ; 
 scalar_t__ memorystatus_scheduled_idle_demotions_apps ; 
 scalar_t__ memorystatus_scheduled_idle_demotions_sysprocs ; 
 int /*<<< orphan*/  memorystatus_suspended_count ; 
 TYPE_2__* memstat_bucket ; 
 int /*<<< orphan*/  p_memstat_list ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 
 size_t system_procs_aging_band ; 

int
memorystatus_remove(proc_t p, boolean_t locked)
{
	int ret;
	memstat_bucket_t *bucket;
	boolean_t	reschedule = FALSE;

	MEMORYSTATUS_DEBUG(1, "memorystatus_list_remove: removing pid %d\n", p->p_pid);

   	if (!locked) {
   	   	proc_list_lock();
   	}

	assert(!(p->p_memstat_state & P_MEMSTAT_INTERNAL));
	
	bucket = &memstat_bucket[p->p_memstat_effectivepriority];

	if (isSysProc(p) && system_procs_aging_band && (p->p_memstat_effectivepriority == system_procs_aging_band)) {

		assert(bucket->count == memorystatus_scheduled_idle_demotions_sysprocs);
		reschedule = TRUE;

	} else if (isApp(p) && applications_aging_band && (p->p_memstat_effectivepriority == applications_aging_band)) {

		assert(bucket->count == memorystatus_scheduled_idle_demotions_apps);
		reschedule = TRUE;
	}

	/*
	 * Record idle delta
	 */

	if (p->p_memstat_effectivepriority == JETSAM_PRIORITY_IDLE) {
		uint64_t now = mach_absolute_time();
		if (now > p->p_memstat_idle_start) {
			p->p_memstat_idle_delta = now - p->p_memstat_idle_start;
		}
	}

	TAILQ_REMOVE(&bucket->list, p, p_memstat_list);
	bucket->count--;

	memorystatus_list_count--;

	/* If awaiting demotion to the idle band, clean up */
	if (reschedule) {
		memorystatus_invalidate_idle_demotion_locked(p, TRUE);
 		memorystatus_reschedule_idle_demotion_locked();
	}

	memorystatus_check_levels_locked();

#if CONFIG_FREEZE    
	if (p->p_memstat_state & (P_MEMSTAT_FROZEN)) {

		if (p->p_memstat_state & P_MEMSTAT_REFREEZE_ELIGIBLE) {
			p->p_memstat_state &= ~P_MEMSTAT_REFREEZE_ELIGIBLE;
			memorystatus_refreeze_eligible_count--;
		}

		memorystatus_frozen_count--;
		memorystatus_frozen_shared_mb -= p->p_memstat_freeze_sharedanon_pages;
		p->p_memstat_freeze_sharedanon_pages = 0;
	}

	if (p->p_memstat_state & P_MEMSTAT_SUSPENDED) {
		memorystatus_suspended_count--;
	}
#endif

   	if (!locked) {
   	   	proc_list_unlock();
   	}

	if (p) {
		ret = 0; 
	} else {
		ret = ESRCH;
	}

	return ret;
}