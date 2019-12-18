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
struct TYPE_2__ {char* to_shortname; char* to_longname; char* to_doc; int to_has_all_memory; int to_has_memory; int /*<<< orphan*/  to_magic; int /*<<< orphan*/  to_stratum; int /*<<< orphan*/  to_create_inferior; int /*<<< orphan*/  to_lookup_symbol; int /*<<< orphan*/  to_load; int /*<<< orphan*/  to_files_info; int /*<<< orphan*/  to_xfer_memory; int /*<<< orphan*/  to_attach; int /*<<< orphan*/  to_close; int /*<<< orphan*/  to_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPS_MAGIC ; 
 int /*<<< orphan*/  core_stratum ; 
 int /*<<< orphan*/  vx_attach ; 
 int /*<<< orphan*/  vx_close ; 
 int /*<<< orphan*/  vx_create_inferior ; 
 int /*<<< orphan*/  vx_files_info ; 
 int /*<<< orphan*/  vx_load_command ; 
 int /*<<< orphan*/  vx_lookup_symbol ; 
 int /*<<< orphan*/  vx_open ; 
 TYPE_1__ vx_ops ; 
 int /*<<< orphan*/  vx_xfer_memory ; 

__attribute__((used)) static void
init_vx_ops (void)
{
  vx_ops.to_shortname = "vxworks";
  vx_ops.to_longname = "VxWorks target memory via RPC over TCP/IP";
  vx_ops.to_doc = "Use VxWorks target memory.  \n\
Specify the name of the machine to connect to.";
  vx_ops.to_open = vx_open;
  vx_ops.to_close = vx_close;
  vx_ops.to_attach = vx_attach;
  vx_ops.to_xfer_memory = vx_xfer_memory;
  vx_ops.to_files_info = vx_files_info;
  vx_ops.to_load = vx_load_command;
  vx_ops.to_lookup_symbol = vx_lookup_symbol;
  vx_ops.to_create_inferior = vx_create_inferior;
  vx_ops.to_stratum = core_stratum;
  vx_ops.to_has_all_memory = 1;
  vx_ops.to_has_memory = 1;
  vx_ops.to_magic = OPS_MAGIC;	/* Always the last thing */
}