#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  TYPE_1__* proc_t ;
typedef  scalar_t__ os_reason_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_10__ {scalar_t__ p_memstat_effectivepriority; int p_memstat_dirty; scalar_t__ p_memstat_idledeadline; int p_pid; char* p_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ JETSAM_PRIORITY_IDLE ; 
 int /*<<< orphan*/  JETSAM_REASON_MEMORY_IDLE_EXIT ; 
 int /*<<< orphan*/  OS_REASON_JETSAM ; 
 scalar_t__ OS_REASON_NULL ; 
 TYPE_1__* PROC_NULL ; 
 int P_DIRTY_ALLOW_IDLE_EXIT ; 
 int P_DIRTY_IS_DIRTY ; 
 int P_DIRTY_TERMINATED ; 
 int /*<<< orphan*/  kMemorystatusKilledIdleExit ; 
 scalar_t__ mach_absolute_time () ; 
 int /*<<< orphan*/  memorystatus_do_kill (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* memorystatus_get_first_proc_locked (unsigned int*,int /*<<< orphan*/ ) ; 
 TYPE_1__* memorystatus_get_next_proc_locked (unsigned int*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ os_reason_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_reason_free (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 
 TYPE_1__* proc_ref_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_rele (TYPE_1__*) ; 

__attribute__((used)) static boolean_t
kill_idle_exit_proc(void)
{
	proc_t p, victim_p = PROC_NULL;
	uint64_t current_time;
	boolean_t killed = FALSE;
	unsigned int i = 0;
	os_reason_t jetsam_reason = OS_REASON_NULL;

	/* Pick next idle exit victim. */
	current_time = mach_absolute_time();
	
	jetsam_reason = os_reason_create(OS_REASON_JETSAM, JETSAM_REASON_MEMORY_IDLE_EXIT);
	if (jetsam_reason == OS_REASON_NULL) {
		printf("kill_idle_exit_proc: failed to allocate jetsam reason\n");
	}

	proc_list_lock();
	
	p = memorystatus_get_first_proc_locked(&i, FALSE);
	while (p) {
		/* No need to look beyond the idle band */
		if (p->p_memstat_effectivepriority != JETSAM_PRIORITY_IDLE) {
			break;
		}
		
		if ((p->p_memstat_dirty & (P_DIRTY_ALLOW_IDLE_EXIT|P_DIRTY_IS_DIRTY|P_DIRTY_TERMINATED)) == (P_DIRTY_ALLOW_IDLE_EXIT)) {				
			if (current_time >= p->p_memstat_idledeadline) {
				p->p_memstat_dirty |= P_DIRTY_TERMINATED;
				victim_p = proc_ref_locked(p);
				break;
			}
		}
		
		p = memorystatus_get_next_proc_locked(&i, p, FALSE);
	}
	
	proc_list_unlock();
	
	if (victim_p) {
		printf("memorystatus: killing_idle_process pid %d [%s]\n", victim_p->p_pid, (*victim_p->p_name ? victim_p->p_name : "unknown"));
		killed = memorystatus_do_kill(victim_p, kMemorystatusKilledIdleExit, jetsam_reason);
		proc_rele(victim_p);
	} else {
		os_reason_free(jetsam_reason);
	}

	return killed;
}