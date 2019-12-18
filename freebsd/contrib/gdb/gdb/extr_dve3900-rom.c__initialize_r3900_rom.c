#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {char* cmd; char* resp_delim; char* term; char* term_cmd; } ;
struct TYPE_11__ {char* cmd; } ;
struct TYPE_10__ {char* cmdb; char* cmdw; char* cmdl; char* resp_delim; char* term; char* term_cmd; } ;
struct TYPE_9__ {char* cmdb; char* cmdw; char* cmdl; } ;
struct TYPE_14__ {int flags; char* cont; char* step; char* set_break; char* clr_break; char* fill; char* dump_registers; char* register_pattern; char* load; char* prompt; char* line_term; int /*<<< orphan*/  magic; int /*<<< orphan*/  regnames; int /*<<< orphan*/  stopbits; TYPE_5__* target; int /*<<< orphan*/  supply_register; TYPE_4__ getreg; TYPE_3__ setreg; TYPE_2__ getmem; TYPE_1__ setmem; int /*<<< orphan*/  init; } ;
struct TYPE_13__ {char* to_shortname; char* to_longname; char* to_doc; int /*<<< orphan*/  to_load; int /*<<< orphan*/  to_store_registers; int /*<<< orphan*/  to_fetch_registers; int /*<<< orphan*/  to_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  MONITOR_OPS_MAGIC ; 
 int MO_ADDR_BITS_REMOVE ; 
 int MO_CLR_BREAK_USES_ADDR ; 
 int MO_GETMEM_READ_SINGLE ; 
 int MO_NO_ECHO_ON_OPEN ; 
 int MO_PRINT_PROGRAM_OUTPUT ; 
 int /*<<< orphan*/  SERIAL_1_STOPBITS ; 
 int /*<<< orphan*/  add_target (TYPE_5__*) ; 
 int /*<<< orphan*/  dummy_inits ; 
 int /*<<< orphan*/  init_monitor_ops (TYPE_5__*) ; 
 int /*<<< orphan*/  orig_monitor_fetch_registers ; 
 int /*<<< orphan*/  orig_monitor_load ; 
 int /*<<< orphan*/  orig_monitor_store_registers ; 
 TYPE_6__ r3900_cmds ; 
 int /*<<< orphan*/  r3900_fetch_registers ; 
 int /*<<< orphan*/  r3900_load ; 
 int /*<<< orphan*/  r3900_open ; 
 TYPE_5__ r3900_ops ; 
 int /*<<< orphan*/  r3900_regnames ; 
 int /*<<< orphan*/  r3900_store_registers ; 
 int /*<<< orphan*/  r3900_supply_register ; 

void
_initialize_r3900_rom (void)
{
  r3900_cmds.flags = MO_NO_ECHO_ON_OPEN |
    MO_ADDR_BITS_REMOVE |
    MO_CLR_BREAK_USES_ADDR |
    MO_GETMEM_READ_SINGLE |
    MO_PRINT_PROGRAM_OUTPUT;

  r3900_cmds.init = dummy_inits;
  r3900_cmds.cont = "g\r";
  r3900_cmds.step = "t\r";
  r3900_cmds.set_break = "b %A\r";	/* COREADDR */
  r3900_cmds.clr_break = "b %A,0\r";	/* COREADDR */
  r3900_cmds.fill = "fx %A s %x %x\r";	/* COREADDR, len, val */

  r3900_cmds.setmem.cmdb = "sx %A %x\r";	/* COREADDR, val */
  r3900_cmds.setmem.cmdw = "sh %A %x\r";	/* COREADDR, val */
  r3900_cmds.setmem.cmdl = "sw %A %x\r";	/* COREADDR, val */

  r3900_cmds.getmem.cmdb = "sx %A\r";	/* COREADDR */
  r3900_cmds.getmem.cmdw = "sh %A\r";	/* COREADDR */
  r3900_cmds.getmem.cmdl = "sw %A\r";	/* COREADDR */
  r3900_cmds.getmem.resp_delim = " : ";
  r3900_cmds.getmem.term = " ";
  r3900_cmds.getmem.term_cmd = ".\r";

  r3900_cmds.setreg.cmd = "x%s %x\r";	/* regname, val */

  r3900_cmds.getreg.cmd = "x%s\r";	/* regname */
  r3900_cmds.getreg.resp_delim = "=";
  r3900_cmds.getreg.term = " ";
  r3900_cmds.getreg.term_cmd = ".\r";

  r3900_cmds.dump_registers = "x\r";
  r3900_cmds.register_pattern =
    "\\([a-zA-Z0-9_]+\\) *=\\([0-9a-f]+ [0-9a-f]+\\b\\)";
  r3900_cmds.supply_register = r3900_supply_register;
  /* S-record download, via "keyboard port".  */
  r3900_cmds.load = "r0\r";
  r3900_cmds.prompt = "#";
  r3900_cmds.line_term = "\r";
  r3900_cmds.target = &r3900_ops;
  r3900_cmds.stopbits = SERIAL_1_STOPBITS;
  r3900_cmds.regnames = r3900_regnames;
  r3900_cmds.magic = MONITOR_OPS_MAGIC;

  init_monitor_ops (&r3900_ops);

  r3900_ops.to_shortname = "r3900";
  r3900_ops.to_longname = "R3900 monitor";
  r3900_ops.to_doc = "Debug using the DVE R3900 monitor.\n\
Specify the serial device it is connected to (e.g. /dev/ttya).";
  r3900_ops.to_open = r3900_open;

  /* Override the functions to fetch and store registers.  But save the
     addresses of the default functions, because we will use those functions
     for "normal" registers.  */

  orig_monitor_fetch_registers = r3900_ops.to_fetch_registers;
  orig_monitor_store_registers = r3900_ops.to_store_registers;
  r3900_ops.to_fetch_registers = r3900_fetch_registers;
  r3900_ops.to_store_registers = r3900_store_registers;

  /* Override the load function, but save the address of the default
     function to use when loading S-records over a serial link.  */
  orig_monitor_load = r3900_ops.to_load;
  r3900_ops.to_load = r3900_load;

  add_target (&r3900_ops);
}