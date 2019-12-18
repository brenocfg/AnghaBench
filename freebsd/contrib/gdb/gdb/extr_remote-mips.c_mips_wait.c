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
struct TYPE_3__ {int integer; void* sig; } ;
struct target_waitstatus {TYPE_1__ value; void* kind; } ;
typedef  int /*<<< orphan*/  ptid_t ;
struct TYPE_4__ {scalar_t__ addr; scalar_t__ type; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ BREAK_FETCH ; 
 int DATA_MAXLEN ; 
 int DEPRECATED_FP_REGNUM ; 
 int /*<<< orphan*/  DEPRECATED_REGISTER_RAW_SIZE (int) ; 
 int MAX_LSI_BREAKPOINTS ; 
 int MAX_REGISTER_SIZE ; 
 scalar_t__ MON_PMON ; 
 int PC_REGNUM ; 
 int SP_REGNUM ; 
 void* TARGET_SIGNAL_TRAP ; 
 void* TARGET_WAITKIND_EXITED ; 
 void* TARGET_WAITKIND_SIGNALLED ; 
 void* TARGET_WAITKIND_STOPPED ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  find_pc_partial_function (scalar_t__,char**,scalar_t__*,int /*<<< orphan*/ *) ; 
 int hit_watchpoint ; 
 int /*<<< orphan*/  inferior_ptid ; 
 scalar_t__ interrupt_count ; 
 TYPE_2__* lsi_breakpoints ; 
 int /*<<< orphan*/  mips_enter_debug () ; 
 int /*<<< orphan*/  mips_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_exit_debug () ; 
 scalar_t__ mips_monitor ; 
 int /*<<< orphan*/  mips_need_reply ; 
 int mips_request (char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,char*) ; 
 void* mips_signal_from_protocol (int) ; 
 int mips_wait_flag ; 
 scalar_t__ read_pc () ; 
 int /*<<< orphan*/  safe_strerror (int /*<<< orphan*/ ) ; 
 int sscanf (char*,char*,int*,int*,int*,char*) ; 
 int /*<<< orphan*/  store_unsigned_integer (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  supply_register (int,char*) ; 
 char* target_shortname ; 

__attribute__((used)) static ptid_t
mips_wait (ptid_t ptid, struct target_waitstatus *status)
{
  int rstatus;
  int err;
  char buff[DATA_MAXLEN];
  int rpc, rfp, rsp;
  char flags[20];
  int nfields;
  int i;

  interrupt_count = 0;
  hit_watchpoint = 0;

  /* If we have not sent a single step or continue command, then the
     board is waiting for us to do something.  Return a status
     indicating that it is stopped.  */
  if (!mips_need_reply)
    {
      status->kind = TARGET_WAITKIND_STOPPED;
      status->value.sig = TARGET_SIGNAL_TRAP;
      return inferior_ptid;
    }

  /* No timeout; we sit here as long as the program continues to execute.  */
  mips_wait_flag = 1;
  rstatus = mips_request ('\000', 0, 0, &err, -1, buff);
  mips_wait_flag = 0;
  if (err)
    mips_error ("Remote failure: %s", safe_strerror (errno));

  /* On returning from a continue, the PMON monitor seems to start
     echoing back the messages we send prior to sending back the
     ACK. The code can cope with this, but to try and avoid the
     unnecessary serial traffic, and "spurious" characters displayed
     to the user, we cheat and reset the debug protocol. The problems
     seems to be caused by a check on the number of arguments, and the
     command length, within the monitor causing it to echo the command
     as a bad packet. */
  if (mips_monitor == MON_PMON)
    {
      mips_exit_debug ();
      mips_enter_debug ();
    }

  /* See if we got back extended status.  If so, pick out the pc, fp, sp, etc... */

  nfields = sscanf (buff, "0x%*x %*c 0x%*x 0x%*x 0x%x 0x%x 0x%x 0x%*x %s",
		    &rpc, &rfp, &rsp, flags);
  if (nfields >= 3)
    {
      char buf[MAX_REGISTER_SIZE];

      store_unsigned_integer (buf, DEPRECATED_REGISTER_RAW_SIZE (PC_REGNUM), rpc);
      supply_register (PC_REGNUM, buf);

      store_unsigned_integer (buf, DEPRECATED_REGISTER_RAW_SIZE (PC_REGNUM), rfp);
      supply_register (30, buf);	/* This register they are avoiding and so it is unnamed */

      store_unsigned_integer (buf, DEPRECATED_REGISTER_RAW_SIZE (SP_REGNUM), rsp);
      supply_register (SP_REGNUM, buf);

      store_unsigned_integer (buf, DEPRECATED_REGISTER_RAW_SIZE (DEPRECATED_FP_REGNUM), 0);
      supply_register (DEPRECATED_FP_REGNUM, buf);

      if (nfields == 9)
	{
	  int i;

	  for (i = 0; i <= 2; i++)
	    if (flags[i] == 'r' || flags[i] == 'w')
	      hit_watchpoint = 1;
	    else if (flags[i] == '\000')
	      break;
	}
    }

  if (strcmp (target_shortname, "lsi") == 0)
    {
#if 0
      /* If this is an LSI PMON target, see if we just hit a hardrdware watchpoint.
         Right now, PMON doesn't give us enough information to determine which
         breakpoint we hit.  So we have to look up the PC in our own table
         of breakpoints, and if found, assume it's just a normal instruction
         fetch breakpoint, not a data watchpoint.  FIXME when PMON
         provides some way to tell us what type of breakpoint it is.  */
      int i;
      CORE_ADDR pc = read_pc ();

      hit_watchpoint = 1;
      for (i = 0; i < MAX_LSI_BREAKPOINTS; i++)
	{
	  if (lsi_breakpoints[i].addr == pc
	      && lsi_breakpoints[i].type == BREAK_FETCH)
	    {
	      hit_watchpoint = 0;
	      break;
	    }
	}
#else
      /* If a data breakpoint was hit, PMON returns the following packet:
         0x1 c 0x0 0x57f 0x1
         The return packet from an ordinary breakpoint doesn't have the
         extra 0x01 field tacked onto the end.  */
      if (nfields == 1 && rpc == 1)
	hit_watchpoint = 1;
#endif
    }

  /* NOTE: The following (sig) numbers are defined by PMON:
     SPP_SIGTRAP     5       breakpoint
     SPP_SIGINT      2
     SPP_SIGSEGV     11
     SPP_SIGBUS      10
     SPP_SIGILL      4
     SPP_SIGFPE      8
     SPP_SIGTERM     15 */

  /* Translate a MIPS waitstatus.  We use constants here rather than WTERMSIG
     and so on, because the constants we want here are determined by the
     MIPS protocol and have nothing to do with what host we are running on.  */
  if ((rstatus & 0xff) == 0)
    {
      status->kind = TARGET_WAITKIND_EXITED;
      status->value.integer = (((rstatus) >> 8) & 0xff);
    }
  else if ((rstatus & 0xff) == 0x7f)
    {
      status->kind = TARGET_WAITKIND_STOPPED;
      status->value.sig = mips_signal_from_protocol (((rstatus) >> 8) & 0xff);

      /* If the stop PC is in the _exit function, assume
         we hit the 'break 0x3ff' instruction in _exit, so this
         is not a normal breakpoint.  */
      if (strcmp (target_shortname, "lsi") == 0)
	{
	  char *func_name;
	  CORE_ADDR func_start;
	  CORE_ADDR pc = read_pc ();

	  find_pc_partial_function (pc, &func_name, &func_start, NULL);
	  if (func_name != NULL && strcmp (func_name, "_exit") == 0
	      && func_start == pc)
	    status->kind = TARGET_WAITKIND_EXITED;
	}
    }
  else
    {
      status->kind = TARGET_WAITKIND_SIGNALLED;
      status->value.sig = mips_signal_from_protocol (rstatus & 0x7f);
    }

  return inferior_ptid;
}