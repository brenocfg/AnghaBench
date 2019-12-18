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
struct TYPE_3__ {scalar_t__ term_cmd; scalar_t__ term; scalar_t__ resp_delim; int /*<<< orphan*/  cmd; } ;
struct TYPE_4__ {char* (* regname ) (int) ;char** regnames; int flags; TYPE_1__ getreg; } ;

/* Variables and functions */
 int DEPRECATED_REGISTER_RAW_SIZE (int) ; 
 int MAX_REGISTER_SIZE ; 
 int MO_32_REGS_PAIRED ; 
 int MO_HEX_PREFIX ; 
 char* alloca (int) ; 
 TYPE_2__* current_monitor ; 
 int /*<<< orphan*/  error (char*,int) ; 
 int /*<<< orphan*/  isxdigit (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  monitor_debug (char*,...) ; 
 int /*<<< orphan*/  monitor_expect (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  monitor_expect_prompt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  monitor_printf (scalar_t__,...) ; 
 int /*<<< orphan*/  monitor_supply_register (int,char*) ; 
 int readchar (int /*<<< orphan*/ ) ; 
 char* stub1 (int) ; 
 int /*<<< orphan*/  supply_register (int,char*) ; 
 int /*<<< orphan*/  timeout ; 

__attribute__((used)) static void
monitor_fetch_register (int regno)
{
  const char *name;
  char *zerobuf;
  char *regbuf;
  int i;

  regbuf  = alloca (MAX_REGISTER_SIZE * 2 + 1);
  zerobuf = alloca (MAX_REGISTER_SIZE);
  memset (zerobuf, 0, MAX_REGISTER_SIZE);

  if (current_monitor->regname != NULL)
    name = current_monitor->regname (regno);
  else
    name = current_monitor->regnames[regno];
  monitor_debug ("MON fetchreg %d '%s'\n", regno, name ? name : "(null name)");

  if (!name || (*name == '\0'))
    {
      monitor_debug ("No register known for %d\n", regno);
      supply_register (regno, zerobuf);
      return;
    }

  /* send the register examine command */

  monitor_printf (current_monitor->getreg.cmd, name);

  /* If RESP_DELIM is specified, we search for that as a leading
     delimiter for the register value.  Otherwise, we just start
     searching from the start of the buf.  */

  if (current_monitor->getreg.resp_delim)
    {
      monitor_debug ("EXP getreg.resp_delim\n");
      monitor_expect (current_monitor->getreg.resp_delim, NULL, 0);
      /* Handle case of first 32 registers listed in pairs.  */
      if (current_monitor->flags & MO_32_REGS_PAIRED
	  && (regno & 1) != 0 && regno < 32)
	{
	  monitor_debug ("EXP getreg.resp_delim\n");
	  monitor_expect (current_monitor->getreg.resp_delim, NULL, 0);
	}
    }

  /* Skip leading spaces and "0x" if MO_HEX_PREFIX flag is set */
  if (current_monitor->flags & MO_HEX_PREFIX)
    {
      int c;
      c = readchar (timeout);
      while (c == ' ')
	c = readchar (timeout);
      if ((c == '0') && ((c = readchar (timeout)) == 'x'))
	;
      else
	error ("Bad value returned from monitor while fetching register %x.",
	       regno);
    }

  /* Read upto the maximum number of hex digits for this register, skipping
     spaces, but stop reading if something else is seen.  Some monitors
     like to drop leading zeros.  */

  for (i = 0; i < DEPRECATED_REGISTER_RAW_SIZE (regno) * 2; i++)
    {
      int c;
      c = readchar (timeout);
      while (c == ' ')
	c = readchar (timeout);

      if (!isxdigit (c))
	break;

      regbuf[i] = c;
    }

  regbuf[i] = '\000';		/* terminate the number */
  monitor_debug ("REGVAL '%s'\n", regbuf);

  /* If TERM is present, we wait for that to show up.  Also, (if TERM
     is present), we will send TERM_CMD if that is present.  In any
     case, we collect all of the output into buf, and then wait for
     the normal prompt.  */

  if (current_monitor->getreg.term)
    {
      monitor_debug ("EXP getreg.term\n");
      monitor_expect (current_monitor->getreg.term, NULL, 0);		/* get response */
    }

  if (current_monitor->getreg.term_cmd)
    {
      monitor_debug ("EMIT getreg.term.cmd\n");
      monitor_printf (current_monitor->getreg.term_cmd);
    }
  if (!current_monitor->getreg.term ||	/* Already expected or */
      current_monitor->getreg.term_cmd)		/* ack expected */
    monitor_expect_prompt (NULL, 0);	/* get response */

  monitor_supply_register (regno, regbuf);
}