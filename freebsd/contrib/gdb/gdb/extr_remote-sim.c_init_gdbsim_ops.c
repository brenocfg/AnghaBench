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
struct TYPE_3__ {char* to_shortname; char* to_longname; char* to_doc; int to_has_all_memory; int to_has_memory; int to_has_stack; int to_has_registers; int to_has_execution; int /*<<< orphan*/  to_magic; int /*<<< orphan*/  to_stratum; int /*<<< orphan*/  to_stop; int /*<<< orphan*/  to_mourn_inferior; int /*<<< orphan*/  to_create_inferior; int /*<<< orphan*/  to_load; int /*<<< orphan*/  to_kill; int /*<<< orphan*/  to_remove_breakpoint; int /*<<< orphan*/  to_insert_breakpoint; int /*<<< orphan*/  to_files_info; int /*<<< orphan*/  to_xfer_memory; int /*<<< orphan*/  to_prepare_to_store; int /*<<< orphan*/  to_store_registers; int /*<<< orphan*/  to_fetch_registers; int /*<<< orphan*/  to_wait; int /*<<< orphan*/  to_resume; int /*<<< orphan*/  to_detach; int /*<<< orphan*/  to_close; int /*<<< orphan*/  to_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPS_MAGIC ; 
 int /*<<< orphan*/  TARGET_REDEFINE_DEFAULT_OPS (TYPE_1__*) ; 
 int /*<<< orphan*/  gdbsim_close ; 
 int /*<<< orphan*/  gdbsim_create_inferior ; 
 int /*<<< orphan*/  gdbsim_detach ; 
 int /*<<< orphan*/  gdbsim_fetch_register ; 
 int /*<<< orphan*/  gdbsim_files_info ; 
 int /*<<< orphan*/  gdbsim_insert_breakpoint ; 
 int /*<<< orphan*/  gdbsim_kill ; 
 int /*<<< orphan*/  gdbsim_load ; 
 int /*<<< orphan*/  gdbsim_mourn_inferior ; 
 int /*<<< orphan*/  gdbsim_open ; 
 TYPE_1__ gdbsim_ops ; 
 int /*<<< orphan*/  gdbsim_prepare_to_store ; 
 int /*<<< orphan*/  gdbsim_remove_breakpoint ; 
 int /*<<< orphan*/  gdbsim_resume ; 
 int /*<<< orphan*/  gdbsim_stop ; 
 int /*<<< orphan*/  gdbsim_store_register ; 
 int /*<<< orphan*/  gdbsim_wait ; 
 int /*<<< orphan*/  gdbsim_xfer_inferior_memory ; 
 int /*<<< orphan*/  process_stratum ; 

__attribute__((used)) static void
init_gdbsim_ops (void)
{
  gdbsim_ops.to_shortname = "sim";
  gdbsim_ops.to_longname = "simulator";
  gdbsim_ops.to_doc = "Use the compiled-in simulator.";
  gdbsim_ops.to_open = gdbsim_open;
  gdbsim_ops.to_close = gdbsim_close;
  gdbsim_ops.to_detach = gdbsim_detach;
  gdbsim_ops.to_resume = gdbsim_resume;
  gdbsim_ops.to_wait = gdbsim_wait;
  gdbsim_ops.to_fetch_registers = gdbsim_fetch_register;
  gdbsim_ops.to_store_registers = gdbsim_store_register;
  gdbsim_ops.to_prepare_to_store = gdbsim_prepare_to_store;
  gdbsim_ops.to_xfer_memory = gdbsim_xfer_inferior_memory;
  gdbsim_ops.to_files_info = gdbsim_files_info;
  gdbsim_ops.to_insert_breakpoint = gdbsim_insert_breakpoint;
  gdbsim_ops.to_remove_breakpoint = gdbsim_remove_breakpoint;
  gdbsim_ops.to_kill = gdbsim_kill;
  gdbsim_ops.to_load = gdbsim_load;
  gdbsim_ops.to_create_inferior = gdbsim_create_inferior;
  gdbsim_ops.to_mourn_inferior = gdbsim_mourn_inferior;
  gdbsim_ops.to_stop = gdbsim_stop;
  gdbsim_ops.to_stratum = process_stratum;
  gdbsim_ops.to_has_all_memory = 1;
  gdbsim_ops.to_has_memory = 1;
  gdbsim_ops.to_has_stack = 1;
  gdbsim_ops.to_has_registers = 1;
  gdbsim_ops.to_has_execution = 1;
  gdbsim_ops.to_magic = OPS_MAGIC;

#ifdef TARGET_REDEFINE_DEFAULT_OPS
  TARGET_REDEFINE_DEFAULT_OPS (&gdbsim_ops);
#endif
}