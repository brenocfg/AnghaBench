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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ int32_t ;
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ JETSAM_PRIORITY_IDLE ; 
 scalar_t__ is_reason_thrashing (int /*<<< orphan*/ ) ; 
 scalar_t__ is_reason_zone_map_exhaustion (int /*<<< orphan*/ ) ; 
 scalar_t__ memorystatus_idle_snapshot ; 

__attribute__((used)) static boolean_t
memorystatus_post_snapshot(int32_t priority, uint32_t cause)
{
#if CONFIG_EMBEDDED
#pragma unused(cause)
	/*
	 * Don't generate logs for steady-state idle-exit kills,
	 * unless it is overridden for debug or by the device
	 * tree.
	 */

	return ((priority != JETSAM_PRIORITY_IDLE) || memorystatus_idle_snapshot);

#else /* CONFIG_EMBEDDED */
	/*
	 * Don't generate logs for steady-state idle-exit kills,
	 * unless
	 * - it is overridden for debug or by the device
	 * tree.
	 * OR
	 * - the kill causes are important i.e. not kMemorystatusKilledIdleExit
	 */

	boolean_t snapshot_eligible_kill_cause = (is_reason_thrashing(cause) || is_reason_zone_map_exhaustion(cause));
	return ((priority != JETSAM_PRIORITY_IDLE) || memorystatus_idle_snapshot || snapshot_eligible_kill_cause);
#endif /* CONFIG_EMBEDDED */
}