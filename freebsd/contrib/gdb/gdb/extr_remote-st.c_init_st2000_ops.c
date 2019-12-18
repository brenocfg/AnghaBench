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
struct TYPE_2__ {char* to_shortname; char* to_longname; char* to_doc; int to_has_all_memory; int to_has_memory; int to_has_stack; int to_has_registers; int to_has_execution; int /*<<< orphan*/  to_magic; int /*<<< orphan*/  to_stratum; int /*<<< orphan*/  to_mourn_inferior; int /*<<< orphan*/  to_create_inferior; int /*<<< orphan*/  to_kill; int /*<<< orphan*/  to_remove_breakpoint; int /*<<< orphan*/  to_insert_breakpoint; int /*<<< orphan*/  to_files_info; int /*<<< orphan*/  to_xfer_memory; int /*<<< orphan*/  to_prepare_to_store; int /*<<< orphan*/  to_store_registers; int /*<<< orphan*/  to_fetch_registers; int /*<<< orphan*/  to_wait; int /*<<< orphan*/  to_resume; int /*<<< orphan*/  to_detach; int /*<<< orphan*/  to_close; int /*<<< orphan*/  to_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPS_MAGIC ; 
 int /*<<< orphan*/  process_stratum ; 
 int /*<<< orphan*/  st2000_close ; 
 int /*<<< orphan*/  st2000_create_inferior ; 
 int /*<<< orphan*/  st2000_detach ; 
 int /*<<< orphan*/  st2000_fetch_register ; 
 int /*<<< orphan*/  st2000_files_info ; 
 int /*<<< orphan*/  st2000_insert_breakpoint ; 
 int /*<<< orphan*/  st2000_kill ; 
 int /*<<< orphan*/  st2000_mourn_inferior ; 
 int /*<<< orphan*/  st2000_open ; 
 TYPE_1__ st2000_ops ; 
 int /*<<< orphan*/  st2000_prepare_to_store ; 
 int /*<<< orphan*/  st2000_remove_breakpoint ; 
 int /*<<< orphan*/  st2000_resume ; 
 int /*<<< orphan*/  st2000_store_register ; 
 int /*<<< orphan*/  st2000_wait ; 
 int /*<<< orphan*/  st2000_xfer_inferior_memory ; 

__attribute__((used)) static void
init_st2000_ops (void)
{
  st2000_ops.to_shortname = "st2000";
  st2000_ops.to_longname = "Remote serial Tandem ST2000 target";
  st2000_ops.to_doc = "Use a remote computer running STDEBUG connected by a serial line;\n\
or a network connection.\n\
Arguments are the name of the device for the serial line,\n\
the speed to connect at in bits per second.";
  st2000_ops.to_open = st2000_open;
  st2000_ops.to_close = st2000_close;
  st2000_ops.to_detach = st2000_detach;
  st2000_ops.to_resume = st2000_resume;
  st2000_ops.to_wait = st2000_wait;
  st2000_ops.to_fetch_registers = st2000_fetch_register;
  st2000_ops.to_store_registers = st2000_store_register;
  st2000_ops.to_prepare_to_store = st2000_prepare_to_store;
  st2000_ops.to_xfer_memory = st2000_xfer_inferior_memory;
  st2000_ops.to_files_info = st2000_files_info;
  st2000_ops.to_insert_breakpoint = st2000_insert_breakpoint;
  st2000_ops.to_remove_breakpoint = st2000_remove_breakpoint;	/* Breakpoints */
  st2000_ops.to_kill = st2000_kill;
  st2000_ops.to_create_inferior = st2000_create_inferior;
  st2000_ops.to_mourn_inferior = st2000_mourn_inferior;
  st2000_ops.to_stratum = process_stratum;
  st2000_ops.to_has_all_memory = 1;
  st2000_ops.to_has_memory = 1;
  st2000_ops.to_has_stack = 1;
  st2000_ops.to_has_registers = 1;
  st2000_ops.to_has_execution = 1;	/* all mem, mem, stack, regs, exec */
  st2000_ops.to_magic = OPS_MAGIC;	/* Always the last thing */
}