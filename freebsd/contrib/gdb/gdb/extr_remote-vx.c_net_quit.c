#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;

/* Variables and functions */
 int PIDGET (int /*<<< orphan*/ ) ; 
 int RPC_SUCCESS ; 
 int /*<<< orphan*/  VX_TASK_SUSPEND ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int net_clnt_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  xdr_int ; 

__attribute__((used)) static int
net_quit (void)
{
  int pid;
  int quit_status;
  enum clnt_stat status;

  quit_status = 0;

  /* don't let rdbTask suspend itself by passing a pid of 0 */

  if ((pid = PIDGET (inferior_ptid)) == 0)
    return -1;

  status = net_clnt_call (VX_TASK_SUSPEND, xdr_int, &pid, xdr_int,
			  &quit_status);

  return (status == RPC_SUCCESS) ? quit_status : -1;
}