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
struct TYPE_2__ {char* to_shortname; char* to_longname; char* to_doc; int to_has_memory; int /*<<< orphan*/  to_magic; int /*<<< orphan*/  to_make_corefile_notes; int /*<<< orphan*/  to_stratum; int /*<<< orphan*/  to_create_inferior; void* to_remove_breakpoint; void* to_insert_breakpoint; int /*<<< orphan*/  to_files_info; int /*<<< orphan*/  to_xfer_memory; int /*<<< orphan*/  to_attach; int /*<<< orphan*/  to_close; int /*<<< orphan*/  to_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPS_MAGIC ; 
 int /*<<< orphan*/  exec_close ; 
 int /*<<< orphan*/  exec_files_info ; 
 int /*<<< orphan*/  exec_make_note_section ; 
 int /*<<< orphan*/  exec_open ; 
 TYPE_1__ exec_ops ; 
 int /*<<< orphan*/  file_stratum ; 
 int /*<<< orphan*/  find_default_attach ; 
 int /*<<< orphan*/  find_default_create_inferior ; 
 void* ignore ; 
 int /*<<< orphan*/  xfer_memory ; 

__attribute__((used)) static void
init_exec_ops (void)
{
  exec_ops.to_shortname = "exec";
  exec_ops.to_longname = "Local exec file";
  exec_ops.to_doc = "Use an executable file as a target.\n\
Specify the filename of the executable file.";
  exec_ops.to_open = exec_open;
  exec_ops.to_close = exec_close;
  exec_ops.to_attach = find_default_attach;
  exec_ops.to_xfer_memory = xfer_memory;
  exec_ops.to_files_info = exec_files_info;
  exec_ops.to_insert_breakpoint = ignore;
  exec_ops.to_remove_breakpoint = ignore;
  exec_ops.to_create_inferior = find_default_create_inferior;
  exec_ops.to_stratum = file_stratum;
  exec_ops.to_has_memory = 1;
  exec_ops.to_make_corefile_notes = exec_make_note_section;
  exec_ops.to_magic = OPS_MAGIC;
}