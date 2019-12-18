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
struct TYPE_2__ {char* to_shortname; char* to_longname; char* to_doc; int to_has_all_memory; int to_has_memory; int to_has_stack; int to_has_registers; int to_has_execution; int /*<<< orphan*/  to_magic; int /*<<< orphan*/  to_stratum; int /*<<< orphan*/  to_pid_to_exec_file; int /*<<< orphan*/  to_get_current_exception_event; int /*<<< orphan*/  to_enable_exception_callback; int /*<<< orphan*/  to_stop; int /*<<< orphan*/  to_pid_to_str; int /*<<< orphan*/  to_thread_alive; int /*<<< orphan*/  to_can_run; int /*<<< orphan*/  to_mourn_inferior; int /*<<< orphan*/  to_has_exited; int /*<<< orphan*/  to_reported_exec_events_per_exec_call; int /*<<< orphan*/  to_remove_exec_catchpoint; int /*<<< orphan*/  to_insert_exec_catchpoint; int /*<<< orphan*/  to_follow_fork; int /*<<< orphan*/  to_remove_vfork_catchpoint; int /*<<< orphan*/  to_insert_vfork_catchpoint; int /*<<< orphan*/  to_remove_fork_catchpoint; int /*<<< orphan*/  to_insert_fork_catchpoint; int /*<<< orphan*/  to_acknowledge_created_inferior; int /*<<< orphan*/  to_post_startup_inferior; int /*<<< orphan*/  to_create_inferior; int /*<<< orphan*/  to_kill; int /*<<< orphan*/  to_terminal_info; int /*<<< orphan*/  to_terminal_ours; int /*<<< orphan*/  to_terminal_save_ours; int /*<<< orphan*/  to_terminal_ours_for_output; int /*<<< orphan*/  to_terminal_inferior; int /*<<< orphan*/  to_terminal_init; int /*<<< orphan*/  to_remove_breakpoint; int /*<<< orphan*/  to_insert_breakpoint; int /*<<< orphan*/  to_files_info; int /*<<< orphan*/  to_xfer_partial; int /*<<< orphan*/  to_xfer_memory; int /*<<< orphan*/  to_prepare_to_store; int /*<<< orphan*/  to_store_registers; int /*<<< orphan*/  to_fetch_registers; int /*<<< orphan*/  to_post_wait; int /*<<< orphan*/  to_wait; int /*<<< orphan*/  to_resume; int /*<<< orphan*/  to_detach; int /*<<< orphan*/  to_post_attach; int /*<<< orphan*/  to_attach; int /*<<< orphan*/  to_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPS_MAGIC ; 
 int /*<<< orphan*/  child_acknowledge_created_inferior ; 
 int /*<<< orphan*/  child_attach ; 
 int /*<<< orphan*/  child_can_run ; 
 int /*<<< orphan*/  child_create_inferior ; 
 int /*<<< orphan*/  child_detach ; 
 int /*<<< orphan*/  child_enable_exception_callback ; 
 int /*<<< orphan*/  child_files_info ; 
 int /*<<< orphan*/  child_follow_fork ; 
 int /*<<< orphan*/  child_get_current_exception_event ; 
 int /*<<< orphan*/  child_has_exited ; 
 int /*<<< orphan*/  child_insert_exec_catchpoint ; 
 int /*<<< orphan*/  child_insert_fork_catchpoint ; 
 int /*<<< orphan*/  child_insert_vfork_catchpoint ; 
 int /*<<< orphan*/  child_mourn_inferior ; 
 int /*<<< orphan*/  child_open ; 
 TYPE_1__ child_ops ; 
 int /*<<< orphan*/  child_pid_to_exec_file ; 
 int /*<<< orphan*/  child_pid_to_str ; 
 int /*<<< orphan*/  child_post_attach ; 
 int /*<<< orphan*/  child_post_startup_inferior ; 
 int /*<<< orphan*/  child_post_wait ; 
 int /*<<< orphan*/  child_prepare_to_store ; 
 int /*<<< orphan*/  child_remove_exec_catchpoint ; 
 int /*<<< orphan*/  child_remove_fork_catchpoint ; 
 int /*<<< orphan*/  child_remove_vfork_catchpoint ; 
 int /*<<< orphan*/  child_reported_exec_events_per_exec_call ; 
 int /*<<< orphan*/  child_resume ; 
 int /*<<< orphan*/  child_stop ; 
 int /*<<< orphan*/  child_terminal_info ; 
 int /*<<< orphan*/  child_thread_alive ; 
 int /*<<< orphan*/  child_wait ; 
 int /*<<< orphan*/  child_xfer_memory ; 
 int /*<<< orphan*/  child_xfer_partial ; 
 int /*<<< orphan*/  fetch_inferior_registers ; 
 int /*<<< orphan*/  kill_inferior ; 
 int /*<<< orphan*/  memory_insert_breakpoint ; 
 int /*<<< orphan*/  memory_remove_breakpoint ; 
 int /*<<< orphan*/  process_stratum ; 
 int /*<<< orphan*/  store_inferior_registers ; 
 int /*<<< orphan*/  terminal_inferior ; 
 int /*<<< orphan*/  terminal_init_inferior ; 
 int /*<<< orphan*/  terminal_ours ; 
 int /*<<< orphan*/  terminal_ours_for_output ; 
 int /*<<< orphan*/  terminal_save_ours ; 

__attribute__((used)) static void
init_child_ops (void)
{
  child_ops.to_shortname = "child";
  child_ops.to_longname = "Unix child process";
  child_ops.to_doc = "Unix child process (started by the \"run\" command).";
  child_ops.to_open = child_open;
  child_ops.to_attach = child_attach;
  child_ops.to_post_attach = child_post_attach;
  child_ops.to_detach = child_detach;
  child_ops.to_resume = child_resume;
  child_ops.to_wait = child_wait;
  child_ops.to_post_wait = child_post_wait;
  child_ops.to_fetch_registers = fetch_inferior_registers;
  child_ops.to_store_registers = store_inferior_registers;
  child_ops.to_prepare_to_store = child_prepare_to_store;
  child_ops.to_xfer_memory = child_xfer_memory;
  child_ops.to_xfer_partial = child_xfer_partial;
  child_ops.to_files_info = child_files_info;
  child_ops.to_insert_breakpoint = memory_insert_breakpoint;
  child_ops.to_remove_breakpoint = memory_remove_breakpoint;
  child_ops.to_terminal_init = terminal_init_inferior;
  child_ops.to_terminal_inferior = terminal_inferior;
  child_ops.to_terminal_ours_for_output = terminal_ours_for_output;
  child_ops.to_terminal_save_ours = terminal_save_ours;
  child_ops.to_terminal_ours = terminal_ours;
  child_ops.to_terminal_info = child_terminal_info;
  child_ops.to_kill = kill_inferior;
  child_ops.to_create_inferior = child_create_inferior;
  child_ops.to_post_startup_inferior = child_post_startup_inferior;
  child_ops.to_acknowledge_created_inferior = child_acknowledge_created_inferior;
  child_ops.to_insert_fork_catchpoint = child_insert_fork_catchpoint;
  child_ops.to_remove_fork_catchpoint = child_remove_fork_catchpoint;
  child_ops.to_insert_vfork_catchpoint = child_insert_vfork_catchpoint;
  child_ops.to_remove_vfork_catchpoint = child_remove_vfork_catchpoint;
  child_ops.to_follow_fork = child_follow_fork;
  child_ops.to_insert_exec_catchpoint = child_insert_exec_catchpoint;
  child_ops.to_remove_exec_catchpoint = child_remove_exec_catchpoint;
  child_ops.to_reported_exec_events_per_exec_call = child_reported_exec_events_per_exec_call;
  child_ops.to_has_exited = child_has_exited;
  child_ops.to_mourn_inferior = child_mourn_inferior;
  child_ops.to_can_run = child_can_run;
  child_ops.to_thread_alive = child_thread_alive;
  child_ops.to_pid_to_str = child_pid_to_str;
  child_ops.to_stop = child_stop;
  child_ops.to_enable_exception_callback = child_enable_exception_callback;
  child_ops.to_get_current_exception_event = child_get_current_exception_event;
  child_ops.to_pid_to_exec_file = child_pid_to_exec_file;
  child_ops.to_stratum = process_stratum;
  child_ops.to_has_all_memory = 1;
  child_ops.to_has_memory = 1;
  child_ops.to_has_stack = 1;
  child_ops.to_has_registers = 1;
  child_ops.to_has_execution = 1;
  child_ops.to_magic = OPS_MAGIC;
}