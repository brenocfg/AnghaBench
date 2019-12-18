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
struct TYPE_6__ {int status; int /*<<< orphan*/  errno_num; } ;
struct TYPE_5__ {scalar_t__ pid; } ;
typedef  TYPE_1__ Rptrace ;
typedef  TYPE_2__ Ptrace_return ;

/* Variables and functions */
 scalar_t__ PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTRACE_KILL ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  local_hex_string (unsigned long) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int net_ptrace_clnt_call (int /*<<< orphan*/ ,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  null_ptid ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  pop_target () ; 
 int /*<<< orphan*/  printf_unfiltered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpcerr ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vx_kill (void)
{
  Rptrace ptrace_in;
  Ptrace_return ptrace_out;
  int status;

  printf_unfiltered ("Killing pid %s.\n", local_hex_string ((unsigned long) PIDGET (inferior_ptid)));

  memset ((char *) &ptrace_in, '\0', sizeof (ptrace_in));
  memset ((char *) &ptrace_out, '\0', sizeof (ptrace_out));
  ptrace_in.pid = PIDGET (inferior_ptid);

  status = net_ptrace_clnt_call (PTRACE_KILL, &ptrace_in, &ptrace_out);
  if (status == -1)
    warning (rpcerr);
  else if (ptrace_out.status == -1)
    {
      errno = ptrace_out.errno_num;
      perror_with_name ("Killing VxWorks process");
    }

  /* If it gives good status, the process is *gone*, no events remain.
     If the kill failed, assume the process is gone anyhow.  */
  inferior_ptid = null_ptid;
  pop_target ();		/* go back to non-executing VxWorks connection */
}