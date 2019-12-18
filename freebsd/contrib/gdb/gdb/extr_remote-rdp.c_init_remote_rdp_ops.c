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
struct TYPE_2__ {char* to_shortname; char* to_longname; char* to_doc; int to_has_all_memory; int to_has_memory; int to_has_stack; int to_has_registers; int to_has_execution; int /*<<< orphan*/  to_magic; int /*<<< orphan*/  to_stratum; int /*<<< orphan*/  to_mourn_inferior; int /*<<< orphan*/  to_create_inferior; int /*<<< orphan*/  to_load; int /*<<< orphan*/  to_kill; int /*<<< orphan*/  to_remove_breakpoint; int /*<<< orphan*/  to_insert_breakpoint; int /*<<< orphan*/  to_files_info; int /*<<< orphan*/  to_xfer_memory; int /*<<< orphan*/  to_prepare_to_store; int /*<<< orphan*/  to_store_registers; int /*<<< orphan*/  to_fetch_registers; int /*<<< orphan*/  to_wait; int /*<<< orphan*/  to_resume; int /*<<< orphan*/  to_attach; int /*<<< orphan*/  to_close; int /*<<< orphan*/  to_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPS_MAGIC ; 
 int /*<<< orphan*/  generic_load ; 
 int /*<<< orphan*/  generic_mourn_inferior ; 
 int /*<<< orphan*/  process_stratum ; 
 int /*<<< orphan*/  remote_rdp_attach ; 
 int /*<<< orphan*/  remote_rdp_close ; 
 int /*<<< orphan*/  remote_rdp_create_inferior ; 
 int /*<<< orphan*/  remote_rdp_fetch_register ; 
 int /*<<< orphan*/  remote_rdp_files_info ; 
 int /*<<< orphan*/  remote_rdp_insert_breakpoint ; 
 int /*<<< orphan*/  remote_rdp_kill ; 
 int /*<<< orphan*/  remote_rdp_open ; 
 TYPE_1__ remote_rdp_ops ; 
 int /*<<< orphan*/  remote_rdp_prepare_to_store ; 
 int /*<<< orphan*/  remote_rdp_remove_breakpoint ; 
 int /*<<< orphan*/  remote_rdp_resume ; 
 int /*<<< orphan*/  remote_rdp_store_register ; 
 int /*<<< orphan*/  remote_rdp_wait ; 
 int /*<<< orphan*/  remote_rdp_xfer_inferior_memory ; 

__attribute__((used)) static void
init_remote_rdp_ops (void)
{
  remote_rdp_ops.to_shortname = "rdp";
  remote_rdp_ops.to_longname = "Remote Target using the RDProtocol";
  remote_rdp_ops.to_doc = "Use a remote ARM system which uses the ARM Remote Debugging Protocol";
  remote_rdp_ops.to_open = remote_rdp_open;
  remote_rdp_ops.to_close = remote_rdp_close;
  remote_rdp_ops.to_attach = remote_rdp_attach;
  remote_rdp_ops.to_resume = remote_rdp_resume;
  remote_rdp_ops.to_wait = remote_rdp_wait;
  remote_rdp_ops.to_fetch_registers = remote_rdp_fetch_register;
  remote_rdp_ops.to_store_registers = remote_rdp_store_register;
  remote_rdp_ops.to_prepare_to_store = remote_rdp_prepare_to_store;
  remote_rdp_ops.to_xfer_memory = remote_rdp_xfer_inferior_memory;
  remote_rdp_ops.to_files_info = remote_rdp_files_info;
  remote_rdp_ops.to_insert_breakpoint = remote_rdp_insert_breakpoint;
  remote_rdp_ops.to_remove_breakpoint = remote_rdp_remove_breakpoint;
  remote_rdp_ops.to_kill = remote_rdp_kill;
  remote_rdp_ops.to_load = generic_load;
  remote_rdp_ops.to_create_inferior = remote_rdp_create_inferior;
  remote_rdp_ops.to_mourn_inferior = generic_mourn_inferior;
  remote_rdp_ops.to_stratum = process_stratum;
  remote_rdp_ops.to_has_all_memory = 1;
  remote_rdp_ops.to_has_memory = 1;
  remote_rdp_ops.to_has_stack = 1;
  remote_rdp_ops.to_has_registers = 1;
  remote_rdp_ops.to_has_execution = 1;
  remote_rdp_ops.to_magic = OPS_MAGIC;
}