#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rpc_task {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  seq_res; } ;
struct TYPE_5__ {int /*<<< orphan*/  seq_args; } ;
struct nfs_commit_data {TYPE_3__ res; TYPE_2__ args; TYPE_1__* ds_clp; } ;
struct TYPE_4__ {int /*<<< orphan*/  cl_session; } ;

/* Variables and functions */
 scalar_t__ nfs41_setup_sequence (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct rpc_task*) ; 
 int /*<<< orphan*/  rpc_call_start (struct rpc_task*) ; 

__attribute__((used)) static void filelayout_commit_prepare(struct rpc_task *task, void *data)
{
	struct nfs_commit_data *wdata = data;

	if (nfs41_setup_sequence(wdata->ds_clp->cl_session,
				&wdata->args.seq_args, &wdata->res.seq_res,
				task))
		return;

	rpc_call_start(task);
}