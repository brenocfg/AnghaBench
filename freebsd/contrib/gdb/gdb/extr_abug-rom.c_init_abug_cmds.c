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
struct TYPE_8__ {char* cmd; char* resp_delim; char* term; char* term_cmd; } ;
struct TYPE_7__ {char* cmdb; char* cmdw; char* cmdl; char* resp_delim; int /*<<< orphan*/ * term_cmd; int /*<<< orphan*/ * term; int /*<<< orphan*/ * cmdll; } ;
struct TYPE_6__ {char* cmdb; char* cmdw; char* cmdl; int /*<<< orphan*/ * term_cmd; int /*<<< orphan*/ * term; int /*<<< orphan*/ * resp_delim; int /*<<< orphan*/ * cmdll; } ;
struct TYPE_10__ {char* cont; char* step; char* set_break; char* clr_break; char* clr_all_break; char* fill; char* dump_registers; char* register_pattern; char* load; char* loadresp; char* prompt; char* line_term; int /*<<< orphan*/  magic; int /*<<< orphan*/  regname; int /*<<< orphan*/ * regnames; int /*<<< orphan*/  stopbits; int /*<<< orphan*/ * target; int /*<<< orphan*/ * cmd_end; int /*<<< orphan*/ * load_routine; int /*<<< orphan*/  supply_register; TYPE_4__ getreg; TYPE_3__ setreg; TYPE_2__ getmem; TYPE_1__ setmem; int /*<<< orphan*/ * stop; int /*<<< orphan*/  init; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MONITOR_OPS_MAGIC ; 
 int /*<<< orphan*/  MO_CLR_BREAK_USES_ADDR ; 
 int /*<<< orphan*/  SERIAL_1_STOPBITS ; 
 TYPE_5__ abug_cmds ; 
 int /*<<< orphan*/  abug_inits ; 
 int /*<<< orphan*/  abug_ops ; 
 int /*<<< orphan*/  abug_regname ; 
 int /*<<< orphan*/  abug_supply_register ; 

__attribute__((used)) static void
init_abug_cmds (void)
{
  abug_cmds.flags = MO_CLR_BREAK_USES_ADDR;
  abug_cmds.init = abug_inits;	/* Init strings */
  abug_cmds.cont = "g\r";	/* continue command */
  abug_cmds.step = "t\r";	/* single step */
  abug_cmds.stop = NULL;	/* interrupt command */
  abug_cmds.set_break = "br %x\r";	/* set a breakpoint */
  abug_cmds.clr_break = "nobr %x\r";	/* clear a breakpoint */
  abug_cmds.clr_all_break = "nobr\r";	/* clear all breakpoints */
  abug_cmds.fill = "bf %x:%x %x;b\r";	/* fill (start count val) */
  abug_cmds.setmem.cmdb = "ms %x %02x\r";	/* setmem.cmdb (addr, value) */
  abug_cmds.setmem.cmdw = "ms %x %04x\r";	/* setmem.cmdw (addr, value) */
  abug_cmds.setmem.cmdl = "ms %x %08x\r";	/* setmem.cmdl (addr, value) */
  abug_cmds.setmem.cmdll = NULL;	/* setmem.cmdll (addr, value) */
  abug_cmds.setmem.resp_delim = NULL;	/* setreg.resp_delim */
  abug_cmds.setmem.term = NULL;	/* setreg.term */
  abug_cmds.setmem.term_cmd = NULL;	/* setreg.term_cmd */
  abug_cmds.getmem.cmdb = "md %x:%x;b\r";	/* getmem.cmdb (addr, len) */
  abug_cmds.getmem.cmdw = "md %x:%x;b\r";	/* getmem.cmdw (addr, len) */
  abug_cmds.getmem.cmdl = "md %x:%x;b\r";	/* getmem.cmdl (addr, len) */
  abug_cmds.getmem.cmdll = NULL;	/* getmem.cmdll (addr, len) */
  abug_cmds.getmem.resp_delim = " ";	/* getmem.resp_delim */
  abug_cmds.getmem.term = NULL;	/* getmem.term */
  abug_cmds.getmem.term_cmd = NULL;	/* getmem.term_cmd */
  abug_cmds.setreg.cmd = "rm %s %x\r";	/* setreg.cmd (name, value) */
  abug_cmds.setreg.resp_delim = "=";	/* setreg.resp_delim */
  abug_cmds.setreg.term = "? ";	/* setreg.term */
  abug_cmds.setreg.term_cmd = ".\r";	/* setreg.term_cmd */
  abug_cmds.getreg.cmd = "rm %s\r";	/* getreg.cmd (name) */
  abug_cmds.getreg.resp_delim = "=";	/* getreg.resp_delim */
  abug_cmds.getreg.term = "? ";	/* getreg.term */
  abug_cmds.getreg.term_cmd = ".\r";	/* getreg.term_cmd */
  abug_cmds.dump_registers = "rd\r";	/* dump_registers */
  abug_cmds.register_pattern = "\\(\\w+\\) +=\\([0-9a-fA-F]+\\b\\)";	/* register_pattern */
  abug_cmds.supply_register = abug_supply_register;	/* supply_register */
  abug_cmds.load_routine = NULL;	/* load_routine (defaults to SRECs) */
  abug_cmds.load = "lo 0\r";	/* download command */
  abug_cmds.loadresp = "\n";	/* load response */
  abug_cmds.prompt = "135Bug>";	/* monitor command prompt */
  abug_cmds.line_term = "\r";	/* end-of-line terminator */
  abug_cmds.cmd_end = NULL;	/* optional command terminator */
  abug_cmds.target = &abug_ops;	/* target operations */
  abug_cmds.stopbits = SERIAL_1_STOPBITS;	/* number of stop bits */
  abug_cmds.regnames = NULL;	/* registers names */
  abug_cmds.regname = abug_regname;
  abug_cmds.magic = MONITOR_OPS_MAGIC;	/* magic */
}