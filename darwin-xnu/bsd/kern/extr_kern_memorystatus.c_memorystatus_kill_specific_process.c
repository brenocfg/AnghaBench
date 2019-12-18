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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  size_t uint32_t ;
typedef  TYPE_1__* proc_t ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  os_reason_t ;
typedef  int clock_usec_t ;
typedef  scalar_t__ clock_sec_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_6__ {char* p_name; int /*<<< orphan*/  p_memstat_effectivepriority; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  OS_LOG_DEFAULT ; 
 int /*<<< orphan*/  absolutetime_to_microtime (int /*<<< orphan*/ ,scalar_t__*,int*) ; 
 int /*<<< orphan*/  mach_absolute_time () ; 
 scalar_t__ memorystatus_available_pages ; 
 int /*<<< orphan*/  memorystatus_do_kill (TYPE_1__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memorystatus_init_jetsam_snapshot_locked (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ memorystatus_jetsam_snapshot_count ; 
 int /*<<< orphan*/ * memorystatus_kill_cause_name ; 
 int /*<<< orphan*/  memorystatus_update_jetsam_snapshot_entry_locked (TYPE_1__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_log_with_startup_serial (int /*<<< orphan*/ ,char*,unsigned long,size_t,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_reason_free (int /*<<< orphan*/ ) ; 
 TYPE_1__* proc_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 
 int /*<<< orphan*/  proc_rele (TYPE_1__*) ; 

__attribute__((used)) static boolean_t 
memorystatus_kill_specific_process(pid_t victim_pid, uint32_t cause, os_reason_t jetsam_reason) {
	boolean_t killed;
	proc_t p;
	uint64_t killtime = 0;
        clock_sec_t     tv_sec;
        clock_usec_t    tv_usec;
        uint32_t        tv_msec;

	/* TODO - add a victim queue and push this into the main jetsam thread */

	p = proc_find(victim_pid);
	if (!p) {
		os_reason_free(jetsam_reason);
		return FALSE;
	}

	proc_list_lock();

	if (memorystatus_jetsam_snapshot_count == 0) {
		memorystatus_init_jetsam_snapshot_locked(NULL,0);
	}

	killtime = mach_absolute_time();
        absolutetime_to_microtime(killtime, &tv_sec, &tv_usec);
        tv_msec = tv_usec / 1000;

	memorystatus_update_jetsam_snapshot_entry_locked(p, cause, killtime);

	proc_list_unlock();

	os_log_with_startup_serial(OS_LOG_DEFAULT, "%lu.%03d memorystatus: killing_specific_process pid %d [%s] (%s %d) - memorystatus_available_pages: %llu\n",
	       (unsigned long)tv_sec, tv_msec, victim_pid, (*p->p_name ? p->p_name : "unknown"),
	       memorystatus_kill_cause_name[cause], p->p_memstat_effectivepriority, (uint64_t)memorystatus_available_pages);
	
	killed = memorystatus_do_kill(p, cause, jetsam_reason);
	proc_rele(p);
	
	return killed;
}