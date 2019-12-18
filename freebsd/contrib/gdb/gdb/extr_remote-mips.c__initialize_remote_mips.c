#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* to_longname; int to_has_all_memory; int to_has_memory; int to_has_stack; int to_has_registers; int to_has_execution; char* to_shortname; char* to_doc; void* to_wait; int /*<<< orphan*/  to_open; int /*<<< orphan*/  to_magic; int /*<<< orphan*/  to_stratum; int /*<<< orphan*/  to_mourn_inferior; int /*<<< orphan*/  to_create_inferior; int /*<<< orphan*/  to_load; int /*<<< orphan*/  to_kill; int /*<<< orphan*/  to_can_use_hw_breakpoint; int /*<<< orphan*/  to_stopped_by_watchpoint; int /*<<< orphan*/  to_remove_watchpoint; int /*<<< orphan*/  to_insert_watchpoint; int /*<<< orphan*/  to_remove_breakpoint; int /*<<< orphan*/  to_insert_breakpoint; int /*<<< orphan*/  to_files_info; int /*<<< orphan*/  to_xfer_memory; int /*<<< orphan*/  to_prepare_to_store; int /*<<< orphan*/  to_store_registers; int /*<<< orphan*/  to_fetch_registers; int /*<<< orphan*/  to_resume; int /*<<< orphan*/  to_detach; int /*<<< orphan*/  to_close; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPS_MAGIC ; 
 int /*<<< orphan*/  add_com (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_set_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_show_from_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_target (TYPE_1__*) ; 
 int /*<<< orphan*/  class_obscure ; 
 int /*<<< orphan*/  ddb_open ; 
 TYPE_1__ ddb_ops ; 
 int /*<<< orphan*/  lsi_open ; 
 TYPE_1__ lsi_ops ; 
 char mask_address_p ; 
 int /*<<< orphan*/  mips_can_use_watchpoint ; 
 int /*<<< orphan*/  mips_close ; 
 int /*<<< orphan*/  mips_create_inferior ; 
 int /*<<< orphan*/  mips_detach ; 
 int /*<<< orphan*/  mips_fetch_registers ; 
 int /*<<< orphan*/  mips_files_info ; 
 int /*<<< orphan*/  mips_insert_breakpoint ; 
 int /*<<< orphan*/  mips_insert_watchpoint ; 
 int /*<<< orphan*/  mips_kill ; 
 int /*<<< orphan*/  mips_load ; 
 int /*<<< orphan*/  mips_monitor_prompt ; 
 int /*<<< orphan*/  mips_mourn_inferior ; 
 int /*<<< orphan*/  mips_open ; 
 TYPE_1__ mips_ops ; 
 int /*<<< orphan*/  mips_prepare_to_store ; 
 int /*<<< orphan*/  mips_receive_wait ; 
 int /*<<< orphan*/  mips_remove_breakpoint ; 
 int /*<<< orphan*/  mips_remove_watchpoint ; 
 int /*<<< orphan*/  mips_resume ; 
 int /*<<< orphan*/  mips_retransmit_wait ; 
 int /*<<< orphan*/  mips_stopped_by_watchpoint ; 
 int /*<<< orphan*/  mips_store_registers ; 
 int /*<<< orphan*/  mips_syn_garbage ; 
 void* mips_wait ; 
 int /*<<< orphan*/  mips_xfer_memory ; 
 int /*<<< orphan*/  monitor_warnings ; 
 int /*<<< orphan*/  no_class ; 
 int /*<<< orphan*/  pmon_command ; 
 int /*<<< orphan*/  pmon_open ; 
 TYPE_1__ pmon_ops ; 
 int /*<<< orphan*/  process_stratum ; 
 int /*<<< orphan*/  setlist ; 
 int /*<<< orphan*/  showlist ; 
 int /*<<< orphan*/  var_boolean ; 
 int /*<<< orphan*/  var_string ; 
 int /*<<< orphan*/  var_zinteger ; 

void
_initialize_remote_mips (void)
{
  /* Initialize the fields in mips_ops that are common to all four targets.  */
  mips_ops.to_longname = "Remote MIPS debugging over serial line";
  mips_ops.to_close = mips_close;
  mips_ops.to_detach = mips_detach;
  mips_ops.to_resume = mips_resume;
  mips_ops.to_fetch_registers = mips_fetch_registers;
  mips_ops.to_store_registers = mips_store_registers;
  mips_ops.to_prepare_to_store = mips_prepare_to_store;
  mips_ops.to_xfer_memory = mips_xfer_memory;
  mips_ops.to_files_info = mips_files_info;
  mips_ops.to_insert_breakpoint = mips_insert_breakpoint;
  mips_ops.to_remove_breakpoint = mips_remove_breakpoint;
  mips_ops.to_insert_watchpoint = mips_insert_watchpoint;
  mips_ops.to_remove_watchpoint = mips_remove_watchpoint;
  mips_ops.to_stopped_by_watchpoint = mips_stopped_by_watchpoint;
  mips_ops.to_can_use_hw_breakpoint = mips_can_use_watchpoint;
  mips_ops.to_kill = mips_kill;
  mips_ops.to_load = mips_load;
  mips_ops.to_create_inferior = mips_create_inferior;
  mips_ops.to_mourn_inferior = mips_mourn_inferior;
  mips_ops.to_stratum = process_stratum;
  mips_ops.to_has_all_memory = 1;
  mips_ops.to_has_memory = 1;
  mips_ops.to_has_stack = 1;
  mips_ops.to_has_registers = 1;
  mips_ops.to_has_execution = 1;
  mips_ops.to_magic = OPS_MAGIC;

  /* Copy the common fields to all four target vectors.  */
  pmon_ops = ddb_ops = lsi_ops = mips_ops;

  /* Initialize target-specific fields in the target vectors.  */
  mips_ops.to_shortname = "mips";
  mips_ops.to_doc = "\
Debug a board using the MIPS remote debugging protocol over a serial line.\n\
The argument is the device it is connected to or, if it contains a colon,\n\
HOST:PORT to access a board over a network";
  mips_ops.to_open = mips_open;
  mips_ops.to_wait = mips_wait;

  pmon_ops.to_shortname = "pmon";
  pmon_ops.to_doc = "\
Debug a board using the PMON MIPS remote debugging protocol over a serial\n\
line. The argument is the device it is connected to or, if it contains a\n\
colon, HOST:PORT to access a board over a network";
  pmon_ops.to_open = pmon_open;
  pmon_ops.to_wait = mips_wait;

  ddb_ops.to_shortname = "ddb";
  ddb_ops.to_doc = "\
Debug a board using the PMON MIPS remote debugging protocol over a serial\n\
line. The first argument is the device it is connected to or, if it contains\n\
a colon, HOST:PORT to access a board over a network.  The optional second\n\
parameter is the temporary file in the form HOST:FILENAME to be used for\n\
TFTP downloads to the board.  The optional third parameter is the local name\n\
of the TFTP temporary file, if it differs from the filename seen by the board.";
  ddb_ops.to_open = ddb_open;
  ddb_ops.to_wait = mips_wait;

  lsi_ops.to_shortname = "lsi";
  lsi_ops.to_doc = pmon_ops.to_doc;
  lsi_ops.to_open = lsi_open;
  lsi_ops.to_wait = mips_wait;

  /* Add the targets.  */
  add_target (&mips_ops);
  add_target (&pmon_ops);
  add_target (&ddb_ops);
  add_target (&lsi_ops);

  add_show_from_set (
		      add_set_cmd ("timeout", no_class, var_zinteger,
				   (char *) &mips_receive_wait,
		       "Set timeout in seconds for remote MIPS serial I/O.",
				   &setlist),
		      &showlist);

  add_show_from_set (
		  add_set_cmd ("retransmit-timeout", no_class, var_zinteger,
			       (char *) &mips_retransmit_wait,
			       "Set retransmit timeout in seconds for remote MIPS serial I/O.\n\
This is the number of seconds to wait for an acknowledgement to a packet\n\
before resending the packet.", &setlist),
		      &showlist);

  add_show_from_set (
		   add_set_cmd ("syn-garbage-limit", no_class, var_zinteger,
				(char *) &mips_syn_garbage,
				"Set the maximum number of characters to ignore when scanning for a SYN.\n\
This is the maximum number of characters GDB will ignore when trying to\n\
synchronize with the remote system.  A value of -1 means that there is no limit\n\
(Note that these characters are printed out even though they are ignored.)",
				&setlist),
		      &showlist);

  add_show_from_set
    (add_set_cmd ("monitor-prompt", class_obscure, var_string,
		  (char *) &mips_monitor_prompt,
		  "Set the prompt that GDB expects from the monitor.",
		  &setlist),
     &showlist);

  add_show_from_set (
	       add_set_cmd ("monitor-warnings", class_obscure, var_zinteger,
			    (char *) &monitor_warnings,
			    "Set printing of monitor warnings.\n"
		"When enabled, monitor warnings about hardware breakpoints "
			    "will be displayed.",
			    &setlist),
		      &showlist);

  add_com ("pmon <command>", class_obscure, pmon_command,
	   "Send a packet to PMON (must be in debug mode).");

  add_show_from_set (add_set_cmd ("mask-address", no_class,
				  var_boolean, &mask_address_p,
				  "Set zeroing of upper 32 bits of 64-bit addresses when talking to PMON targets.\n\
Use \"on\" to enable the masking and \"off\" to disable it.\n",
				  &setlist),
		     &showlist);
}