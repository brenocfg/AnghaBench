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
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ is_reason_thrashing (int /*<<< orphan*/ ) ; 
 scalar_t__ is_reason_zone_map_exhaustion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_under_pressure_cause ; 
 scalar_t__ memorystatus_available_pages ; 
 scalar_t__ memorystatus_available_pages_pressure ; 

__attribute__((used)) static boolean_t
memorystatus_action_needed(void)
{
#if CONFIG_EMBEDDED
	return (is_reason_thrashing(kill_under_pressure_cause) ||
			is_reason_zone_map_exhaustion(kill_under_pressure_cause) ||
	       memorystatus_available_pages <= memorystatus_available_pages_pressure);
#else /* CONFIG_EMBEDDED */
	return (is_reason_thrashing(kill_under_pressure_cause) ||
			is_reason_zone_map_exhaustion(kill_under_pressure_cause));
#endif /* CONFIG_EMBEDDED */
}