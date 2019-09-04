#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  TYPE_1__* proc_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_5__ {int kdebug_flags; } ;
struct TYPE_4__ {scalar_t__ p_kdebug; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_MACH_SCHED ; 
 scalar_t__ DBG_TRACE ; 
 int /*<<< orphan*/  FALSE ; 
 int KDBG_CSC_MASK ; 
 scalar_t__ KDBG_EXTRACT_CLASS (int) ; 
 int KDBG_PIDCHECK ; 
 int KDBG_PIDEXCLUDE ; 
 int MACHDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* current_proc () ; 
 TYPE_2__ kd_ctrl_page ; 
 scalar_t__ ml_at_interrupt_context () ; 

__attribute__((used)) static boolean_t
kdebug_current_proc_enabled(uint32_t debugid)
{
	/* can't determine current process in interrupt context */
	if (ml_at_interrupt_context()) {
		return TRUE;
	}

	/* always emit trace system and scheduling events */
	if ((KDBG_EXTRACT_CLASS(debugid) == DBG_TRACE ||
	    (debugid & KDBG_CSC_MASK) == MACHDBG_CODE(DBG_MACH_SCHED, 0)))
	{
		return TRUE;
	}

	if (kd_ctrl_page.kdebug_flags & KDBG_PIDCHECK) {
		proc_t cur_proc = current_proc();

		/* only the process with the kdebug bit set is allowed */
		if (cur_proc && !(cur_proc->p_kdebug)) {
			return FALSE;
		}
	} else if (kd_ctrl_page.kdebug_flags & KDBG_PIDEXCLUDE) {
		proc_t cur_proc = current_proc();

		/* every process except the one with the kdebug bit set is allowed */
		if (cur_proc && cur_proc->p_kdebug) {
			return FALSE;
		}
	}

	return TRUE;
}