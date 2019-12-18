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
struct TYPE_2__ {int to_has_all_memory; int to_has_memory; int to_has_stack; int to_has_registers; int to_has_execution; int /*<<< orphan*/  to_magic; int /*<<< orphan*/  to_stratum; int /*<<< orphan*/  to_rcmd; int /*<<< orphan*/  to_stop; int /*<<< orphan*/  to_mourn_inferior; int /*<<< orphan*/  to_create_inferior; int /*<<< orphan*/  to_load; int /*<<< orphan*/  to_kill; int /*<<< orphan*/  to_remove_breakpoint; int /*<<< orphan*/  to_insert_breakpoint; int /*<<< orphan*/  to_files_info; int /*<<< orphan*/  to_xfer_memory; int /*<<< orphan*/  to_prepare_to_store; int /*<<< orphan*/  to_store_registers; int /*<<< orphan*/  to_fetch_registers; int /*<<< orphan*/  to_wait; int /*<<< orphan*/  to_resume; int /*<<< orphan*/  to_detach; int /*<<< orphan*/  to_close; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPS_MAGIC ; 
 int /*<<< orphan*/  monitor_close ; 
 int /*<<< orphan*/  monitor_create_inferior ; 
 int /*<<< orphan*/  monitor_detach ; 
 int /*<<< orphan*/  monitor_fetch_registers ; 
 int /*<<< orphan*/  monitor_files_info ; 
 int /*<<< orphan*/  monitor_insert_breakpoint ; 
 int /*<<< orphan*/  monitor_kill ; 
 int /*<<< orphan*/  monitor_load ; 
 int /*<<< orphan*/  monitor_mourn_inferior ; 
 TYPE_1__ monitor_ops ; 
 int /*<<< orphan*/  monitor_prepare_to_store ; 
 int /*<<< orphan*/  monitor_rcmd ; 
 int /*<<< orphan*/  monitor_remove_breakpoint ; 
 int /*<<< orphan*/  monitor_resume ; 
 int /*<<< orphan*/  monitor_stop ; 
 int /*<<< orphan*/  monitor_store_registers ; 
 int /*<<< orphan*/  monitor_wait ; 
 int /*<<< orphan*/  monitor_xfer_memory ; 
 int /*<<< orphan*/  process_stratum ; 

__attribute__((used)) static void
init_base_monitor_ops (void)
{
  monitor_ops.to_close = monitor_close;
  monitor_ops.to_detach = monitor_detach;
  monitor_ops.to_resume = monitor_resume;
  monitor_ops.to_wait = monitor_wait;
  monitor_ops.to_fetch_registers = monitor_fetch_registers;
  monitor_ops.to_store_registers = monitor_store_registers;
  monitor_ops.to_prepare_to_store = monitor_prepare_to_store;
  monitor_ops.to_xfer_memory = monitor_xfer_memory;
  monitor_ops.to_files_info = monitor_files_info;
  monitor_ops.to_insert_breakpoint = monitor_insert_breakpoint;
  monitor_ops.to_remove_breakpoint = monitor_remove_breakpoint;
  monitor_ops.to_kill = monitor_kill;
  monitor_ops.to_load = monitor_load;
  monitor_ops.to_create_inferior = monitor_create_inferior;
  monitor_ops.to_mourn_inferior = monitor_mourn_inferior;
  monitor_ops.to_stop = monitor_stop;
  monitor_ops.to_rcmd = monitor_rcmd;
  monitor_ops.to_stratum = process_stratum;
  monitor_ops.to_has_all_memory = 1;
  monitor_ops.to_has_memory = 1;
  monitor_ops.to_has_stack = 1;
  monitor_ops.to_has_registers = 1;
  monitor_ops.to_has_execution = 1;
  monitor_ops.to_magic = OPS_MAGIC;
}