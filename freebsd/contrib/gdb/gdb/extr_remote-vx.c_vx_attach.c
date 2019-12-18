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
struct TYPE_5__ {unsigned long pid; } ;
typedef  TYPE_1__ Rptrace ;
typedef  TYPE_2__ Ptrace_return ;

/* Variables and functions */
 int /*<<< orphan*/  PTRACE_ATTACH ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  error_no_arg (char*) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  local_hex_string (unsigned long) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int net_ptrace_clnt_call (int /*<<< orphan*/ ,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  pid_to_ptid (unsigned long) ; 
 int /*<<< orphan*/  printf_unfiltered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_target (int /*<<< orphan*/ *) ; 
 char* rpcerr ; 
 unsigned long strtoul (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vx_run_ops ; 
 scalar_t__ vx_running ; 
 int /*<<< orphan*/  xfree (scalar_t__) ; 

__attribute__((used)) static void
vx_attach (char *args, int from_tty)
{
  unsigned long pid;
  char *cptr = 0;
  Rptrace ptrace_in;
  Ptrace_return ptrace_out;
  int status;

  if (!args)
    error_no_arg ("process-id to attach");

  pid = strtoul (args, &cptr, 0);
  if ((cptr == args) || (*cptr != '\0'))
    error ("Invalid process-id -- give a single number in decimal or 0xhex");

  if (from_tty)
    printf_unfiltered ("Attaching pid %s.\n",
		       local_hex_string ((unsigned long) pid));

  memset ((char *) &ptrace_in, '\0', sizeof (ptrace_in));
  memset ((char *) &ptrace_out, '\0', sizeof (ptrace_out));
  ptrace_in.pid = pid;

  status = net_ptrace_clnt_call (PTRACE_ATTACH, &ptrace_in, &ptrace_out);
  if (status == -1)
    error (rpcerr);
  if (ptrace_out.status == -1)
    {
      errno = ptrace_out.errno_num;
      perror_with_name ("Attaching remote process");
    }

  /* It worked... */

  inferior_ptid = pid_to_ptid (pid);
  push_target (&vx_run_ops);

  if (vx_running)
    xfree (vx_running);
  vx_running = 0;
}