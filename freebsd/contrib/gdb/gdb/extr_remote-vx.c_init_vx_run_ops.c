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
struct TYPE_2__ {char* to_shortname; char* to_longname; char* to_doc; int to_has_memory; int to_has_stack; int to_has_registers; int to_has_execution; int /*<<< orphan*/  to_magic; int /*<<< orphan*/  to_stratum; int /*<<< orphan*/  to_mourn_inferior; int /*<<< orphan*/  to_lookup_symbol; int /*<<< orphan*/  to_load; int /*<<< orphan*/  to_kill; int /*<<< orphan*/  to_remove_breakpoint; int /*<<< orphan*/  to_insert_breakpoint; int /*<<< orphan*/  to_files_info; int /*<<< orphan*/  to_xfer_memory; int /*<<< orphan*/  to_prepare_to_store; int /*<<< orphan*/  to_store_registers; int /*<<< orphan*/  to_fetch_registers; int /*<<< orphan*/  to_wait; int /*<<< orphan*/  to_resume; int /*<<< orphan*/  to_detach; int /*<<< orphan*/  to_close; int /*<<< orphan*/  to_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPS_MAGIC ; 
 int /*<<< orphan*/  process_stratum ; 
 int /*<<< orphan*/  vx_detach ; 
 int /*<<< orphan*/  vx_insert_breakpoint ; 
 int /*<<< orphan*/  vx_kill ; 
 int /*<<< orphan*/  vx_load_command ; 
 int /*<<< orphan*/  vx_lookup_symbol ; 
 int /*<<< orphan*/  vx_mourn_inferior ; 
 int /*<<< orphan*/  vx_prepare_to_store ; 
 int /*<<< orphan*/  vx_proc_close ; 
 int /*<<< orphan*/  vx_proc_open ; 
 int /*<<< orphan*/  vx_read_register ; 
 int /*<<< orphan*/  vx_remove_breakpoint ; 
 int /*<<< orphan*/  vx_resume ; 
 int /*<<< orphan*/  vx_run_files_info ; 
 TYPE_1__ vx_run_ops ; 
 int /*<<< orphan*/  vx_wait ; 
 int /*<<< orphan*/  vx_write_register ; 
 int /*<<< orphan*/  vx_xfer_memory ; 

__attribute__((used)) static void
init_vx_run_ops (void)
{
  vx_run_ops.to_shortname = "vxprocess";
  vx_run_ops.to_longname = "VxWorks process";
  vx_run_ops.to_doc = "VxWorks process; started by the \"run\" command.";
  vx_run_ops.to_open = vx_proc_open;
  vx_run_ops.to_close = vx_proc_close;
  vx_run_ops.to_detach = vx_detach;
  vx_run_ops.to_resume = vx_resume;
  vx_run_ops.to_wait = vx_wait;
  vx_run_ops.to_fetch_registers = vx_read_register;
  vx_run_ops.to_store_registers = vx_write_register;
  vx_run_ops.to_prepare_to_store = vx_prepare_to_store;
  vx_run_ops.to_xfer_memory = vx_xfer_memory;
  vx_run_ops.to_files_info = vx_run_files_info;
  vx_run_ops.to_insert_breakpoint = vx_insert_breakpoint;
  vx_run_ops.to_remove_breakpoint = vx_remove_breakpoint;
  vx_run_ops.to_kill = vx_kill;
  vx_run_ops.to_load = vx_load_command;
  vx_run_ops.to_lookup_symbol = vx_lookup_symbol;
  vx_run_ops.to_mourn_inferior = vx_mourn_inferior;
  vx_run_ops.to_stratum = process_stratum;
  vx_run_ops.to_has_memory = 1;
  vx_run_ops.to_has_stack = 1;
  vx_run_ops.to_has_registers = 1;
  vx_run_ops.to_has_execution = 1;
  vx_run_ops.to_magic = OPS_MAGIC;
}