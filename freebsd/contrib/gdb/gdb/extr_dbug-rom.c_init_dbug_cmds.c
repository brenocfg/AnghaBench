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
struct TYPE_10__ {int flags; char* cont; char* step; char* set_break; char* clr_break; char* clr_all_break; char* fill; char* dump_registers; char* register_pattern; char* load; char* loadresp; char* prompt; char* line_term; int /*<<< orphan*/  magic; int /*<<< orphan*/  regname; int /*<<< orphan*/ * regnames; int /*<<< orphan*/  stopbits; int /*<<< orphan*/ * target; int /*<<< orphan*/ * cmd_end; int /*<<< orphan*/ * load_routine; int /*<<< orphan*/  supply_register; TYPE_4__ getreg; TYPE_3__ setreg; TYPE_2__ getmem; TYPE_1__ setmem; int /*<<< orphan*/ * stop; int /*<<< orphan*/  init; } ;

/* Variables and functions */
 int /*<<< orphan*/  MONITOR_OPS_MAGIC ; 
 int MO_CLR_BREAK_USES_ADDR ; 
 int MO_FILL_USES_ADDR ; 
 int MO_GETMEM_NEEDS_RANGE ; 
 int /*<<< orphan*/  SERIAL_1_STOPBITS ; 
 TYPE_5__ dbug_cmds ; 
 int /*<<< orphan*/  dbug_inits ; 
 int /*<<< orphan*/  dbug_ops ; 
 int /*<<< orphan*/  dbug_regname ; 
 int /*<<< orphan*/  dbug_supply_register ; 

__attribute__((used)) static void
init_dbug_cmds (void)
{
  dbug_cmds.flags = MO_CLR_BREAK_USES_ADDR | MO_GETMEM_NEEDS_RANGE | MO_FILL_USES_ADDR;
  dbug_cmds.init = dbug_inits;	/* Init strings */
  dbug_cmds.cont = "go\r";	/* continue command */
  dbug_cmds.step = "trace\r";	/* single step */
  dbug_cmds.stop = NULL;	/* interrupt command */
  dbug_cmds.set_break = "br %x\r";	/* set a breakpoint */
  dbug_cmds.clr_break = "br -r %x\r";	/* clear a breakpoint */
  dbug_cmds.clr_all_break = "br -r\r";	/* clear all breakpoints */
  dbug_cmds.fill = "bf.b %x %x %x\r";	/* fill (start end val) */
  dbug_cmds.setmem.cmdb = "mm.b %x %x\r";	/* setmem.cmdb (addr, value) */
  dbug_cmds.setmem.cmdw = "mm.w %x %x\r";	/* setmem.cmdw (addr, value) */
  dbug_cmds.setmem.cmdl = "mm.l %x %x\r";	/* setmem.cmdl (addr, value) */
  dbug_cmds.setmem.cmdll = NULL;	/* setmem.cmdll (addr, value) */
  dbug_cmds.setmem.resp_delim = NULL;	/* setmem.resp_delim */
  dbug_cmds.setmem.term = NULL;	/* setmem.term */
  dbug_cmds.setmem.term_cmd = NULL;	/* setmem.term_cmd */
  dbug_cmds.getmem.cmdb = "md.b %x %x\r";	/* getmem.cmdb (addr, addr2) */
  dbug_cmds.getmem.cmdw = "md.w %x %x\r";	/* getmem.cmdw (addr, addr2) */
  dbug_cmds.getmem.cmdl = "md.l %x %x\r";	/* getmem.cmdl (addr, addr2) */
  dbug_cmds.getmem.cmdll = NULL;	/* getmem.cmdll (addr, addr2) */
  dbug_cmds.getmem.resp_delim = ":";	/* getmem.resp_delim */
  dbug_cmds.getmem.term = NULL;	/* getmem.term */
  dbug_cmds.getmem.term_cmd = NULL;	/* getmem.term_cmd */
  dbug_cmds.setreg.cmd = "rm %s %x\r";	/* setreg.cmd (name, value) */
  dbug_cmds.setreg.resp_delim = NULL;	/* setreg.resp_delim */
  dbug_cmds.setreg.term = NULL;	/* setreg.term */
  dbug_cmds.setreg.term_cmd = NULL;	/* setreg.term_cmd */
  dbug_cmds.getreg.cmd = "rd %s\r";	/* getreg.cmd (name) */
  dbug_cmds.getreg.resp_delim = ":";	/* getreg.resp_delim */
  dbug_cmds.getreg.term = NULL;	/* getreg.term */
  dbug_cmds.getreg.term_cmd = NULL;	/* getreg.term_cmd */
  dbug_cmds.dump_registers = "rd\r";	/* dump_registers */
  dbug_cmds.register_pattern = "\\(\\w+\\) +:\\([0-9a-fA-F]+\\b\\)";	/* register_pattern */
  dbug_cmds.supply_register = dbug_supply_register;	/* supply_register */
  dbug_cmds.load_routine = NULL;	/* load_routine (defaults to SRECs) */
  dbug_cmds.load = "dl\r";	/* download command */
  dbug_cmds.loadresp = "\n";	/* load response */
  dbug_cmds.prompt = "dBUG>";	/* monitor command prompt */
  dbug_cmds.line_term = "\r";	/* end-of-line terminator */
  dbug_cmds.cmd_end = NULL;	/* optional command terminator */
  dbug_cmds.target = &dbug_ops;	/* target operations */
  dbug_cmds.stopbits = SERIAL_1_STOPBITS;	/* number of stop bits */
  dbug_cmds.regnames = NULL;	/* registers names */
  dbug_cmds.regname = dbug_regname;
  dbug_cmds.magic = MONITOR_OPS_MAGIC;	/* magic */
}