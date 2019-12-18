#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONGEST ;
struct TYPE_3__ {char* cmd; char const* term_cmd; scalar_t__ term; scalar_t__ resp_delim; } ;
struct TYPE_4__ {char* (* regname ) (int) ;char** regnames; int flags; TYPE_1__ setreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEPRECATED_REGISTER_RAW_SIZE (int) ; 
 int MO_REGISTER_VALUE_FIRST ; 
 int MO_SETREG_INTERACTIVE ; 
 TYPE_2__* current_monitor ; 
 int /*<<< orphan*/  monitor_debug (char*,...) ; 
 int /*<<< orphan*/  monitor_expect (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  monitor_expect_prompt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  monitor_expect_regexp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  monitor_printf (char*,char const*,...) ; 
 char const* paddr_nz (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_register (int) ; 
 int /*<<< orphan*/  setreg_resp_delim_pattern ; 
 char* stub1 (int) ; 

__attribute__((used)) static void
monitor_store_register (int regno)
{
  const char *name;
  ULONGEST val;
  
  if (current_monitor->regname != NULL)
    name = current_monitor->regname (regno);
  else
    name = current_monitor->regnames[regno];
  
  if (!name || (*name == '\0'))
    {
      monitor_debug ("MON Cannot store unknown register\n");
      return;
    }

  val = read_register (regno);
  monitor_debug ("MON storeg %d %s\n", regno,
		 phex (val, DEPRECATED_REGISTER_RAW_SIZE (regno)));

  /* send the register deposit command */

  if (current_monitor->flags & MO_REGISTER_VALUE_FIRST)
    monitor_printf (current_monitor->setreg.cmd, val, name);
  else if (current_monitor->flags & MO_SETREG_INTERACTIVE)
    monitor_printf (current_monitor->setreg.cmd, name);
  else
    monitor_printf (current_monitor->setreg.cmd, name, val);

  if (current_monitor->setreg.resp_delim)
    {
      monitor_debug ("EXP setreg.resp_delim\n");
      monitor_expect_regexp (&setreg_resp_delim_pattern, NULL, 0);
      if (current_monitor->flags & MO_SETREG_INTERACTIVE)
	monitor_printf ("%s\r", paddr_nz (val));
    }
  if (current_monitor->setreg.term)
    {
      monitor_debug ("EXP setreg.term\n");
      monitor_expect (current_monitor->setreg.term, NULL, 0);
      if (current_monitor->flags & MO_SETREG_INTERACTIVE)
	monitor_printf ("%s\r", paddr_nz (val));
      monitor_expect_prompt (NULL, 0);
    }
  else
    monitor_expect_prompt (NULL, 0);
  if (current_monitor->setreg.term_cmd)		/* Mode exit required */
    {
      monitor_debug ("EXP setreg_termcmd\n");
      monitor_printf ("%s", current_monitor->setreg.term_cmd);
      monitor_expect_prompt (NULL, 0);
    }
}