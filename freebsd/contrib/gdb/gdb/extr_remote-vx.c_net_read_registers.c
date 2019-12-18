#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_long ;
typedef  int /*<<< orphan*/  ptrace_out ;
typedef  int /*<<< orphan*/  ptrace_in ;
typedef  scalar_t__ caddr_t ;
struct TYPE_12__ {char* bytes; int len; } ;
struct TYPE_9__ {scalar_t__ more_data; } ;
struct TYPE_11__ {int status; int /*<<< orphan*/  errno_num; TYPE_2__ info; } ;
struct TYPE_8__ {int /*<<< orphan*/  ttype; } ;
struct TYPE_10__ {TYPE_1__ info; int /*<<< orphan*/  pid; } ;
typedef  TYPE_3__ Rptrace ;
typedef  TYPE_4__ Ptrace_return ;
typedef  TYPE_5__ C_bytes ;

/* Variables and functions */
 int /*<<< orphan*/  NOINFO ; 
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 scalar_t__ PTRACE_GETREGS ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int net_ptrace_clnt_call (scalar_t__,TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  rpcerr ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

void
net_read_registers (char *reg_buf, int len, u_long procnum)
{
  int status;
  Rptrace ptrace_in;
  Ptrace_return ptrace_out;
  C_bytes out_data;
  char message[100];

  memset ((char *) &ptrace_in, '\0', sizeof (ptrace_in));
  memset ((char *) &ptrace_out, '\0', sizeof (ptrace_out));

  /* Initialize RPC input argument structure.  */

  ptrace_in.pid = PIDGET (inferior_ptid);
  ptrace_in.info.ttype = NOINFO;

  /* Initialize RPC return value structure.  */

  out_data.bytes = reg_buf;
  out_data.len = len;
  ptrace_out.info.more_data = (caddr_t) & out_data;

  /* Call RPC; take an error exit if appropriate.  */

  status = net_ptrace_clnt_call (procnum, &ptrace_in, &ptrace_out);
  if (status)
    error (rpcerr);
  if (ptrace_out.status == -1)
    {
      errno = ptrace_out.errno_num;
      sprintf (message, "reading %s registers", (procnum == PTRACE_GETREGS)
	       ? "general-purpose"
	       : "floating-point");
      perror_with_name (message);
    }
}