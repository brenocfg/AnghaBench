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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_2__ {int kdebug_flags; } ;

/* Variables and functions */
 scalar_t__ DBG_TRACE ; 
 int /*<<< orphan*/  FALSE ; 
 int KDBG_EVENTID_MASK ; 
 scalar_t__ KDBG_EXTRACT_CLASS (int) ; 
 int KDBG_RANGECHECK ; 
 int KDBG_TYPEFILTER_CHECK ; 
 int KDBG_VALCHECK ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__ kd_ctrl_page ; 
 int /*<<< orphan*/  kdbg_typefilter ; 
 int kdlog_beg ; 
 int kdlog_end ; 
 int kdlog_value1 ; 
 int kdlog_value2 ; 
 int kdlog_value3 ; 
 int kdlog_value4 ; 
 int /*<<< orphan*/  typefilter_is_debugid_allowed (int /*<<< orphan*/ ,int) ; 

boolean_t
kdebug_debugid_explicitly_enabled(uint32_t debugid)
{
	if (kd_ctrl_page.kdebug_flags & KDBG_TYPEFILTER_CHECK) {
		return typefilter_is_debugid_allowed(kdbg_typefilter, debugid);
	} else if (KDBG_EXTRACT_CLASS(debugid) == DBG_TRACE) {
		return TRUE;
	} else if (kd_ctrl_page.kdebug_flags & KDBG_RANGECHECK) {
		if (debugid < kdlog_beg || debugid > kdlog_end) {
			return FALSE;
		}
	} else if (kd_ctrl_page.kdebug_flags & KDBG_VALCHECK) {
		if ((debugid & KDBG_EVENTID_MASK) != kdlog_value1 &&
			(debugid & KDBG_EVENTID_MASK) != kdlog_value2 &&
			(debugid & KDBG_EVENTID_MASK) != kdlog_value3 &&
			(debugid & KDBG_EVENTID_MASK) != kdlog_value4)
		{
			return FALSE;
		}
	}

	return TRUE;
}