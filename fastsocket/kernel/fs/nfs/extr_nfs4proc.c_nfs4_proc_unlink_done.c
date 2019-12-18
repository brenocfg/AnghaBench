#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct nfs_removeres* rpc_resp; } ;
struct rpc_task {TYPE_1__ tk_msg; } ;
struct nfs_removeres {int /*<<< orphan*/  cinfo; int /*<<< orphan*/  server; int /*<<< orphan*/  seq_res; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  nfs4_async_handle_error (struct rpc_task*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_sequence_done (struct rpc_task*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_changeattr (struct inode*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs4_proc_unlink_done(struct rpc_task *task, struct inode *dir)
{
	struct nfs_removeres *res = task->tk_msg.rpc_resp;

	if (!nfs4_sequence_done(task, &res->seq_res))
		return 0;
	if (nfs4_async_handle_error(task, res->server, NULL) == -EAGAIN)
		return 0;
	update_changeattr(dir, &res->cinfo);
	return 1;
}