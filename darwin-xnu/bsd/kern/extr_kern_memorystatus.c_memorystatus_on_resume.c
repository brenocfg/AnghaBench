#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* proc_t ;
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_6__ {int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ memorystatus_freeze_entry_t ;
typedef  int /*<<< orphan*/  data ;
typedef  int boolean_t ;
struct TYPE_5__ {int p_memstat_state; int /*<<< orphan*/  p_pid; int /*<<< orphan*/  p_memstat_thaw_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int P_MEMSTAT_FROZEN ; 
 int P_MEMSTAT_REFREEZE_ELIGIBLE ; 
 int P_MEMSTAT_SUSPENDED ; 
 int /*<<< orphan*/  kMemorystatusFreezeNote ; 
 int /*<<< orphan*/  memorystatus_refreeze_eligible_count ; 
 int /*<<< orphan*/  memorystatus_send_note (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memorystatus_suspended_count ; 
 int /*<<< orphan*/  memorystatus_thaw_count ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 

void
memorystatus_on_resume(proc_t p)
{
#if CONFIG_FREEZE
	boolean_t frozen;
	pid_t pid;
#endif

	proc_list_lock();

#if CONFIG_FREEZE
	frozen = (p->p_memstat_state & P_MEMSTAT_FROZEN);
	if (frozen) {
		/*
		 * Now that we don't _thaw_ a process completely,
		 * resuming it (and having some on-demand swapins)
		 * shouldn't preclude it from being counted as frozen.
		 *
		 * memorystatus_frozen_count--;
		 *
		 * We preserve the P_MEMSTAT_FROZEN state since the process
		 * could have state on disk AND so will deserve some protection
		 * in the jetsam bands.
		 */
		if ((p->p_memstat_state & P_MEMSTAT_REFREEZE_ELIGIBLE) == 0) {
			p->p_memstat_state |= P_MEMSTAT_REFREEZE_ELIGIBLE;
			memorystatus_refreeze_eligible_count++;
		}
		p->p_memstat_thaw_count++;

		memorystatus_thaw_count++;
	}

	memorystatus_suspended_count--;
	
	pid = p->p_pid;
#endif

	/*
	 * P_MEMSTAT_FROZEN will remain unchanged. This used to be:
	 * p->p_memstat_state &= ~(P_MEMSTAT_SUSPENDED | P_MEMSTAT_FROZEN);
	 */
	p->p_memstat_state &= ~P_MEMSTAT_SUSPENDED;

	proc_list_unlock();
    
#if CONFIG_FREEZE
	if (frozen) {
		memorystatus_freeze_entry_t data = { pid, FALSE, 0 };
		memorystatus_send_note(kMemorystatusFreezeNote, &data, sizeof(data));
	}
#endif
}