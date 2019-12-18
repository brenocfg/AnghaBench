#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  ptrace_in ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
struct TYPE_3__ {int addr; int /*<<< orphan*/  pid; } ;
typedef  TYPE_1__ Rptrace ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int RPC_SUCCESS ; 
 int errno ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int net_clnt_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  xdr_int ; 
 int /*<<< orphan*/  xdr_rptrace ; 

__attribute__((used)) static int
net_break (int addr, u_long procnum)
{
  enum clnt_stat status;
  int break_status;
  Rptrace ptrace_in;		/* XXX This is stupid.  It doesn't need to be a ptrace
				   structure.  How about something smaller? */

  memset ((char *) &ptrace_in, '\0', sizeof (ptrace_in));
  break_status = 0;

  ptrace_in.addr = addr;
  ptrace_in.pid = PIDGET (inferior_ptid);

  status = net_clnt_call (procnum, xdr_rptrace, &ptrace_in, xdr_int,
			  &break_status);

  if (status != RPC_SUCCESS)
    return errno;

  if (break_status == -1)
    return ENOMEM;
  return break_status;		/* probably (FIXME) zero */
}