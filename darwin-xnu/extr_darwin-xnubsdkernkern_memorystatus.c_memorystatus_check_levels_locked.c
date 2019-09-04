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

/* Variables and functions */

__attribute__((used)) static void
memorystatus_check_levels_locked(void) {
#if CONFIG_JETSAM
	/* Update levels */
	memorystatus_update_levels_locked(TRUE);
#else /* CONFIG_JETSAM */
	/*
	 * Nothing to do here currently since we update
	 * memorystatus_available_pages in vm_pressure_response.
	 */
#endif /* CONFIG_JETSAM */
}