#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* cmd; char* resp_delim; char* term; char* term_cmd; } ;
struct TYPE_8__ {char* cmd; int /*<<< orphan*/ * term_cmd; int /*<<< orphan*/ * term; int /*<<< orphan*/ * resp_delim; } ;
struct TYPE_7__ {char* cmdb; char* cmdw; char* resp_delim; char* term; char* term_cmd; int /*<<< orphan*/ * cmdll; int /*<<< orphan*/ * cmdl; } ;
struct TYPE_6__ {char* cmdb; char* cmdw; int /*<<< orphan*/ * term_cmd; int /*<<< orphan*/ * term; int /*<<< orphan*/ * resp_delim; int /*<<< orphan*/ * cmdll; int /*<<< orphan*/ * cmdl; } ;
struct TYPE_10__ {int flags; char* cont; char* step; char* stop; char* set_break; char* clr_break; char* clr_all_break; char* fill; char* dump_registers; char* register_pattern; char* load; char* prompt; char* line_term; int /*<<< orphan*/  magic; int /*<<< orphan*/  regnames; int /*<<< orphan*/  stopbits; int /*<<< orphan*/ * target; int /*<<< orphan*/ * cmd_end; int /*<<< orphan*/ * loadresp; int /*<<< orphan*/ * load_routine; int /*<<< orphan*/  supply_register; TYPE_4__ getreg; TYPE_3__ setreg; TYPE_2__ getmem; TYPE_1__ setmem; int /*<<< orphan*/  init; } ;

/* Variables and functions */
 int /*<<< orphan*/  MONITOR_OPS_MAGIC ; 
 int MO_CLR_BREAK_USES_ADDR ; 
 int MO_FILL_USES_ADDR ; 
 int MO_GETMEM_NEEDS_RANGE ; 
 int /*<<< orphan*/  SERIAL_1_STOPBITS ; 
 TYPE_5__ hms_cmds ; 
 int /*<<< orphan*/  hms_inits ; 
 int /*<<< orphan*/  hms_ops ; 
 int /*<<< orphan*/  hms_regnames ; 
 int /*<<< orphan*/  hms_supply_register ; 

__attribute__((used)) static void
init_hms_cmds (void)
{
  hms_cmds.flags = MO_CLR_BREAK_USES_ADDR | MO_FILL_USES_ADDR | MO_GETMEM_NEEDS_RANGE;
  hms_cmds.init = hms_inits;	/* Init strings */
  hms_cmds.cont = "g\r";	/* continue command */
  hms_cmds.step = "s\r";	/* single step */
  hms_cmds.stop = "\003";	/* ^C interrupts the program */
  hms_cmds.set_break = "b %x\r";	/* set a breakpoint */
  hms_cmds.clr_break = "b - %x\r";	/* clear a breakpoint */
  hms_cmds.clr_all_break = "b -\r";	/* clear all breakpoints */
  hms_cmds.fill = "f %x %x %x\r";	/* fill (start end val) */
  hms_cmds.setmem.cmdb = "m.b %x=%x\r";		/* setmem.cmdb (addr, value) */
  hms_cmds.setmem.cmdw = "m.w %x=%x\r";		/* setmem.cmdw (addr, value) */
  hms_cmds.setmem.cmdl = NULL;	/* setmem.cmdl (addr, value) */
  hms_cmds.setmem.cmdll = NULL;	/* setmem.cmdll (addr, value) */
  hms_cmds.setmem.resp_delim = NULL;	/* setreg.resp_delim */
  hms_cmds.setmem.term = NULL;	/* setreg.term */
  hms_cmds.setmem.term_cmd = NULL;	/* setreg.term_cmd */
  hms_cmds.getmem.cmdb = "m.b %x %x\r";		/* getmem.cmdb (addr, addr) */
  hms_cmds.getmem.cmdw = "m.w %x %x\r";		/* getmem.cmdw (addr, addr) */
  hms_cmds.getmem.cmdl = NULL;	/* getmem.cmdl (addr, addr) */
  hms_cmds.getmem.cmdll = NULL;	/* getmem.cmdll (addr, addr) */
  hms_cmds.getmem.resp_delim = ": ";	/* getmem.resp_delim */
  hms_cmds.getmem.term = ">";	/* getmem.term */
  hms_cmds.getmem.term_cmd = "\003";	/* getmem.term_cmd */
  hms_cmds.setreg.cmd = "r %s=%x\r";	/* setreg.cmd (name, value) */
  hms_cmds.setreg.resp_delim = NULL;	/* setreg.resp_delim */
  hms_cmds.setreg.term = NULL;	/* setreg.term */
  hms_cmds.setreg.term_cmd = NULL;	/* setreg.term_cmd */
  hms_cmds.getreg.cmd = "r %s\r";	/* getreg.cmd (name) */
  hms_cmds.getreg.resp_delim = " (";	/* getreg.resp_delim */
  hms_cmds.getreg.term = ":";	/* getreg.term */
  hms_cmds.getreg.term_cmd = "\003";	/* getreg.term_cmd */
  hms_cmds.dump_registers = "r\r";	/* dump_registers */
  hms_cmds.register_pattern = "\\(\\w+\\)=\\([0-9a-fA-F]+\\)";	/* register_pattern */
  hms_cmds.supply_register = hms_supply_register;	/* supply_register */
  hms_cmds.load_routine = NULL;	/* load_routine (defaults to SRECs) */
  hms_cmds.load = "tl\r";	/* download command */
  hms_cmds.loadresp = NULL;	/* load response */
  hms_cmds.prompt = ">";	/* monitor command prompt */
  hms_cmds.line_term = "\r";	/* end-of-command delimitor */
  hms_cmds.cmd_end = NULL;	/* optional command terminator */
  hms_cmds.target = &hms_ops;	/* target operations */
  hms_cmds.stopbits = SERIAL_1_STOPBITS;	/* number of stop bits */
  hms_cmds.regnames = hms_regnames;	/* registers names */
  hms_cmds.magic = MONITOR_OPS_MAGIC;	/* magic */
}