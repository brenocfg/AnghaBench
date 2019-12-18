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
struct TYPE_2__ {char* to_shortname; char* to_longname; char* to_doc; int to_has_all_memory; int to_has_memory; int to_has_stack; int to_has_registers; int to_has_execution; int /*<<< orphan*/  to_magic; int /*<<< orphan*/  to_stratum; int /*<<< orphan*/  to_stop; int /*<<< orphan*/  to_mourn_inferior; int /*<<< orphan*/  to_create_inferior; int /*<<< orphan*/  to_load; int /*<<< orphan*/  to_kill; int /*<<< orphan*/  to_remove_breakpoint; int /*<<< orphan*/  to_insert_breakpoint; int /*<<< orphan*/  to_files_info; int /*<<< orphan*/  to_xfer_memory; int /*<<< orphan*/  to_prepare_to_store; int /*<<< orphan*/  to_store_registers; int /*<<< orphan*/  to_fetch_registers; int /*<<< orphan*/  to_wait; int /*<<< orphan*/  to_resume; int /*<<< orphan*/  to_detach; int /*<<< orphan*/  to_close; int /*<<< orphan*/  to_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPS_MAGIC ; 
 int /*<<< orphan*/  e7000_close ; 
 int /*<<< orphan*/  e7000_create_inferior ; 
 int /*<<< orphan*/  e7000_detach ; 
 int /*<<< orphan*/  e7000_fetch_register ; 
 int /*<<< orphan*/  e7000_files_info ; 
 int /*<<< orphan*/  e7000_insert_breakpoint ; 
 int /*<<< orphan*/  e7000_kill ; 
 int /*<<< orphan*/  e7000_load ; 
 int /*<<< orphan*/  e7000_mourn_inferior ; 
 int /*<<< orphan*/  e7000_open ; 
 TYPE_1__ e7000_ops ; 
 int /*<<< orphan*/  e7000_prepare_to_store ; 
 int /*<<< orphan*/  e7000_remove_breakpoint ; 
 int /*<<< orphan*/  e7000_resume ; 
 int /*<<< orphan*/  e7000_stop ; 
 int /*<<< orphan*/  e7000_store_register ; 
 int /*<<< orphan*/  e7000_wait ; 
 int /*<<< orphan*/  e7000_xfer_inferior_memory ; 
 int /*<<< orphan*/  process_stratum ; 

__attribute__((used)) static void
init_e7000_ops (void)
{
  e7000_ops.to_shortname = "e7000";
  e7000_ops.to_longname = "Remote Renesas e7000 target";
  e7000_ops.to_doc = "Use a remote Renesas e7000 ICE connected by a serial line;\n\
or a network connection.\n\
Arguments are the name of the device for the serial line,\n\
the speed to connect at in bits per second.\n\
eg\n\
target e7000 /dev/ttya 9600\n\
target e7000 foobar";
  e7000_ops.to_open = e7000_open;
  e7000_ops.to_close = e7000_close;
  e7000_ops.to_detach = e7000_detach;
  e7000_ops.to_resume = e7000_resume;
  e7000_ops.to_wait = e7000_wait;
  e7000_ops.to_fetch_registers = e7000_fetch_register;
  e7000_ops.to_store_registers = e7000_store_register;
  e7000_ops.to_prepare_to_store = e7000_prepare_to_store;
  e7000_ops.to_xfer_memory = e7000_xfer_inferior_memory;
  e7000_ops.to_files_info = e7000_files_info;
  e7000_ops.to_insert_breakpoint = e7000_insert_breakpoint;
  e7000_ops.to_remove_breakpoint = e7000_remove_breakpoint;
  e7000_ops.to_kill = e7000_kill;
  e7000_ops.to_load = e7000_load;
  e7000_ops.to_create_inferior = e7000_create_inferior;
  e7000_ops.to_mourn_inferior = e7000_mourn_inferior;
  e7000_ops.to_stop = e7000_stop;
  e7000_ops.to_stratum = process_stratum;
  e7000_ops.to_has_all_memory = 1;
  e7000_ops.to_has_memory = 1;
  e7000_ops.to_has_stack = 1;
  e7000_ops.to_has_registers = 1;
  e7000_ops.to_has_execution = 1;
  e7000_ops.to_magic = OPS_MAGIC;
}