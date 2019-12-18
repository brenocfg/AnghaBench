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
 int /*<<< orphan*/  PTRACE_DETACH ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  local_hex_string (unsigned long) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int net_ptrace_clnt_call (int /*<<< orphan*/ ,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  null_ptid ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  pop_target () ; 
 int /*<<< orphan*/  printf_unfiltered (char*,int /*<<< orphan*/ ) ; 
 char* rpcerr ; 

__attribute__((used)) static void
vx_detach (char *args, int from_tty)
{
  Rptrace ptrace_in;
  Ptrace_return ptrace_out;
  int signal = 0;
  int status;

  if (args)
    error ("Argument given to VxWorks \"detach\".");

  if (from_tty)
    printf_unfiltered ("Detaching pid %s.\n",
		       local_hex_string (
		         (unsigned long) PIDGET (inferior_ptid)));

  if (args)			/* FIXME, should be possible to leave suspended */
    signal = atoi (args);

  memset ((char *) &ptrace_in, '\0', sizeof (ptrace_in));
  memset ((char *) &ptrace_out, '\0', sizeof (ptrace_out));
  ptrace_in.pid = PIDGET (inferior_ptid);

  status = net_ptrace_clnt_call (PTRACE_DETACH, &ptrace_in, &ptrace_out);
  if (status == -1)
    error (rpcerr);
  if (ptrace_out.status == -1)
    {
      errno = ptrace_out.errno_num;
      perror_with_name ("Detaching VxWorks process");
    }

  inferior_ptid = null_ptid;
  pop_target ();		/* go back to non-executing VxWorks connection */
}