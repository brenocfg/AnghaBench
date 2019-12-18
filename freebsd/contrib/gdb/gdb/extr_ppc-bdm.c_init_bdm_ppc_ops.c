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
struct TYPE_2__ {char* to_shortname; char* to_longname; char* to_doc; int to_has_all_memory; int to_has_memory; int to_has_stack; int to_has_registers; int to_has_execution; int /*<<< orphan*/  to_magic; int /*<<< orphan*/  to_stratum; int /*<<< orphan*/  to_stop; int /*<<< orphan*/  to_thread_alive; int /*<<< orphan*/  to_mourn_inferior; int /*<<< orphan*/  to_create_inferior; int /*<<< orphan*/  to_load; int /*<<< orphan*/  to_kill; int /*<<< orphan*/  to_remove_breakpoint; int /*<<< orphan*/  to_insert_breakpoint; int /*<<< orphan*/  to_files_info; int /*<<< orphan*/  to_xfer_memory; int /*<<< orphan*/  to_prepare_to_store; int /*<<< orphan*/  to_store_registers; int /*<<< orphan*/  to_fetch_registers; int /*<<< orphan*/  to_wait; int /*<<< orphan*/  to_resume; int /*<<< orphan*/  to_detach; int /*<<< orphan*/  to_close; int /*<<< orphan*/  to_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPS_MAGIC ; 
 int /*<<< orphan*/  bdm_ppc_fetch_registers ; 
 int /*<<< orphan*/  bdm_ppc_open ; 
 TYPE_1__ bdm_ppc_ops ; 
 int /*<<< orphan*/  bdm_ppc_store_registers ; 
 int /*<<< orphan*/  bdm_ppc_wait ; 
 int /*<<< orphan*/  ocd_close ; 
 int /*<<< orphan*/  ocd_create_inferior ; 
 int /*<<< orphan*/  ocd_detach ; 
 int /*<<< orphan*/  ocd_files_info ; 
 int /*<<< orphan*/  ocd_insert_breakpoint ; 
 int /*<<< orphan*/  ocd_kill ; 
 int /*<<< orphan*/  ocd_load ; 
 int /*<<< orphan*/  ocd_mourn ; 
 int /*<<< orphan*/  ocd_prepare_to_store ; 
 int /*<<< orphan*/  ocd_remove_breakpoint ; 
 int /*<<< orphan*/  ocd_resume ; 
 int /*<<< orphan*/  ocd_stop ; 
 int /*<<< orphan*/  ocd_thread_alive ; 
 int /*<<< orphan*/  ocd_xfer_memory ; 
 int /*<<< orphan*/  process_stratum ; 

__attribute__((used)) static void
init_bdm_ppc_ops (void)
{
  bdm_ppc_ops.to_shortname = "ocd";
  bdm_ppc_ops.to_longname = "Remote target with On-Chip Debugging";
  bdm_ppc_ops.to_doc = "Use a remote target with On-Chip Debugging.  To use a target box;\n\
specify the serial device it is connected to (e.g. /dev/ttya).  To use\n\
a wiggler, specify wiggler and then the port it is connected to\n\
(e.g. wiggler lpt1).";		/* to_doc */
  bdm_ppc_ops.to_open = bdm_ppc_open;
  bdm_ppc_ops.to_close = ocd_close;
  bdm_ppc_ops.to_detach = ocd_detach;
  bdm_ppc_ops.to_resume = ocd_resume;
  bdm_ppc_ops.to_wait = bdm_ppc_wait;
  bdm_ppc_ops.to_fetch_registers = bdm_ppc_fetch_registers;
  bdm_ppc_ops.to_store_registers = bdm_ppc_store_registers;
  bdm_ppc_ops.to_prepare_to_store = ocd_prepare_to_store;
  bdm_ppc_ops.to_xfer_memory = ocd_xfer_memory;
  bdm_ppc_ops.to_files_info = ocd_files_info;
  bdm_ppc_ops.to_insert_breakpoint = ocd_insert_breakpoint;
  bdm_ppc_ops.to_remove_breakpoint = ocd_remove_breakpoint;
  bdm_ppc_ops.to_kill = ocd_kill;
  bdm_ppc_ops.to_load = ocd_load;
  bdm_ppc_ops.to_create_inferior = ocd_create_inferior;
  bdm_ppc_ops.to_mourn_inferior = ocd_mourn;
  bdm_ppc_ops.to_thread_alive = ocd_thread_alive;
  bdm_ppc_ops.to_stop = ocd_stop;
  bdm_ppc_ops.to_stratum = process_stratum;
  bdm_ppc_ops.to_has_all_memory = 1;
  bdm_ppc_ops.to_has_memory = 1;
  bdm_ppc_ops.to_has_stack = 1;
  bdm_ppc_ops.to_has_registers = 1;
  bdm_ppc_ops.to_has_execution = 1;
  bdm_ppc_ops.to_magic = OPS_MAGIC;
}