#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rpc_task {TYPE_2__* tk_client; scalar_t__ tk_status; int /*<<< orphan*/  tk_action; } ;
struct TYPE_4__ {TYPE_1__* cl_stats; } ;
struct TYPE_3__ {int /*<<< orphan*/  rpcauthrefresh; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_refreshresult ; 
 int /*<<< orphan*/  dprint_status (struct rpc_task*) ; 
 int /*<<< orphan*/  rpcauth_refreshcred (struct rpc_task*) ; 

__attribute__((used)) static void
call_refresh(struct rpc_task *task)
{
	dprint_status(task);

	task->tk_action = call_refreshresult;
	task->tk_status = 0;
	task->tk_client->cl_stats->rpcauthrefresh++;
	rpcauth_refreshcred(task);
}