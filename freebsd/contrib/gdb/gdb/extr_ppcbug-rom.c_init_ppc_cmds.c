#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct target_ops {int dummy; } ;
struct TYPE_8__ {char* cmd; char* resp_delim; int /*<<< orphan*/ * term_cmd; int /*<<< orphan*/ * term; } ;
struct TYPE_7__ {char* cmd; int /*<<< orphan*/ * term_cmd; int /*<<< orphan*/ * term; int /*<<< orphan*/ * resp_delim; } ;
struct TYPE_6__ {char* cmdb; char* cmdw; char* cmdl; char* resp_delim; int /*<<< orphan*/ * term_cmd; int /*<<< orphan*/ * term; int /*<<< orphan*/ * cmdll; } ;
struct TYPE_5__ {char* cmdb; char* cmdw; char* cmdl; int /*<<< orphan*/ * term_cmd; int /*<<< orphan*/ * term; int /*<<< orphan*/ * resp_delim; int /*<<< orphan*/ * cmdll; } ;
struct monitor_ops {int flags; char* cont; char* step; char* set_break; char* clr_break; char* clr_all_break; char* fill; char* register_pattern; char* dump_registers; char* load; char* prompt; char* line_term; int /*<<< orphan*/  magic; int /*<<< orphan*/  regnames; int /*<<< orphan*/  stopbits; struct target_ops* target; int /*<<< orphan*/ * cmd_end; int /*<<< orphan*/ * loadresp; int /*<<< orphan*/ * load_routine; int /*<<< orphan*/  supply_register; TYPE_4__ getreg; TYPE_3__ setreg; TYPE_2__ getmem; TYPE_1__ setmem; int /*<<< orphan*/ * stop; int /*<<< orphan*/  init; } ;

/* Variables and functions */
 int /*<<< orphan*/  MONITOR_OPS_MAGIC ; 
 int MO_CLR_BREAK_USES_ADDR ; 
 int MO_HANDLE_NL ; 
 int /*<<< orphan*/  SERIAL_1_STOPBITS ; 
 int /*<<< orphan*/  ppcbug_inits ; 
 int /*<<< orphan*/  ppcbug_regnames ; 
 int /*<<< orphan*/  ppcbug_supply_register ; 

__attribute__((used)) static void
init_ppc_cmds (char *LOAD_CMD,
	       struct monitor_ops *OPS,
	       struct target_ops *targops)
{
  OPS->flags = MO_CLR_BREAK_USES_ADDR | MO_HANDLE_NL;
  OPS->init = ppcbug_inits;	/* Init strings */
  OPS->cont = "g\r";		/* continue command */
  OPS->step = "t\r";		/* single step */
  OPS->stop = NULL;		/* interrupt command */
  OPS->set_break = "br %x\r";	/* set a breakpoint */
  OPS->clr_break = "nobr %x\r";	/* clear a breakpoint */
  OPS->clr_all_break = "nobr\r";	/* clear all breakpoints */
  OPS->fill = "bf %x:%x %x;b\r";	/* fill (start count val) */
  OPS->setmem.cmdb = "ms %x %02x\r";	/* setmem.cmdb (addr, value) */
  OPS->setmem.cmdw = "ms %x %04x\r";	/* setmem.cmdw (addr, value) */
  OPS->setmem.cmdl = "ms %x %08x\r";	/* setmem.cmdl (addr, value) */
  OPS->setmem.cmdll = NULL;	/* setmem.cmdll (addr, value) */
  OPS->setmem.resp_delim = NULL;	/* setreg.resp_delim */
  OPS->setmem.term = NULL;	/* setreg.term */
  OPS->setmem.term_cmd = NULL;	/* setreg.term_cmd */
  OPS->getmem.cmdb = "md %x:%x;b\r";	/* getmem.cmdb (addr, len) */
  OPS->getmem.cmdw = "md %x:%x;b\r";	/* getmem.cmdw (addr, len) */
  OPS->getmem.cmdl = "md %x:%x;b\r";	/* getmem.cmdl (addr, len) */
  OPS->getmem.cmdll = NULL;	/* getmem.cmdll (addr, len) */
  OPS->getmem.resp_delim = " ";	/* getmem.resp_delim */
  OPS->getmem.term = NULL;	/* getmem.term */
  OPS->getmem.term_cmd = NULL;	/* getmem.term_cmd */
  OPS->setreg.cmd = "rs %s %x\r";	/* setreg.cmd (name, value) */
  OPS->setreg.resp_delim = NULL;	/* setreg.resp_delim */
  OPS->setreg.term = NULL;	/* setreg.term */
  OPS->setreg.term_cmd = NULL;	/* setreg.term_cmd */
  OPS->getreg.cmd = "rs %s\r";	/* getreg.cmd (name) */
  OPS->getreg.resp_delim = "=";	/* getreg.resp_delim */
  OPS->getreg.term = NULL;	/* getreg.term */
  OPS->getreg.term_cmd = NULL;	/* getreg.term_cmd */
  OPS->register_pattern = "\\(\\w+\\) +=\\([0-9a-fA-F]+\\b\\)";		/* register_pattern */
  OPS->supply_register = ppcbug_supply_register;	/* supply_register */
  OPS->dump_registers = "rd\r";	/* dump all registers */
  OPS->load_routine = NULL;	/* load_routine (defaults to SRECs) */
  OPS->load = LOAD_CMD;		/* download command */
  OPS->loadresp = NULL;		/* load response */
  OPS->prompt = "PPC1-Bug>";	/* monitor command prompt */
  OPS->line_term = "\r";	/* end-of-line terminator */
  OPS->cmd_end = NULL;		/* optional command terminator */
  OPS->target = targops;	/* target operations */
  OPS->stopbits = SERIAL_1_STOPBITS;	/* number of stop bits */
  OPS->regnames = ppcbug_regnames;	/* registers names */
  OPS->magic = MONITOR_OPS_MAGIC;	/* magic */
}