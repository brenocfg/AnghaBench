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
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
struct TYPE_3__ {scalar_t__ endAddr; scalar_t__ startAddr; int /*<<< orphan*/  taskId; } ;
typedef  TYPE_1__ SOURCE_STEP ;

/* Variables and functions */
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int RPC_SUCCESS ; 
 int /*<<< orphan*/  VX_SOURCE_STEP ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int net_clnt_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rpcerr ; 
 scalar_t__ step_range_end ; 
 scalar_t__ step_range_start ; 
 int /*<<< orphan*/  xdr_SOURCE_STEP ; 
 int /*<<< orphan*/  xdr_int ; 

__attribute__((used)) static int
net_step (void)
{
  enum clnt_stat status;
  int step_status;
  SOURCE_STEP source_step;

  source_step.taskId = PIDGET (inferior_ptid);

  if (step_range_end)
    {
      source_step.startAddr = step_range_start;
      source_step.endAddr = step_range_end;
    }
  else
    {
      source_step.startAddr = 0;
      source_step.endAddr = 0;
    }

  status = net_clnt_call (VX_SOURCE_STEP, xdr_SOURCE_STEP, &source_step,
			  xdr_int, &step_status);

  if (status == RPC_SUCCESS)
    return step_status;
  else
    error (rpcerr);
}