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
struct target_ops {int dummy; } ;
struct mem_attrib {int dummy; } ;
typedef  int /*<<< orphan*/  ptrace_out ;
typedef  int /*<<< orphan*/  ptrace_in ;
typedef  enum ptracereq { ____Placeholder_ptracereq } ptracereq ;
typedef  void* caddr_t ;
struct TYPE_12__ {int len; void* bytes; } ;
struct TYPE_9__ {void* more_data; } ;
struct TYPE_11__ {int status; int /*<<< orphan*/  errno_num; TYPE_2__ info; } ;
struct TYPE_8__ {void* more_data; int /*<<< orphan*/  ttype; } ;
struct TYPE_10__ {int addr; int data; TYPE_1__ info; int /*<<< orphan*/  pid; } ;
typedef  TYPE_3__ Rptrace ;
typedef  TYPE_4__ Ptrace_return ;
typedef  TYPE_5__ C_bytes ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int PTRACE_READDATA ; 
 int PTRACE_WRITEDATA ; 
 int /*<<< orphan*/  VX_MEMXFER_MAX ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 scalar_t__ net_ptrace_clnt_call (int,TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  rpcerr ; 

__attribute__((used)) static int
vx_xfer_memory (CORE_ADDR memaddr, char *myaddr, int len, int write,
		struct mem_attrib *attrib, struct target_ops *target)
{
  int status;
  Rptrace ptrace_in;
  Ptrace_return ptrace_out;
  C_bytes data;
  enum ptracereq request;
  int nleft, nxfer;

  memset ((char *) &ptrace_in, '\0', sizeof (ptrace_in));
  memset ((char *) &ptrace_out, '\0', sizeof (ptrace_out));

  ptrace_in.pid = PIDGET (inferior_ptid); /* XXX pid unnecessary for READDATA */
  ptrace_in.addr = (int) memaddr;	/* Where from */
  ptrace_in.data = len;		/* How many bytes */

  if (write)
    {
      ptrace_in.info.ttype = DATA;
      ptrace_in.info.more_data = (caddr_t) & data;

      data.bytes = (caddr_t) myaddr;	/* Where from */
      data.len = len;		/* How many bytes (again, for XDR) */
      request = PTRACE_WRITEDATA;
    }
  else
    {
      ptrace_out.info.more_data = (caddr_t) & data;
      request = PTRACE_READDATA;
    }
  /* Loop until the entire request has been satisfied, transferring
     at most VX_MEMXFER_MAX bytes per iteration.  Break from the loop
     if an error status is returned by the remote debug server.  */

  nleft = len;
  status = 0;

  while (nleft > 0 && status == 0)
    {
      nxfer = min (nleft, VX_MEMXFER_MAX);

      ptrace_in.addr = (int) memaddr;
      ptrace_in.data = nxfer;
      data.bytes = (caddr_t) myaddr;
      data.len = nxfer;

      /* Request a block from the remote debug server; if RPC fails,
         report an error and return to debugger command level.  */

      if (net_ptrace_clnt_call (request, &ptrace_in, &ptrace_out))
	error (rpcerr);

      status = ptrace_out.status;
      if (status == 0)
	{
	  memaddr += nxfer;
	  myaddr += nxfer;
	  nleft -= nxfer;
	}
      else
	{
	  /* A target-side error has ocurred.  Set errno to the error
	     code chosen by the target so that a later perror () will
	     say something meaningful.  */

	  errno = ptrace_out.errno_num;
	}
    }

  /* Return the number of bytes transferred.  */

  return (len - nleft);
}