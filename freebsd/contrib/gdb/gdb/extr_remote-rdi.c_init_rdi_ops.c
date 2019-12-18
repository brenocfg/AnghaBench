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
struct TYPE_2__ {char* to_shortname; char* to_longname; char* to_doc; int to_has_all_memory; int to_has_memory; int to_has_stack; int to_has_registers; int to_has_execution; int /*<<< orphan*/  to_magic; int /*<<< orphan*/  to_stratum; int /*<<< orphan*/  to_mourn_inferior; int /*<<< orphan*/  to_create_inferior; int /*<<< orphan*/  to_load; int /*<<< orphan*/  to_kill; int /*<<< orphan*/  to_remove_breakpoint; int /*<<< orphan*/  to_insert_breakpoint; int /*<<< orphan*/  to_files_info; int /*<<< orphan*/  to_xfer_memory; int /*<<< orphan*/  to_prepare_to_store; int /*<<< orphan*/  to_store_registers; int /*<<< orphan*/  to_fetch_registers; int /*<<< orphan*/  to_stop; int /*<<< orphan*/  to_wait; int /*<<< orphan*/  to_resume; int /*<<< orphan*/  to_detach; int /*<<< orphan*/  to_close; int /*<<< orphan*/  to_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPS_MAGIC ; 
 int /*<<< orphan*/  arm_rdi_close ; 
 int /*<<< orphan*/  arm_rdi_create_inferior ; 
 int /*<<< orphan*/  arm_rdi_detach ; 
 int /*<<< orphan*/  arm_rdi_fetch_registers ; 
 int /*<<< orphan*/  arm_rdi_files_info ; 
 int /*<<< orphan*/  arm_rdi_insert_breakpoint ; 
 int /*<<< orphan*/  arm_rdi_kill ; 
 int /*<<< orphan*/  arm_rdi_mourn_inferior ; 
 int /*<<< orphan*/  arm_rdi_open ; 
 TYPE_1__ arm_rdi_ops ; 
 int /*<<< orphan*/  arm_rdi_prepare_to_store ; 
 int /*<<< orphan*/  arm_rdi_remove_breakpoint ; 
 int /*<<< orphan*/  arm_rdi_resume ; 
 int /*<<< orphan*/  arm_rdi_stop ; 
 int /*<<< orphan*/  arm_rdi_store_registers ; 
 int /*<<< orphan*/  arm_rdi_wait ; 
 int /*<<< orphan*/  arm_rdi_xfer_memory ; 
 int /*<<< orphan*/  generic_load ; 
 int /*<<< orphan*/  process_stratum ; 

__attribute__((used)) static void
init_rdi_ops (void)
{
  arm_rdi_ops.to_shortname = "rdi";
  arm_rdi_ops.to_longname = "ARM RDI";
  arm_rdi_ops.to_doc = "Use a remote ARM-based computer; via the RDI library.\n\
Specify the serial device it is connected to (e.g. /dev/ttya).";
  arm_rdi_ops.to_open = arm_rdi_open;
  arm_rdi_ops.to_close = arm_rdi_close;
  arm_rdi_ops.to_detach = arm_rdi_detach;
  arm_rdi_ops.to_resume = arm_rdi_resume;
  arm_rdi_ops.to_wait = arm_rdi_wait;
  arm_rdi_ops.to_stop = arm_rdi_stop;
  arm_rdi_ops.to_fetch_registers = arm_rdi_fetch_registers;
  arm_rdi_ops.to_store_registers = arm_rdi_store_registers;
  arm_rdi_ops.to_prepare_to_store = arm_rdi_prepare_to_store;
  arm_rdi_ops.to_xfer_memory = arm_rdi_xfer_memory;
  arm_rdi_ops.to_files_info = arm_rdi_files_info;
  arm_rdi_ops.to_insert_breakpoint = arm_rdi_insert_breakpoint;
  arm_rdi_ops.to_remove_breakpoint = arm_rdi_remove_breakpoint;
  arm_rdi_ops.to_kill = arm_rdi_kill;
  arm_rdi_ops.to_load = generic_load;
  arm_rdi_ops.to_create_inferior = arm_rdi_create_inferior;
  arm_rdi_ops.to_mourn_inferior = arm_rdi_mourn_inferior;
  arm_rdi_ops.to_stratum = process_stratum;
  arm_rdi_ops.to_has_all_memory = 1;
  arm_rdi_ops.to_has_memory = 1;
  arm_rdi_ops.to_has_stack = 1;
  arm_rdi_ops.to_has_registers = 1;
  arm_rdi_ops.to_has_execution = 1;
  arm_rdi_ops.to_magic = OPS_MAGIC;
}