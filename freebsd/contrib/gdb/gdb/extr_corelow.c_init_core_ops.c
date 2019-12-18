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
struct TYPE_2__ {char* to_shortname; char* to_longname; char* to_doc; int to_has_memory; int to_has_stack; int to_has_registers; int /*<<< orphan*/  to_magic; int /*<<< orphan*/  to_stratum; int /*<<< orphan*/  to_thread_alive; int /*<<< orphan*/  to_create_inferior; void* to_remove_breakpoint; void* to_insert_breakpoint; int /*<<< orphan*/  to_files_info; int /*<<< orphan*/  to_xfer_memory; int /*<<< orphan*/  to_xfer_partial; int /*<<< orphan*/  to_fetch_registers; int /*<<< orphan*/  to_detach; int /*<<< orphan*/  to_attach; int /*<<< orphan*/  to_close; int /*<<< orphan*/  to_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPS_MAGIC ; 
 int /*<<< orphan*/  core_close ; 
 int /*<<< orphan*/  core_detach ; 
 int /*<<< orphan*/  core_file_thread_alive ; 
 int /*<<< orphan*/  core_files_info ; 
 int /*<<< orphan*/  core_open ; 
 TYPE_1__ core_ops ; 
 int /*<<< orphan*/  core_stratum ; 
 int /*<<< orphan*/  core_xfer_partial ; 
 int /*<<< orphan*/  find_default_attach ; 
 int /*<<< orphan*/  find_default_create_inferior ; 
 int /*<<< orphan*/  get_core_registers ; 
 void* ignore ; 
 int /*<<< orphan*/  xfer_memory ; 

__attribute__((used)) static void
init_core_ops (void)
{
  core_ops.to_shortname = "core";
  core_ops.to_longname = "Local core dump file";
  core_ops.to_doc =
    "Use a core file as a target.  Specify the filename of the core file.";
  core_ops.to_open = core_open;
  core_ops.to_close = core_close;
  core_ops.to_attach = find_default_attach;
  core_ops.to_detach = core_detach;
  core_ops.to_fetch_registers = get_core_registers;
  core_ops.to_xfer_partial = core_xfer_partial;
  core_ops.to_xfer_memory = xfer_memory;
  core_ops.to_files_info = core_files_info;
  core_ops.to_insert_breakpoint = ignore;
  core_ops.to_remove_breakpoint = ignore;
  core_ops.to_create_inferior = find_default_create_inferior;
  core_ops.to_thread_alive = core_file_thread_alive;
  core_ops.to_stratum = core_stratum;
  core_ops.to_has_memory = 1;
  core_ops.to_has_stack = 1;
  core_ops.to_has_registers = 1;
  core_ops.to_magic = OPS_MAGIC;
}