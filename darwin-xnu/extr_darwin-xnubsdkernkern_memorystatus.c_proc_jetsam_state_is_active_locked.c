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
typedef  TYPE_1__* proc_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_3__ {int p_memstat_state; scalar_t__ p_memstat_effectivepriority; int p_memstat_dirty; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ JETSAM_PRIORITY_ELEVATED_INACTIVE ; 
 scalar_t__ JETSAM_PRIORITY_FOREGROUND ; 
 int P_DIRTY_IS_DIRTY ; 
 int P_DIRTY_TRACK ; 
 int P_MEMSTAT_USE_ELEVATED_INACTIVE_BAND ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static boolean_t
proc_jetsam_state_is_active_locked(proc_t p) {

	if ((p->p_memstat_state & P_MEMSTAT_USE_ELEVATED_INACTIVE_BAND) &&
	    (p->p_memstat_effectivepriority == JETSAM_PRIORITY_ELEVATED_INACTIVE)) {
		/*
		 * process has the 'elevated inactive jetsam band' attribute
		 * and process is present in the elevated band
		 * implies active state
		 */
		return TRUE;
	} else if (p->p_memstat_dirty & P_DIRTY_TRACK) {
		/*
		 * process has opted into dirty tracking
		 * active state is based on dirty vs. clean
		 */
		if (p->p_memstat_dirty & P_DIRTY_IS_DIRTY) {
			/*
			 * process is dirty
			 * implies active state
			 */
			return TRUE;
		} else {
			/*
			 * process is clean
			 * implies inactive state
			 */
			return FALSE;
		}
	} else if (p->p_memstat_effectivepriority >= JETSAM_PRIORITY_FOREGROUND) {
		/*
		 * process is Foreground or higher
		 * implies active state
		 */
		return TRUE;
	} else {
		/*
		 * process found below Foreground
		 * implies inactive state
		 */
		return FALSE;
	}
}