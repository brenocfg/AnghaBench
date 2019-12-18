#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
struct TYPE_4__ {scalar_t__ status; } ;
typedef  TYPE_1__ RDB_EVENT ;

/* Variables and functions */
 int PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROCESS_WAIT ; 
 int RPC_SUCCESS ; 
 int RPC_TIMEDOUT ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int net_clnt_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  xdr_RDB_EVENT ; 
 int /*<<< orphan*/  xdr_int ; 

__attribute__((used)) static int
net_wait (RDB_EVENT *pEvent)
{
  int pid;
  enum clnt_stat status;

  memset ((char *) pEvent, '\0', sizeof (RDB_EVENT));

  pid = PIDGET (inferior_ptid);
  status = net_clnt_call (PROCESS_WAIT, xdr_int, &pid, xdr_RDB_EVENT,
			  pEvent);

  /* return (status == RPC_SUCCESS)? pEvent->status: -1; */
  if (status == RPC_SUCCESS)
    return ((pEvent->status) ? 1 : 0);
  else if (status == RPC_TIMEDOUT)
    return (1);
  else
    return (-1);
}