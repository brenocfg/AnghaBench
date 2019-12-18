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
struct TYPE_10__ {int flags; char* cont; char* step; char* stop; char* set_break; char* clr_break; char* clr_all_break; char* fill; char* dump_registers; char* register_pattern; char* load; char* loadresp; char* prompt; char* line_term; int /*<<< orphan*/  magic; int /*<<< orphan*/  regname; int /*<<< orphan*/ * regnames; int /*<<< orphan*/  stopbits; int /*<<< orphan*/ * target; int /*<<< orphan*/ * cmd_end; int /*<<< orphan*/ * load_routine; int /*<<< orphan*/  supply_register; TYPE_4__ getreg; TYPE_3__ setreg; TYPE_2__ getmem; TYPE_1__ setmem; int /*<<< orphan*/  init; } ;

/* Variables and functions */
 int /*<<< orphan*/  MONITOR_OPS_MAGIC ; 
 int MO_CLR_BREAK_USES_ADDR ; 
 int MO_FILL_USES_ADDR ; 
 int MO_NEED_REGDUMP_AFTER_CONT ; 
 int MO_SREC_ACK ; 
 int MO_SREC_ACK_PLUS ; 
 int /*<<< orphan*/  SERIAL_1_STOPBITS ; 
 TYPE_5__ est_cmds ; 
 int /*<<< orphan*/  est_inits ; 
 int /*<<< orphan*/  est_ops ; 
 int /*<<< orphan*/  est_regname ; 
 int /*<<< orphan*/  est_supply_register ; 

__attribute__((used)) static void
init_est_cmds (void)
{
  est_cmds.flags = MO_CLR_BREAK_USES_ADDR | MO_FILL_USES_ADDR | MO_NEED_REGDUMP_AFTER_CONT |
    MO_SREC_ACK | MO_SREC_ACK_PLUS;
  est_cmds.init = est_inits;	/* Init strings */
  est_cmds.cont = "go\r";	/* continue command */
  est_cmds.step = "sidr\r";	/* single step */
  est_cmds.stop = "\003";	/* ^C interrupts the program */
  est_cmds.set_break = "sb %x\r";	/* set a breakpoint */
  est_cmds.clr_break = "rb %x\r";	/* clear a breakpoint */
  est_cmds.clr_all_break = "rb\r";	/* clear all breakpoints */
  est_cmds.fill = "bfb %x %x %x\r";	/* fill (start end val) */
  est_cmds.setmem.cmdb = "smb %x %x\r";		/* setmem.cmdb (addr, value) */
  est_cmds.setmem.cmdw = "smw %x %x\r";		/* setmem.cmdw (addr, value) */
  est_cmds.setmem.cmdl = "sml %x %x\r";		/* setmem.cmdl (addr, value) */
  est_cmds.setmem.cmdll = NULL;	/* setmem.cmdll (addr, value) */
  est_cmds.setmem.resp_delim = NULL;	/* setreg.resp_delim */
  est_cmds.setmem.term = NULL;	/* setreg.term */
  est_cmds.setmem.term_cmd = NULL;	/* setreg.term_cmd */
  est_cmds.getmem.cmdb = "dmb %x %x\r";		/* getmem.cmdb (addr, len) */
  est_cmds.getmem.cmdw = "dmw %x %x\r";		/* getmem.cmdw (addr, len) */
  est_cmds.getmem.cmdl = "dml %x %x\r";		/* getmem.cmdl (addr, len) */
  est_cmds.getmem.cmdll = NULL;	/* getmem.cmdll (addr, len) */
  est_cmds.getmem.resp_delim = ": ";	/* getmem.resp_delim */
  est_cmds.getmem.term = NULL;	/* getmem.term */
  est_cmds.getmem.term_cmd = NULL;	/* getmem.term_cmd */
  est_cmds.setreg.cmd = "sr %s %x\r";	/* setreg.cmd (name, value) */
  est_cmds.setreg.resp_delim = NULL;	/* setreg.resp_delim */
  est_cmds.setreg.term = NULL;	/* setreg.term */
  est_cmds.setreg.term_cmd = NULL;	/* setreg.term_cmd */
  est_cmds.getreg.cmd = "dr %s\r";	/* getreg.cmd (name) */
  est_cmds.getreg.resp_delim = " = ";	/* getreg.resp_delim */
  est_cmds.getreg.term = NULL;	/* getreg.term */
  est_cmds.getreg.term_cmd = NULL;	/* getreg.term_cmd */
  est_cmds.dump_registers = "dr\r";	/* dump_registers */
  est_cmds.register_pattern = "\\(\\w+\\) = \\([0-9a-fA-F]+\\)";	/* register_pattern */
  est_cmds.supply_register = est_supply_register;	/* supply_register */
  est_cmds.load_routine = NULL;	/* load_routine (defaults to SRECs) */
  est_cmds.load = "dl\r";	/* download command */
  est_cmds.loadresp = "+";	/* load response */
  est_cmds.prompt = ">BKM>";	/* monitor command prompt */
  est_cmds.line_term = "\r";	/* end-of-line terminator */
  est_cmds.cmd_end = NULL;	/* optional command terminator */
  est_cmds.target = &est_ops;	/* target operations */
  est_cmds.stopbits = SERIAL_1_STOPBITS;	/* number of stop bits */
  est_cmds.regnames = NULL;
  est_cmds.regname = est_regname; /*register names*/
  est_cmds.magic = MONITOR_OPS_MAGIC;	/* magic */
}