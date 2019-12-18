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
struct TYPE_9__ {char* cmd; char* resp_delim; int /*<<< orphan*/ * term_cmd; int /*<<< orphan*/ * term; } ;
struct TYPE_8__ {char* cmd; int /*<<< orphan*/ * term_cmd; int /*<<< orphan*/ * term; int /*<<< orphan*/ * resp_delim; } ;
struct TYPE_7__ {char* cmdb; char* cmdw; char* cmdl; char* resp_delim; int /*<<< orphan*/ * term_cmd; int /*<<< orphan*/ * term; int /*<<< orphan*/ * cmdll; } ;
struct TYPE_6__ {char* cmdb; char* cmdw; char* cmdl; int /*<<< orphan*/ * term_cmd; int /*<<< orphan*/ * term; int /*<<< orphan*/ * resp_delim; int /*<<< orphan*/ * cmdll; } ;
struct TYPE_10__ {char* cont; char* step; char* set_break; char* clr_break; char* clr_all_break; char* fill; char* dump_registers; char* register_pattern; char* load; char* loadresp; char* prompt; char* line_term; int /*<<< orphan*/  magic; int /*<<< orphan*/  regname; int /*<<< orphan*/ * regnames; int /*<<< orphan*/  stopbits; int /*<<< orphan*/ * target; int /*<<< orphan*/ * cmd_end; int /*<<< orphan*/ * load_routine; int /*<<< orphan*/  supply_register; TYPE_4__ getreg; TYPE_3__ setreg; TYPE_2__ getmem; TYPE_1__ setmem; int /*<<< orphan*/ * stop; int /*<<< orphan*/  init; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MONITOR_OPS_MAGIC ; 
 int /*<<< orphan*/  MO_CLR_BREAK_USES_ADDR ; 
 int /*<<< orphan*/  SERIAL_1_STOPBITS ; 
 TYPE_5__ cpu32bug_cmds ; 
 int /*<<< orphan*/  cpu32bug_inits ; 
 int /*<<< orphan*/  cpu32bug_ops ; 
 int /*<<< orphan*/  cpu32bug_regname ; 
 int /*<<< orphan*/  cpu32bug_supply_register ; 

__attribute__((used)) static void
init_cpu32bug_cmds (void)
{
  cpu32bug_cmds.flags = MO_CLR_BREAK_USES_ADDR;
  cpu32bug_cmds.init = cpu32bug_inits;	/* Init strings */
  cpu32bug_cmds.cont = "g\r";	/* continue command */
  cpu32bug_cmds.step = "t\r";	/* single step */
  cpu32bug_cmds.stop = NULL;	/* interrupt command */
  cpu32bug_cmds.set_break = "br %x\r";	/* set a breakpoint */
  cpu32bug_cmds.clr_break = "nobr %x\r";	/* clear a breakpoint */
  cpu32bug_cmds.clr_all_break = "nobr\r";	/* clear all breakpoints */
  cpu32bug_cmds.fill = "bf %x:%x %x;b\r";	/* fill (start count val) */
  cpu32bug_cmds.setmem.cmdb = "ms %x %02x\r";	/* setmem.cmdb (addr, value) */
  cpu32bug_cmds.setmem.cmdw = "ms %x %04x\r";	/* setmem.cmdw (addr, value) */
  cpu32bug_cmds.setmem.cmdl = "ms %x %08x\r";	/* setmem.cmdl (addr, value) */
  cpu32bug_cmds.setmem.cmdll = NULL;	/* setmem.cmdll (addr, value) */
  cpu32bug_cmds.setmem.resp_delim = NULL;	/* setreg.resp_delim */
  cpu32bug_cmds.setmem.term = NULL;	/* setreg.term */
  cpu32bug_cmds.setmem.term_cmd = NULL;		/* setreg.term_cmd */
  cpu32bug_cmds.getmem.cmdb = "md %x:%x;b\r";	/* getmem.cmdb (addr, len) */
  cpu32bug_cmds.getmem.cmdw = "md %x:%x;b\r";	/* getmem.cmdw (addr, len) */
  cpu32bug_cmds.getmem.cmdl = "md %x:%x;b\r";	/* getmem.cmdl (addr, len) */
  cpu32bug_cmds.getmem.cmdll = NULL;	/* getmem.cmdll (addr, len) */
  cpu32bug_cmds.getmem.resp_delim = " ";	/* getmem.resp_delim */
  cpu32bug_cmds.getmem.term = NULL;	/* getmem.term */
  cpu32bug_cmds.getmem.term_cmd = NULL;		/* getmem.term_cmd */
  cpu32bug_cmds.setreg.cmd = "rs %s %x\r";	/* setreg.cmd (name, value) */
  cpu32bug_cmds.setreg.resp_delim = NULL;	/* setreg.resp_delim */
  cpu32bug_cmds.setreg.term = NULL;	/* setreg.term */
  cpu32bug_cmds.setreg.term_cmd = NULL;		/* setreg.term_cmd */
  cpu32bug_cmds.getreg.cmd = "rs %s\r";		/* getreg.cmd (name) */
  cpu32bug_cmds.getreg.resp_delim = "=";	/* getreg.resp_delim */
  cpu32bug_cmds.getreg.term = NULL;	/* getreg.term */
  cpu32bug_cmds.getreg.term_cmd = NULL;		/* getreg.term_cmd */
  cpu32bug_cmds.dump_registers = "rd\r";	/* dump_registers */
  cpu32bug_cmds.register_pattern = "\\(\\w+\\) +=\\([0-9a-fA-F]+\\b\\)";	/* register_pattern */
  cpu32bug_cmds.supply_register = cpu32bug_supply_register;	/* supply_register */
  cpu32bug_cmds.load_routine = NULL;	/* load_routine (defaults to SRECs) */
  cpu32bug_cmds.load = "lo\r";	/* download command */
  cpu32bug_cmds.loadresp = "\n";	/* load response */
  cpu32bug_cmds.prompt = "CPU32Bug>";	/* monitor command prompt */
  cpu32bug_cmds.line_term = "\r";	/* end-of-line terminator */
  cpu32bug_cmds.cmd_end = NULL;	/* optional command terminator */
  cpu32bug_cmds.target = &cpu32bug_ops;		/* target operations */
  cpu32bug_cmds.stopbits = SERIAL_1_STOPBITS;	/* number of stop bits */
  cpu32bug_cmds.regnames = NULL;	/* registers names */
  cpu32bug_cmds.regname = cpu32bug_regname;
  cpu32bug_cmds.magic = MONITOR_OPS_MAGIC;	/* magic */
}