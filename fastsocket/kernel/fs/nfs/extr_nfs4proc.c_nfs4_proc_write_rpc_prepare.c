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
struct TYPE_6__ {int /*<<< orphan*/  lock_context; int /*<<< orphan*/  context; int /*<<< orphan*/  stateid; int /*<<< orphan*/  seq_args; } ;
struct TYPE_5__ {int /*<<< orphan*/  seq_res; } ;
struct nfs_write_data {TYPE_3__ args; TYPE_2__ res; TYPE_1__* header; } ;
struct TYPE_4__ {int /*<<< orphan*/  inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMODE_WRITE ; 
 int /*<<< orphan*/  NFS_SERVER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_set_rw_stateid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nfs4_setup_sequence (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct rpc_task*) ; 
 int /*<<< orphan*/  rpc_call_start (struct rpc_task*) ; 

__attribute__((used)) static void nfs4_proc_write_rpc_prepare(struct rpc_task *task, struct nfs_write_data *data)
{
	if (nfs4_setup_sequence(NFS_SERVER(data->header->inode),
				&data->args.seq_args,
				&data->res.seq_res,
				task))
		return;
	rpc_call_start(task);
	nfs4_set_rw_stateid(&data->args.stateid, data->args.context,
			data->args.lock_context, FMODE_WRITE);
}