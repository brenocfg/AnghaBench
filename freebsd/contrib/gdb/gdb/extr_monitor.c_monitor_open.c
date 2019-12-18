#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ resp_delim; } ;
struct TYPE_8__ {scalar_t__ resp_delim; } ;
struct TYPE_7__ {scalar_t__ resp_delim; } ;
struct monitor_ops {scalar_t__ magic; int flags; char** init; int num_breakpoints; char* clr_all_break; char* line_term; int /*<<< orphan*/ * set_break; scalar_t__ stop; int /*<<< orphan*/  stopbits; TYPE_3__ setreg; TYPE_2__ setmem; TYPE_1__ getmem; scalar_t__ register_pattern; TYPE_4__* target; } ;
struct TYPE_10__ {char* to_shortname; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 scalar_t__ MONITOR_OPS_MAGIC ; 
 int MO_NO_ECHO_ON_OPEN ; 
 int baud_rate ; 
 int /*<<< orphan*/ * breakaddr ; 
 int /*<<< orphan*/  compile_pattern (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct monitor_ops* current_monitor ; 
 scalar_t__ dev_name ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  getmem_resp_delim_fastmap ; 
 int /*<<< orphan*/  getmem_resp_delim_pattern ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  monitor_debug (char*) ; 
 int /*<<< orphan*/  monitor_desc ; 
 int /*<<< orphan*/  monitor_expect_prompt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  monitor_printf (char*) ; 
 int /*<<< orphan*/  monitor_printf_noecho (char*) ; 
 int /*<<< orphan*/  monitor_stop () ; 
 int /*<<< orphan*/  perror_with_name (scalar_t__) ; 
 int /*<<< orphan*/  pid_to_ptid (int) ; 
 int /*<<< orphan*/  printf_unfiltered (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  push_target (TYPE_4__*) ; 
 int /*<<< orphan*/  register_fastmap ; 
 int /*<<< orphan*/  register_pattern ; 
 int /*<<< orphan*/  serial_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_flush_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_open (scalar_t__) ; 
 int /*<<< orphan*/  serial_raw (int /*<<< orphan*/ ) ; 
 scalar_t__ serial_setbaudrate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  serial_setstopbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setmem_resp_delim_fastmap ; 
 int /*<<< orphan*/  setmem_resp_delim_pattern ; 
 int /*<<< orphan*/  setreg_resp_delim_fastmap ; 
 int /*<<< orphan*/  setreg_resp_delim_pattern ; 
 int /*<<< orphan*/  start_remote () ; 
 TYPE_4__* targ_ops ; 
 int /*<<< orphan*/  target_preopen (int) ; 
 int /*<<< orphan*/  unpush_target (TYPE_4__*) ; 
 int /*<<< orphan*/  xfree (scalar_t__) ; 
 scalar_t__ xmalloc (int) ; 
 scalar_t__ xstrdup (char*) ; 

void
monitor_open (char *args, struct monitor_ops *mon_ops, int from_tty)
{
  char *name;
  char **p;

  if (mon_ops->magic != MONITOR_OPS_MAGIC)
    error ("Magic number of monitor_ops struct wrong.");

  targ_ops = mon_ops->target;
  name = targ_ops->to_shortname;

  if (!args)
    error ("Use `target %s DEVICE-NAME' to use a serial port, or \n\
`target %s HOST-NAME:PORT-NUMBER' to use a network connection.", name, name);

  target_preopen (from_tty);

  /* Setup pattern for register dump */

  if (mon_ops->register_pattern)
    compile_pattern (mon_ops->register_pattern, &register_pattern,
		     register_fastmap);

  if (mon_ops->getmem.resp_delim)
    compile_pattern (mon_ops->getmem.resp_delim, &getmem_resp_delim_pattern,
		     getmem_resp_delim_fastmap);

  if (mon_ops->setmem.resp_delim)
    compile_pattern (mon_ops->setmem.resp_delim, &setmem_resp_delim_pattern,
                     setmem_resp_delim_fastmap);

  if (mon_ops->setreg.resp_delim)
    compile_pattern (mon_ops->setreg.resp_delim, &setreg_resp_delim_pattern,
                     setreg_resp_delim_fastmap);
  
  unpush_target (targ_ops);

  if (dev_name)
    xfree (dev_name);
  dev_name = xstrdup (args);

  monitor_desc = serial_open (dev_name);

  if (!monitor_desc)
    perror_with_name (dev_name);

  if (baud_rate != -1)
    {
      if (serial_setbaudrate (monitor_desc, baud_rate))
	{
	  serial_close (monitor_desc);
	  perror_with_name (dev_name);
	}
    }

  serial_raw (monitor_desc);

  serial_flush_input (monitor_desc);

  /* some systems only work with 2 stop bits */

  serial_setstopbits (monitor_desc, mon_ops->stopbits);

  current_monitor = mon_ops;

  /* See if we can wake up the monitor.  First, try sending a stop sequence,
     then send the init strings.  Last, remove all breakpoints.  */

  if (current_monitor->stop)
    {
      monitor_stop ();
      if ((current_monitor->flags & MO_NO_ECHO_ON_OPEN) == 0)
	{
	  monitor_debug ("EXP Open echo\n");
	  monitor_expect_prompt (NULL, 0);
	}
    }

  /* wake up the monitor and see if it's alive */
  for (p = mon_ops->init; *p != NULL; p++)
    {
      /* Some of the characters we send may not be echoed,
         but we hope to get a prompt at the end of it all. */

      if ((current_monitor->flags & MO_NO_ECHO_ON_OPEN) == 0)
	monitor_printf (*p);
      else
	monitor_printf_noecho (*p);
      monitor_expect_prompt (NULL, 0);
    }

  serial_flush_input (monitor_desc);

  /* Alloc breakpoints */
  if (mon_ops->set_break != NULL)
    {
      if (mon_ops->num_breakpoints == 0)
	mon_ops->num_breakpoints = 8;

      breakaddr = (CORE_ADDR *) xmalloc (mon_ops->num_breakpoints * sizeof (CORE_ADDR));
      memset (breakaddr, 0, mon_ops->num_breakpoints * sizeof (CORE_ADDR));
    }

  /* Remove all breakpoints */

  if (mon_ops->clr_all_break)
    {
      monitor_printf (mon_ops->clr_all_break);
      monitor_expect_prompt (NULL, 0);
    }

  if (from_tty)
    printf_unfiltered ("Remote target %s connected to %s\n", name, dev_name);

  push_target (targ_ops);

  inferior_ptid = pid_to_ptid (42000);	/* Make run command think we are busy... */

  /* Give monitor_wait something to read */

  monitor_printf (current_monitor->line_term);

  start_remote ();
}