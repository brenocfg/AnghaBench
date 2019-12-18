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
struct TYPE_2__ {char* to_shortname; char* to_longname; char* to_doc; int to_has_all_memory; int to_has_memory; int to_has_stack; int to_has_registers; int to_has_execution; int /*<<< orphan*/  to_magic; int /*<<< orphan*/  to_stratum; int /*<<< orphan*/  to_pid_to_exec_file; int /*<<< orphan*/  to_stop; int /*<<< orphan*/  to_pid_to_str; int /*<<< orphan*/  to_thread_alive; int /*<<< orphan*/  to_can_run; int /*<<< orphan*/  to_mourn_inferior; int /*<<< orphan*/  to_create_inferior; int /*<<< orphan*/  to_kill; int /*<<< orphan*/  to_terminal_info; int /*<<< orphan*/  to_terminal_ours; int /*<<< orphan*/  to_terminal_save_ours; int /*<<< orphan*/  to_terminal_ours_for_output; int /*<<< orphan*/  to_terminal_inferior; int /*<<< orphan*/  to_terminal_init; int /*<<< orphan*/  to_remove_breakpoint; int /*<<< orphan*/  to_insert_breakpoint; int /*<<< orphan*/  to_find_memory_regions; int /*<<< orphan*/  to_xfer_memory; int /*<<< orphan*/  to_prepare_to_store; int /*<<< orphan*/  to_store_registers; int /*<<< orphan*/  to_fetch_registers; int /*<<< orphan*/  to_wait; int /*<<< orphan*/  to_resume; int /*<<< orphan*/  to_detach; int /*<<< orphan*/  to_attach; int /*<<< orphan*/  to_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPS_MAGIC ; 
 int /*<<< orphan*/  child_terminal_info ; 
 int /*<<< orphan*/  gnu_attach ; 
 int /*<<< orphan*/  gnu_can_run ; 
 int /*<<< orphan*/  gnu_create_inferior ; 
 int /*<<< orphan*/  gnu_detach ; 
 int /*<<< orphan*/  gnu_fetch_registers ; 
 int /*<<< orphan*/  gnu_find_memory_regions ; 
 int /*<<< orphan*/  gnu_kill_inferior ; 
 int /*<<< orphan*/  gnu_mourn_inferior ; 
 int /*<<< orphan*/  gnu_open ; 
 TYPE_1__ gnu_ops ; 
 int /*<<< orphan*/  gnu_pid_to_exec_file ; 
 int /*<<< orphan*/  gnu_pid_to_str ; 
 int /*<<< orphan*/  gnu_prepare_to_store ; 
 int /*<<< orphan*/  gnu_resume ; 
 int /*<<< orphan*/  gnu_stop ; 
 int /*<<< orphan*/  gnu_store_registers ; 
 int /*<<< orphan*/  gnu_terminal_init_inferior ; 
 int /*<<< orphan*/  gnu_thread_alive ; 
 int /*<<< orphan*/  gnu_wait ; 
 int /*<<< orphan*/  gnu_xfer_memory ; 
 int /*<<< orphan*/  memory_insert_breakpoint ; 
 int /*<<< orphan*/  memory_remove_breakpoint ; 
 int /*<<< orphan*/  process_stratum ; 
 int /*<<< orphan*/  terminal_inferior ; 
 int /*<<< orphan*/  terminal_ours ; 
 int /*<<< orphan*/  terminal_ours_for_output ; 
 int /*<<< orphan*/  terminal_save_ours ; 

__attribute__((used)) static void
init_gnu_ops (void)
{
  gnu_ops.to_shortname = "GNU";		/* to_shortname */
  gnu_ops.to_longname = "GNU Hurd process"; /* to_longname */
  gnu_ops.to_doc = "GNU Hurd process";	/* to_doc */
  gnu_ops.to_open = gnu_open;		/* to_open */
  gnu_ops.to_attach = gnu_attach;	/* to_attach */
  gnu_ops.to_detach = gnu_detach;	/* to_detach */
  gnu_ops.to_resume = gnu_resume;	/* to_resume */
  gnu_ops.to_wait = gnu_wait;		/* to_wait */
  gnu_ops.to_fetch_registers = gnu_fetch_registers;    /* to_fetch_registers */
  gnu_ops.to_store_registers = gnu_store_registers;    /* to_store_registers */
  gnu_ops.to_prepare_to_store = gnu_prepare_to_store; /* to_prepare_to_store */
  gnu_ops.to_xfer_memory = gnu_xfer_memory; /* to_xfer_memory */
  gnu_ops.to_find_memory_regions = gnu_find_memory_regions;
  gnu_ops.to_insert_breakpoint = memory_insert_breakpoint;
  gnu_ops.to_remove_breakpoint = memory_remove_breakpoint;
  gnu_ops.to_terminal_init = gnu_terminal_init_inferior;
  gnu_ops.to_terminal_inferior = terminal_inferior;
  gnu_ops.to_terminal_ours_for_output = terminal_ours_for_output;
  gnu_ops.to_terminal_save_ours = terminal_save_ours;
  gnu_ops.to_terminal_ours = terminal_ours;
  gnu_ops.to_terminal_info = child_terminal_info;
  gnu_ops.to_kill = gnu_kill_inferior;	/* to_kill */
  gnu_ops.to_create_inferior = gnu_create_inferior; /* to_create_inferior */
  gnu_ops.to_mourn_inferior = gnu_mourn_inferior;	/* to_mourn_inferior */
  gnu_ops.to_can_run = gnu_can_run;	/* to_can_run */
  gnu_ops.to_thread_alive = gnu_thread_alive;	/* to_thread_alive */
  gnu_ops.to_pid_to_str = gnu_pid_to_str;   /* to_pid_to_str */
  gnu_ops.to_stop = gnu_stop;	/* to_stop */
  gnu_ops.to_pid_to_exec_file = gnu_pid_to_exec_file; /* to_pid_to_exec_file */
  gnu_ops.to_stratum = process_stratum;		/* to_stratum */
  gnu_ops.to_has_all_memory = 1;	/* to_has_all_memory */
  gnu_ops.to_has_memory = 1;		/* to_has_memory */
  gnu_ops.to_has_stack = 1;		/* to_has_stack */
  gnu_ops.to_has_registers = 1;		/* to_has_registers */
  gnu_ops.to_has_execution = 1;		/* to_has_execution */
  gnu_ops.to_magic = OPS_MAGIC;		/* to_magic */
}