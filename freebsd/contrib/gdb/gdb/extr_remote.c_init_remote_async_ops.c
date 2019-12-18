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
struct TYPE_2__ {char* to_shortname; char* to_longname; char* to_doc; int to_has_all_memory; int to_has_memory; int to_has_stack; int to_has_registers; int to_has_execution; int to_async_mask_value; int /*<<< orphan*/  to_magic; int /*<<< orphan*/  to_async; int /*<<< orphan*/  to_is_async_p; int /*<<< orphan*/  to_can_async_p; int /*<<< orphan*/  to_has_thread_control; int /*<<< orphan*/  to_stratum; int /*<<< orphan*/  to_rcmd; int /*<<< orphan*/  to_xfer_partial; int /*<<< orphan*/  to_stop; int /*<<< orphan*/  to_extra_thread_info; int /*<<< orphan*/  to_pid_to_str; int /*<<< orphan*/  to_find_new_threads; int /*<<< orphan*/  to_thread_alive; int /*<<< orphan*/  to_mourn_inferior; int /*<<< orphan*/  to_load; int /*<<< orphan*/  to_kill; int /*<<< orphan*/  to_terminal_ours; int /*<<< orphan*/  to_terminal_inferior; int /*<<< orphan*/  to_stopped_data_address; int /*<<< orphan*/  to_stopped_by_watchpoint; int /*<<< orphan*/  to_remove_watchpoint; int /*<<< orphan*/  to_insert_watchpoint; int /*<<< orphan*/  to_remove_hw_breakpoint; int /*<<< orphan*/  to_insert_hw_breakpoint; int /*<<< orphan*/  to_can_use_hw_breakpoint; int /*<<< orphan*/  to_remove_breakpoint; int /*<<< orphan*/  to_insert_breakpoint; int /*<<< orphan*/  to_files_info; int /*<<< orphan*/  to_xfer_memory; int /*<<< orphan*/  to_prepare_to_store; int /*<<< orphan*/  to_store_registers; int /*<<< orphan*/  to_fetch_registers; int /*<<< orphan*/  to_wait; int /*<<< orphan*/  to_resume; int /*<<< orphan*/  to_disconnect; int /*<<< orphan*/  to_detach; int /*<<< orphan*/  to_close; int /*<<< orphan*/  to_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPS_MAGIC ; 
 int /*<<< orphan*/  generic_load ; 
 int /*<<< orphan*/  process_stratum ; 
 int /*<<< orphan*/  remote_async ; 
 int /*<<< orphan*/  remote_async_kill ; 
 int /*<<< orphan*/  remote_async_mourn ; 
 int /*<<< orphan*/  remote_async_open ; 
 TYPE_1__ remote_async_ops ; 
 int /*<<< orphan*/  remote_async_resume ; 
 int /*<<< orphan*/  remote_async_terminal_inferior ; 
 int /*<<< orphan*/  remote_async_terminal_ours ; 
 int /*<<< orphan*/  remote_async_wait ; 
 int /*<<< orphan*/  remote_can_async_p ; 
 int /*<<< orphan*/  remote_check_watch_resources ; 
 int /*<<< orphan*/  remote_close ; 
 int /*<<< orphan*/  remote_detach ; 
 int /*<<< orphan*/  remote_disconnect ; 
 int /*<<< orphan*/  remote_fetch_registers ; 
 int /*<<< orphan*/  remote_files_info ; 
 int /*<<< orphan*/  remote_insert_breakpoint ; 
 int /*<<< orphan*/  remote_insert_hw_breakpoint ; 
 int /*<<< orphan*/  remote_insert_watchpoint ; 
 int /*<<< orphan*/  remote_is_async_p ; 
 int /*<<< orphan*/  remote_pid_to_str ; 
 int /*<<< orphan*/  remote_prepare_to_store ; 
 int /*<<< orphan*/  remote_rcmd ; 
 int /*<<< orphan*/  remote_remove_breakpoint ; 
 int /*<<< orphan*/  remote_remove_hw_breakpoint ; 
 int /*<<< orphan*/  remote_remove_watchpoint ; 
 int /*<<< orphan*/  remote_stop ; 
 int /*<<< orphan*/  remote_stopped_by_watchpoint ; 
 int /*<<< orphan*/  remote_stopped_data_address ; 
 int /*<<< orphan*/  remote_store_registers ; 
 int /*<<< orphan*/  remote_thread_alive ; 
 int /*<<< orphan*/  remote_threads_extra_info ; 
 int /*<<< orphan*/  remote_threads_info ; 
 int /*<<< orphan*/  remote_xfer_memory ; 
 int /*<<< orphan*/  remote_xfer_partial ; 
 int /*<<< orphan*/  tc_schedlock ; 

__attribute__((used)) static void
init_remote_async_ops (void)
{
  remote_async_ops.to_shortname = "async";
  remote_async_ops.to_longname = "Remote serial target in async version of the gdb-specific protocol";
  remote_async_ops.to_doc =
    "Use a remote computer via a serial line, using a gdb-specific protocol.\n\
Specify the serial device it is connected to (e.g. /dev/ttya).";
  remote_async_ops.to_open = remote_async_open;
  remote_async_ops.to_close = remote_close;
  remote_async_ops.to_detach = remote_detach;
  remote_async_ops.to_disconnect = remote_disconnect;
  remote_async_ops.to_resume = remote_async_resume;
  remote_async_ops.to_wait = remote_async_wait;
  remote_async_ops.to_fetch_registers = remote_fetch_registers;
  remote_async_ops.to_store_registers = remote_store_registers;
  remote_async_ops.to_prepare_to_store = remote_prepare_to_store;
  remote_async_ops.to_xfer_memory = remote_xfer_memory;
  remote_async_ops.to_files_info = remote_files_info;
  remote_async_ops.to_insert_breakpoint = remote_insert_breakpoint;
  remote_async_ops.to_remove_breakpoint = remote_remove_breakpoint;
  remote_async_ops.to_can_use_hw_breakpoint = remote_check_watch_resources;
  remote_async_ops.to_insert_hw_breakpoint = remote_insert_hw_breakpoint;
  remote_async_ops.to_remove_hw_breakpoint = remote_remove_hw_breakpoint;
  remote_async_ops.to_insert_watchpoint = remote_insert_watchpoint;
  remote_async_ops.to_remove_watchpoint = remote_remove_watchpoint;
  remote_async_ops.to_stopped_by_watchpoint = remote_stopped_by_watchpoint;
  remote_async_ops.to_stopped_data_address = remote_stopped_data_address;
  remote_async_ops.to_terminal_inferior = remote_async_terminal_inferior;
  remote_async_ops.to_terminal_ours = remote_async_terminal_ours;
  remote_async_ops.to_kill = remote_async_kill;
  remote_async_ops.to_load = generic_load;
  remote_async_ops.to_mourn_inferior = remote_async_mourn;
  remote_async_ops.to_thread_alive = remote_thread_alive;
  remote_async_ops.to_find_new_threads = remote_threads_info;
  remote_async_ops.to_pid_to_str = remote_pid_to_str;
  remote_async_ops.to_extra_thread_info = remote_threads_extra_info;
  remote_async_ops.to_stop = remote_stop;
  remote_async_ops.to_xfer_partial = remote_xfer_partial;
  remote_async_ops.to_rcmd = remote_rcmd;
  remote_async_ops.to_stratum = process_stratum;
  remote_async_ops.to_has_all_memory = 1;
  remote_async_ops.to_has_memory = 1;
  remote_async_ops.to_has_stack = 1;
  remote_async_ops.to_has_registers = 1;
  remote_async_ops.to_has_execution = 1;
  remote_async_ops.to_has_thread_control = tc_schedlock;	/* can lock scheduler */
  remote_async_ops.to_can_async_p = remote_can_async_p;
  remote_async_ops.to_is_async_p = remote_is_async_p;
  remote_async_ops.to_async = remote_async;
  remote_async_ops.to_async_mask_value = 1;
  remote_async_ops.to_magic = OPS_MAGIC;
}