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
 int /*<<< orphan*/  DEPRECATED_REGISTER_GDBARCH_SWAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_com (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  build_regcache ; 
 int /*<<< orphan*/  class_maintenance ; 
 int /*<<< orphan*/  current_regcache ; 
 int /*<<< orphan*/  deprecated_register_gdbarch_swap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deprecated_register_valid ; 
 int /*<<< orphan*/  deprecated_registers ; 
 int /*<<< orphan*/  init_regcache_descr ; 
 int /*<<< orphan*/  maintenance_print_cooked_registers ; 
 int /*<<< orphan*/  maintenance_print_raw_registers ; 
 int /*<<< orphan*/  maintenance_print_register_groups ; 
 int /*<<< orphan*/  maintenance_print_registers ; 
 int /*<<< orphan*/  maintenanceprintlist ; 
 int /*<<< orphan*/  pid_to_ptid (int) ; 
 int /*<<< orphan*/  reg_flush_command ; 
 int /*<<< orphan*/  regcache_descr_handle ; 
 int /*<<< orphan*/  register_gdbarch_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  registers_ptid ; 

void
_initialize_regcache (void)
{
  regcache_descr_handle = register_gdbarch_data (init_regcache_descr);
  DEPRECATED_REGISTER_GDBARCH_SWAP (current_regcache);
  DEPRECATED_REGISTER_GDBARCH_SWAP (deprecated_registers);
  DEPRECATED_REGISTER_GDBARCH_SWAP (deprecated_register_valid);
  deprecated_register_gdbarch_swap (NULL, 0, build_regcache);

  add_com ("flushregs", class_maintenance, reg_flush_command,
	   "Force gdb to flush its register cache (maintainer command)");

   /* Initialize the thread/process associated with the current set of
      registers.  For now, -1 is special, and means `no current process'.  */
  registers_ptid = pid_to_ptid (-1);

  add_cmd ("registers", class_maintenance,
	   maintenance_print_registers,
	   "Print the internal register configuration.\
Takes an optional file parameter.",
	   &maintenanceprintlist);
  add_cmd ("raw-registers", class_maintenance,
	   maintenance_print_raw_registers,
	   "Print the internal register configuration including raw values.\
Takes an optional file parameter.",
	   &maintenanceprintlist);
  add_cmd ("cooked-registers", class_maintenance,
	   maintenance_print_cooked_registers,
	   "Print the internal register configuration including cooked values.\
Takes an optional file parameter.",
	   &maintenanceprintlist);
  add_cmd ("register-groups", class_maintenance,
	   maintenance_print_register_groups,
	   "Print the internal register configuration including each register's group.\
Takes an optional file parameter.",
	   &maintenanceprintlist);

}