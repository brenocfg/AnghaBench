#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ptrace_out ;
typedef  int /*<<< orphan*/  ptrace_in ;
typedef  int /*<<< orphan*/  ptid_t ;
typedef  enum target_signal { ____Placeholder_target_signal } target_signal ;
struct TYPE_6__ {int status; int /*<<< orphan*/  errno_num; } ;
struct TYPE_5__ {int addr; int /*<<< orphan*/  pid; } ;
typedef  TYPE_1__ Rptrace ;
typedef  TYPE_2__ Ptrace_return ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  PC_REGNUM ; 
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTRACE_CONT ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  minus_one_ptid ; 
 int net_ptrace_clnt_call (int /*<<< orphan*/ ,TYPE_1__*,TYPE_2__*) ; 
 int net_step () ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 scalar_t__ ptid_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read_register (int /*<<< orphan*/ ) ; 
 char* rpcerr ; 
 int stop_pc ; 
 int stop_signal ; 

__attribute__((used)) static void
vx_resume (ptid_t ptid, int step, enum target_signal siggnal)
{
  int status;
  Rptrace ptrace_in;
  Ptrace_return ptrace_out;
  CORE_ADDR cont_addr;

  if (ptid_equal (ptid, minus_one_ptid))
    ptid = inferior_ptid;

  if (siggnal != 0 && siggnal != stop_signal)
    error ("Cannot send signals to VxWorks processes");

  /* Set CONT_ADDR to the address at which we are continuing,
     or to 1 if we are continuing from where the program stopped.
     This conforms to traditional ptrace () usage, but at the same
     time has special meaning for the VxWorks remote debug server.
     If the address is not 1, the server knows that the target
     program is jumping to a new address, which requires special
     handling if there is a breakpoint at the new address.  */

  cont_addr = read_register (PC_REGNUM);
  if (cont_addr == stop_pc)
    cont_addr = 1;

  memset ((char *) &ptrace_in, '\0', sizeof (ptrace_in));
  memset ((char *) &ptrace_out, '\0', sizeof (ptrace_out));

  ptrace_in.pid = PIDGET (ptid);
  ptrace_in.addr = cont_addr;	/* Target side insists on this, or it panics.  */

  if (step)
    status = net_step ();
  else
    status = net_ptrace_clnt_call (PTRACE_CONT, &ptrace_in, &ptrace_out);

  if (status)
    error (rpcerr);
  if (ptrace_out.status == -1)
    {
      errno = ptrace_out.errno_num;
      perror_with_name ("Resuming remote process");
    }
}