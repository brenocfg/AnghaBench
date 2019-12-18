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
struct rpc_call_ops {int dummy; } ;
struct nfs_write_data {TYPE_1__* header; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {struct inode* inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_CLIENT (struct inode*) ; 
 int nfs_initiate_write (int /*<<< orphan*/ ,struct nfs_write_data*,struct rpc_call_ops const*,int) ; 

__attribute__((used)) static int nfs_do_write(struct nfs_write_data *data,
		const struct rpc_call_ops *call_ops,
		int how)
{
	struct inode *inode = data->header->inode;

	return nfs_initiate_write(NFS_CLIENT(inode), data, call_ops, how);
}