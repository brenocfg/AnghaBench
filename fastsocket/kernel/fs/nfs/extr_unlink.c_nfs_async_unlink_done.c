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
struct rpc_task {int dummy; } ;
struct nfs_unlinkdata {struct inode* dir; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unlink_done ) (struct rpc_task*,struct inode*) ;} ;

/* Variables and functions */
 TYPE_1__* NFS_PROTO (struct inode*) ; 
 int /*<<< orphan*/  rpc_restart_call_prepare (struct rpc_task*) ; 
 int /*<<< orphan*/  stub1 (struct rpc_task*,struct inode*) ; 

__attribute__((used)) static void nfs_async_unlink_done(struct rpc_task *task, void *calldata)
{
	struct nfs_unlinkdata *data = calldata;
	struct inode *dir = data->dir;

	if (!NFS_PROTO(dir)->unlink_done(task, dir))
		rpc_restart_call_prepare(task);
}