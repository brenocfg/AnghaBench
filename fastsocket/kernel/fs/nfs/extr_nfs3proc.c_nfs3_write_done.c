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
struct rpc_task {scalar_t__ tk_status; } ;
struct TYPE_4__ {int /*<<< orphan*/  fattr; } ;
struct nfs_write_data {TYPE_2__ res; TYPE_1__* header; } ;
struct inode {int dummy; } ;
struct TYPE_3__ {struct inode* inode; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ nfs3_async_handle_jukebox (struct rpc_task*,struct inode*) ; 
 int /*<<< orphan*/  nfs_post_op_update_inode_force_wcc (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfs3_write_done(struct rpc_task *task, struct nfs_write_data *data)
{
	struct inode *inode = data->header->inode;

	if (nfs3_async_handle_jukebox(task, inode))
		return -EAGAIN;
	if (task->tk_status >= 0)
		nfs_post_op_update_inode_force_wcc(inode, data->res.fattr);
	return 0;
}