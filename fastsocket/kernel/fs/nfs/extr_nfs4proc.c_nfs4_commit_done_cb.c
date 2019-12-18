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
struct rpc_task {int dummy; } ;
struct nfs_commit_data {struct inode* inode; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  NFS_SERVER (struct inode*) ; 
 int nfs4_async_handle_error (struct rpc_task*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_restart_call_prepare (struct rpc_task*) ; 

__attribute__((used)) static int nfs4_commit_done_cb(struct rpc_task *task, struct nfs_commit_data *data)
{
	struct inode *inode = data->inode;

	if (nfs4_async_handle_error(task, NFS_SERVER(inode), NULL) == -EAGAIN) {
		rpc_restart_call_prepare(task);
		return -EAGAIN;
	}
	return 0;
}