#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  snapshot_size ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  os_reason_t ;
typedef  int /*<<< orphan*/  memorystatus_jetsam_snapshot_t ;
typedef  int /*<<< orphan*/  memorystatus_jetsam_snapshot_entry_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_2__ {scalar_t__ notification_time; } ;

/* Variables and functions */
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  kMemorystatusSnapshotNote ; 
 scalar_t__ mach_absolute_time () ; 
 int /*<<< orphan*/  memorystatus_clear_errors () ; 
 TYPE_1__* memorystatus_jetsam_snapshot ; 
 int memorystatus_jetsam_snapshot_count ; 
 scalar_t__ memorystatus_jetsam_snapshot_last_timestamp ; 
 scalar_t__ memorystatus_jetsam_snapshot_timeout ; 
 scalar_t__ memorystatus_kill_specific_process (int,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ memorystatus_kill_top_process (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int memorystatus_send_note (int /*<<< orphan*/ ,size_t*,int) ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 

__attribute__((used)) static boolean_t 
memorystatus_kill_process_sync(pid_t victim_pid, uint32_t cause, os_reason_t jetsam_reason) {
	boolean_t res;

	uint32_t errors = 0;

	if (victim_pid == -1) {
		/* No pid, so kill first process */
		res = memorystatus_kill_top_process(TRUE, TRUE, cause, jetsam_reason, NULL, &errors);
	} else {
		res = memorystatus_kill_specific_process(victim_pid, cause, jetsam_reason);
	}
	
	if (errors) {
		memorystatus_clear_errors();
	}

	if (res == TRUE) {
		/* Fire off snapshot notification */
		proc_list_lock();
		size_t snapshot_size = sizeof(memorystatus_jetsam_snapshot_t) + 
			sizeof(memorystatus_jetsam_snapshot_entry_t) * memorystatus_jetsam_snapshot_count;
		uint64_t timestamp_now = mach_absolute_time();
		memorystatus_jetsam_snapshot->notification_time = timestamp_now;
		if (memorystatus_jetsam_snapshot_count > 0 && (memorystatus_jetsam_snapshot_last_timestamp == 0 ||
				timestamp_now > memorystatus_jetsam_snapshot_last_timestamp + memorystatus_jetsam_snapshot_timeout)) {
			proc_list_unlock();
			int ret = memorystatus_send_note(kMemorystatusSnapshotNote, &snapshot_size, sizeof(snapshot_size));
			if (!ret) {
				proc_list_lock();
				memorystatus_jetsam_snapshot_last_timestamp = timestamp_now;
				proc_list_unlock();
			}
		} else {
			proc_list_unlock();
		}
	}

	return res;
}