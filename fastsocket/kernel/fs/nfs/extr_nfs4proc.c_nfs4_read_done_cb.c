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
struct rpc_task {scalar_t__ tk_status; } ;
struct nfs_server {int dummy; } ;
struct TYPE_6__ {TYPE_2__* context; } ;
struct nfs_read_data {int /*<<< orphan*/  timestamp; TYPE_3__ args; TYPE_1__* header; } ;
struct TYPE_5__ {int /*<<< orphan*/  state; } ;
struct TYPE_4__ {int /*<<< orphan*/  inode; } ;

/* Variables and functions */
 int EAGAIN ; 
 struct nfs_server* NFS_SERVER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __nfs4_read_done_cb (struct nfs_read_data*) ; 
 int nfs4_async_handle_error (struct rpc_task*,struct nfs_server*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  renew_lease (struct nfs_server*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_restart_call_prepare (struct rpc_task*) ; 

__attribute__((used)) static int nfs4_read_done_cb(struct rpc_task *task, struct nfs_read_data *data)
{
	struct nfs_server *server = NFS_SERVER(data->header->inode);

	if (nfs4_async_handle_error(task, server, data->args.context->state) == -EAGAIN) {
		rpc_restart_call_prepare(task);
		return -EAGAIN;
	}

	__nfs4_read_done_cb(data);
	if (task->tk_status > 0)
		renew_lease(server, data->timestamp);
	return 0;
}