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
struct rpc_task {scalar_t__ tk_status; } ;
struct nfs_renamedata {struct dentry* old_dentry; struct inode* new_dir; struct inode* old_dir; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* rename_done ) (struct rpc_task*,struct inode*,struct inode*) ;} ;

/* Variables and functions */
 TYPE_1__* NFS_PROTO (struct inode*) ; 
 int /*<<< orphan*/  nfs_cancel_async_unlink (struct dentry*) ; 
 int /*<<< orphan*/  rpc_restart_call_prepare (struct rpc_task*) ; 
 int /*<<< orphan*/  stub1 (struct rpc_task*,struct inode*,struct inode*) ; 

__attribute__((used)) static void nfs_async_rename_done(struct rpc_task *task, void *calldata)
{
	struct nfs_renamedata *data = calldata;
	struct inode *old_dir = data->old_dir;
	struct inode *new_dir = data->new_dir;
	struct dentry *old_dentry = data->old_dentry;

	if (!NFS_PROTO(old_dir)->rename_done(task, old_dir, new_dir)) {
		rpc_restart_call_prepare(task);
		return;
	}

	if (task->tk_status != 0)
		nfs_cancel_async_unlink(old_dentry);
}