#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int pid_t ;
typedef  scalar_t__ os_reason_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  JETSAM_REASON_ZONE_MAP_EXHAUSTION ; 
 int /*<<< orphan*/  OS_REASON_JETSAM ; 
 scalar_t__ OS_REASON_NULL ; 
 int /*<<< orphan*/  kMemorystatusKilledZoneMapExhaustion ; 
 int /*<<< orphan*/  memorystatus_kill_process_async (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memorystatus_kill_process_sync (int,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ os_reason_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

boolean_t
memorystatus_kill_on_zone_map_exhaustion(pid_t pid) {
	boolean_t res = FALSE;
	if (pid == -1) {
		res = memorystatus_kill_process_async(-1, kMemorystatusKilledZoneMapExhaustion);
	} else {
		os_reason_t jetsam_reason = os_reason_create(OS_REASON_JETSAM, JETSAM_REASON_ZONE_MAP_EXHAUSTION);
		if (jetsam_reason == OS_REASON_NULL) {
			printf("memorystatus_kill_on_zone_map_exhaustion: failed to allocate jetsam reason\n");
		}

		res = memorystatus_kill_process_sync(pid, kMemorystatusKilledZoneMapExhaustion, jetsam_reason);
	}
	return res;
}