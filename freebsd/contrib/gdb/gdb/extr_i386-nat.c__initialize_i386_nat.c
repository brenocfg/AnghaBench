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
 int /*<<< orphan*/  add_set_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_maintenance ; 
 int /*<<< orphan*/  maint_show_dr ; 
 int /*<<< orphan*/  maintenancelist ; 
 int /*<<< orphan*/  var_boolean ; 

void
_initialize_i386_nat (void)
{
#ifdef I386_USE_GENERIC_WATCHPOINTS
  /* A maintenance command to enable printing the internal DRi mirror
     variables.  */
  add_set_cmd ("show-debug-regs", class_maintenance,
	       var_boolean, (char *) &maint_show_dr,
	       "\
Set whether to show variables that mirror the x86 debug registers.\n\
Use \"on\" to enable, \"off\" to disable.\n\
If enabled, the debug registers values are shown when GDB inserts\n\
or removes a hardware breakpoint or watchpoint, and when the inferior\n\
triggers a breakpoint or watchpoint.", &maintenancelist);
#endif
}