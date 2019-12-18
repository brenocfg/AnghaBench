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
struct nfs_removeres {int /*<<< orphan*/  dir_attr; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 scalar_t__ nfs3_async_handle_jukebox (struct rpc_task*,struct inode*) ; 
 int /*<<< orphan*/  nfs_post_op_update_inode (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs3_proc_unlink_done(struct rpc_task *task, struct inode *dir)
{
	struct nfs_removeres *res;
	if (nfs3_async_handle_jukebox(task, dir))
		return 0;
	res = task->tk_msg.rpc_resp;
	nfs_post_op_update_inode(dir, res->dir_attr);
	return 1;
}