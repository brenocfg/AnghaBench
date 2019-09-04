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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  debugger_op ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPUDEBUGGERRET ; 
 int /*<<< orphan*/  DBOP_NONE ; 
 int /*<<< orphan*/  DebuggerSaveState (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,scalar_t__,unsigned long) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  TRAP_DEBUGGER ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ml_get_interrupts_enabled () ; 

kern_return_t
DebuggerTrapWithState(debugger_op db_op, const char *db_message, const char *db_panic_str,
		va_list *db_panic_args, uint64_t db_panic_options, void *db_panic_data_ptr,
		boolean_t db_proceed_on_sync_failure, unsigned long db_panic_caller)
{
	kern_return_t ret;

	assert(ml_get_interrupts_enabled() == FALSE);
	DebuggerSaveState(db_op, db_message, db_panic_str, db_panic_args,
				db_panic_options, db_panic_data_ptr,
				db_proceed_on_sync_failure, db_panic_caller);

	TRAP_DEBUGGER;

	ret = CPUDEBUGGERRET;

	DebuggerSaveState(DBOP_NONE, NULL, NULL, NULL, 0, NULL, FALSE, 0);

	return ret;
}