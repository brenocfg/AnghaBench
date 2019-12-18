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
struct TYPE_2__ {char* to_shortname; char* to_longname; char* to_doc; int to_has_all_memory; int to_has_memory; int to_has_stack; int to_has_registers; int to_has_execution; int /*<<< orphan*/  to_magic; int /*<<< orphan*/  to_stratum; int /*<<< orphan*/  to_mourn_inferior; int /*<<< orphan*/  to_create_inferior; int /*<<< orphan*/  to_load; int /*<<< orphan*/  to_kill; int /*<<< orphan*/  to_remove_breakpoint; int /*<<< orphan*/  to_insert_breakpoint; int /*<<< orphan*/  to_files_info; int /*<<< orphan*/  to_xfer_memory; int /*<<< orphan*/  to_prepare_to_store; int /*<<< orphan*/  to_store_registers; int /*<<< orphan*/  to_fetch_registers; int /*<<< orphan*/  to_wait; int /*<<< orphan*/  to_resume; int /*<<< orphan*/  to_detach; int /*<<< orphan*/  to_close; int /*<<< orphan*/  to_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPS_MAGIC ; 
 int /*<<< orphan*/  process_stratum ; 
 int /*<<< orphan*/  sds_close ; 
 int /*<<< orphan*/  sds_create_inferior ; 
 int /*<<< orphan*/  sds_detach ; 
 int /*<<< orphan*/  sds_fetch_registers ; 
 int /*<<< orphan*/  sds_files_info ; 
 int /*<<< orphan*/  sds_insert_breakpoint ; 
 int /*<<< orphan*/  sds_kill ; 
 int /*<<< orphan*/  sds_load ; 
 int /*<<< orphan*/  sds_mourn ; 
 int /*<<< orphan*/  sds_open ; 
 TYPE_1__ sds_ops ; 
 int /*<<< orphan*/  sds_prepare_to_store ; 
 int /*<<< orphan*/  sds_remove_breakpoint ; 
 int /*<<< orphan*/  sds_resume ; 
 int /*<<< orphan*/  sds_store_registers ; 
 int /*<<< orphan*/  sds_wait ; 
 int /*<<< orphan*/  sds_xfer_memory ; 

__attribute__((used)) static void
init_sds_ops (void)
{
  sds_ops.to_shortname = "sds";
  sds_ops.to_longname = "Remote serial target with SDS protocol";
  sds_ops.to_doc = "Use a remote computer via a serial line; using the SDS protocol.\n\
Specify the serial device it is connected to (e.g. /dev/ttya).";
  sds_ops.to_open = sds_open;
  sds_ops.to_close = sds_close;
  sds_ops.to_detach = sds_detach;
  sds_ops.to_resume = sds_resume;
  sds_ops.to_wait = sds_wait;
  sds_ops.to_fetch_registers = sds_fetch_registers;
  sds_ops.to_store_registers = sds_store_registers;
  sds_ops.to_prepare_to_store = sds_prepare_to_store;
  sds_ops.to_xfer_memory = sds_xfer_memory;
  sds_ops.to_files_info = sds_files_info;
  sds_ops.to_insert_breakpoint = sds_insert_breakpoint;
  sds_ops.to_remove_breakpoint = sds_remove_breakpoint;
  sds_ops.to_kill = sds_kill;
  sds_ops.to_load = sds_load;
  sds_ops.to_create_inferior = sds_create_inferior;
  sds_ops.to_mourn_inferior = sds_mourn;
  sds_ops.to_stratum = process_stratum;
  sds_ops.to_has_all_memory = 1;
  sds_ops.to_has_memory = 1;
  sds_ops.to_has_stack = 1;
  sds_ops.to_has_registers = 1;
  sds_ops.to_has_execution = 1;
  sds_ops.to_magic = OPS_MAGIC;
}