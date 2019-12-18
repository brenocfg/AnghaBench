#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rpc_task {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock_context; TYPE_4__* context; int /*<<< orphan*/  stateid; int /*<<< orphan*/  seq_args; } ;
struct TYPE_6__ {int /*<<< orphan*/  seq_res; } ;
struct nfs_read_data {TYPE_3__ args; TYPE_2__ res; TYPE_1__* ds_clp; int /*<<< orphan*/  read_done_cb; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  cl_session; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  FMODE_READ ; 
 int /*<<< orphan*/  NFS_CONTEXT_BAD ; 
 int /*<<< orphan*/  filelayout_read_done_cb ; 
 scalar_t__ nfs41_setup_sequence (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct rpc_task*) ; 
 int /*<<< orphan*/  nfs4_set_rw_stateid (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_call_start (struct rpc_task*) ; 
 int /*<<< orphan*/  rpc_exit (struct rpc_task*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void filelayout_read_prepare(struct rpc_task *task, void *data)
{
	struct nfs_read_data *rdata = data;

	if (unlikely(test_bit(NFS_CONTEXT_BAD, &rdata->args.context->flags))) {
		rpc_exit(task, -EIO);
		return;
	}
	rdata->read_done_cb = filelayout_read_done_cb;

	if (nfs41_setup_sequence(rdata->ds_clp->cl_session,
				&rdata->args.seq_args, &rdata->res.seq_res,
				task))
		return;

	rpc_call_start(task);
	nfs4_set_rw_stateid(&rdata->args.stateid, rdata->args.context,
			rdata->args.lock_context, FMODE_READ);
}