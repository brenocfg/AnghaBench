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
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  SInt64 ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  DBG_TRACE_STRING ; 
 int KDBG_EVENTID_MASK ; 
 scalar_t__ OSIncrementAtomic64 (int /*<<< orphan*/ *) ; 
 scalar_t__ STR_ID_MASK ; 
 int TRACEDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE_STRING_GLOBAL ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  g_curr_str_id ; 
 scalar_t__ g_str_id_signature ; 
 int /*<<< orphan*/  kernel_debug_internal (int,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,int /*<<< orphan*/ ) ; 
 scalar_t__ thread_tid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
kernel_debug_string_internal(uint32_t debugid, uint64_t str_id, void *vstr,
                             size_t str_len)
{
	/* str must be word-aligned */
	uintptr_t *str = vstr;
	size_t written = 0;
	uintptr_t thread_id;
	int i;
	uint32_t trace_debugid = TRACEDBG_CODE(DBG_TRACE_STRING,
	                                       TRACE_STRING_GLOBAL);

	thread_id = (uintptr_t)thread_tid(current_thread());

	/* if the ID is being invalidated, just emit that */
	if (str_id != 0 && str_len == 0) {
		kernel_debug_internal(trace_debugid | DBG_FUNC_START | DBG_FUNC_END,
				(uintptr_t)debugid, (uintptr_t)str_id, 0, 0, thread_id, 0);
		return str_id;
	}

	/* generate an ID, if necessary */
	if (str_id == 0) {
		str_id = OSIncrementAtomic64((SInt64 *)&g_curr_str_id);
		str_id = (str_id & STR_ID_MASK) | g_str_id_signature;
	}

	trace_debugid |= DBG_FUNC_START;
	/* string can fit in a single tracepoint */
	if (str_len <= (2 * sizeof(uintptr_t))) {
		trace_debugid |= DBG_FUNC_END;
	}

	kernel_debug_internal(trace_debugid, (uintptr_t)debugid, (uintptr_t)str_id,
			str[0], str[1], thread_id, 0);

	trace_debugid &= KDBG_EVENTID_MASK;
	i = 2;
	written += 2 * sizeof(uintptr_t);

	for (; written < str_len; i += 4, written += 4 * sizeof(uintptr_t)) {
		if ((written + (4 * sizeof(uintptr_t))) >= str_len) {
			trace_debugid |= DBG_FUNC_END;
		}
		kernel_debug_internal(trace_debugid, str[i],
		                                     str[i + 1],
		                                     str[i + 2],
		                                     str[i + 3], thread_id, 0);
	}

	return str_id;
}