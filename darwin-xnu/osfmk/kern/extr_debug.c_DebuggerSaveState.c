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
typedef  int /*<<< orphan*/  debugger_op ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int CPUDEBUGGERCOUNT ; 
 char const* CPUDEBUGGERMSG ; 
 int /*<<< orphan*/  CPUDEBUGGEROP ; 
 int /*<<< orphan*/  CPUDEBUGGERRET ; 
 int /*<<< orphan*/  CPUDEBUGGERSYNC ; 
 int /*<<< orphan*/ * CPUPANICARGS ; 
 unsigned long CPUPANICCALLER ; 
 void* CPUPANICDATAPTR ; 
 int /*<<< orphan*/  CPUPANICOPTS ; 
 char const* CPUPANICSTR ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  PE_kputc ; 
 int /*<<< orphan*/  _doprnt (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kprintf (char*) ; 

__attribute__((used)) static void
DebuggerSaveState(debugger_op db_op, const char *db_message, const char *db_panic_str,
		va_list *db_panic_args, uint64_t db_panic_options, void *db_panic_data_ptr,
		boolean_t db_proceed_on_sync_failure, unsigned long db_panic_caller)
{
	CPUDEBUGGEROP = db_op;

	/* Preserve the original panic message */
	if (CPUDEBUGGERCOUNT == 1 || CPUPANICSTR == NULL) {
		CPUDEBUGGERMSG = db_message;
		CPUPANICSTR = db_panic_str;
		CPUPANICARGS = db_panic_args;
		CPUPANICDATAPTR = db_panic_data_ptr;
		CPUPANICCALLER = db_panic_caller;
	} else if (CPUDEBUGGERCOUNT > 1 && db_panic_str != NULL) {
		kprintf("Nested panic detected:");
		if (db_panic_str != NULL)
			_doprnt(db_panic_str, db_panic_args, PE_kputc, 0);
	}

	CPUDEBUGGERSYNC = db_proceed_on_sync_failure;
	CPUDEBUGGERRET = KERN_SUCCESS;

	/* Reset these on any nested panics */
	CPUPANICOPTS = db_panic_options;

	return;
}