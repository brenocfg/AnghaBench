#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  props ;
struct TYPE_3__ {scalar_t__ user_data; int /*<<< orphan*/  priority; } ;
typedef  TYPE_1__ memorystatus_priority_properties_t ;

/* Variables and functions */
 int /*<<< orphan*/  JETSAM_PRIORITY_IDLE ; 
 int /*<<< orphan*/  MEMORYSTATUS_CMD_SET_PRIORITY_PROPERTIES ; 
 int /*<<< orphan*/  MEMSTAT_PRIORITY_CHANGE_FAILED ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getpid () ; 
 scalar_t__ memorystatus_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 

void move_to_idle_band(void) {

	memorystatus_priority_properties_t props;
	/*
	 * Freezing a process also moves it to an elevated jetsam band in order to protect it from idle exits.
	 * So we move the child process to the idle band to mirror the typical 'idle app being frozen' scenario.
	 */
	props.priority = JETSAM_PRIORITY_IDLE;
	props.user_data = 0;

	/*
	 * This requires us to run as root (in the absence of entitlement).
	 * Hence the T_META_ASROOT(true) in the T_HELPER_DECL.
	 */
	if (memorystatus_control(MEMORYSTATUS_CMD_SET_PRIORITY_PROPERTIES, getpid(), 0, &props, sizeof(props))) {
		exit(MEMSTAT_PRIORITY_CHANGE_FAILED);
	}
}