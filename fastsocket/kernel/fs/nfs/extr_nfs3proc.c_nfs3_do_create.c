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
struct TYPE_2__ {int /*<<< orphan*/  fattr; int /*<<< orphan*/  fh; int /*<<< orphan*/  dir_attr; } ;
struct nfs3_createdata {TYPE_1__ res; int /*<<< orphan*/  msg; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_CLIENT (struct inode*) ; 
 int nfs_instantiate (struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_post_op_update_inode (struct inode*,int /*<<< orphan*/ ) ; 
 int rpc_call_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfs3_do_create(struct inode *dir, struct dentry *dentry, struct nfs3_createdata *data)
{
	int status;

	status = rpc_call_sync(NFS_CLIENT(dir), &data->msg, 0);
	nfs_post_op_update_inode(dir, data->res.dir_attr);
	if (status == 0)
		status = nfs_instantiate(dentry, data->res.fh, data->res.fattr);
	return status;
}