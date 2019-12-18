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
struct TYPE_3__ {char* cmdll; char* cmdl; char* cmdw; char* cmdb; int /*<<< orphan*/  term_cmd; scalar_t__ term; scalar_t__ resp_delim; } ;
struct TYPE_4__ {int flags; TYPE_1__ getmem; } ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 int MO_HEX_PREFIX ; 
 TYPE_2__* current_monitor ; 
 int /*<<< orphan*/  getmem_resp_delim_pattern ; 
 scalar_t__ isxdigit (int) ; 
 int /*<<< orphan*/  monitor_debug (char*) ; 
 int /*<<< orphan*/  monitor_error (char*,char*,int,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  monitor_expect (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  monitor_expect_prompt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  monitor_expect_regexp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  monitor_printf (char*,...) ; 
 int readchar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store_unsigned_integer (char*,int,unsigned int) ; 
 unsigned int strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  timeout ; 

__attribute__((used)) static int
monitor_read_memory_single (CORE_ADDR memaddr, char *myaddr, int len)
{
  unsigned int val;
  char membuf[sizeof (int) * 2 + 1];
  char *p;
  char *cmd;

  monitor_debug ("MON read single\n");
#if 0
  /* Can't actually use long longs (nice idea, though).  In fact, the
     call to strtoul below will fail if it tries to convert a value
     that's too big to fit in a long.  */
  if ((memaddr & 0x7) == 0 && len >= 8 && current_monitor->getmem.cmdll)
    {
      len = 8;
      cmd = current_monitor->getmem.cmdll;
    }
  else
#endif
  if ((memaddr & 0x3) == 0 && len >= 4 && current_monitor->getmem.cmdl)
    {
      len = 4;
      cmd = current_monitor->getmem.cmdl;
    }
  else if ((memaddr & 0x1) == 0 && len >= 2 && current_monitor->getmem.cmdw)
    {
      len = 2;
      cmd = current_monitor->getmem.cmdw;
    }
  else
    {
      len = 1;
      cmd = current_monitor->getmem.cmdb;
    }

  /* Send the examine command.  */

  monitor_printf (cmd, memaddr);

  /* If RESP_DELIM is specified, we search for that as a leading
     delimiter for the memory value.  Otherwise, we just start
     searching from the start of the buf.  */

  if (current_monitor->getmem.resp_delim)
    {
      monitor_debug ("EXP getmem.resp_delim\n");
      monitor_expect_regexp (&getmem_resp_delim_pattern, NULL, 0);
    }

  /* Now, read the appropriate number of hex digits for this loc,
     skipping spaces.  */

  /* Skip leading spaces and "0x" if MO_HEX_PREFIX flag is set. */
  if (current_monitor->flags & MO_HEX_PREFIX)
    {
      int c;

      c = readchar (timeout);
      while (c == ' ')
	c = readchar (timeout);
      if ((c == '0') && ((c = readchar (timeout)) == 'x'))
	;
      else
	monitor_error ("monitor_read_memory_single", 
		       "bad response from monitor",
		       memaddr, 0, NULL, 0);
    }

  {
    int i;
    for (i = 0; i < len * 2; i++)
      {
	int c;

	while (1)
	  {
	    c = readchar (timeout);
	    if (isxdigit (c))
	      break;
	    if (c == ' ')
	      continue;
	    
	    monitor_error ("monitor_read_memory_single",
			   "bad response from monitor",
			   memaddr, i, membuf, 0);
	  }
      membuf[i] = c;
    }
    membuf[i] = '\000';		/* terminate the number */
  }

/* If TERM is present, we wait for that to show up.  Also, (if TERM is
   present), we will send TERM_CMD if that is present.  In any case, we collect
   all of the output into buf, and then wait for the normal prompt.  */

  if (current_monitor->getmem.term)
    {
      monitor_expect (current_monitor->getmem.term, NULL, 0);	/* get response */

      if (current_monitor->getmem.term_cmd)
	{
	  monitor_printf (current_monitor->getmem.term_cmd);
	  monitor_expect_prompt (NULL, 0);
	}
    }
  else
    monitor_expect_prompt (NULL, 0);	/* get response */

  p = membuf;
  val = strtoul (membuf, &p, 16);

  if (val == 0 && membuf == p)
    monitor_error ("monitor_read_memory_single",
		   "bad value from monitor",
		   memaddr, 0, membuf, 0);

  /* supply register stores in target byte order, so swap here */

  store_unsigned_integer (myaddr, len, val);

  return len;
}