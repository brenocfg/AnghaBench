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
struct rpc_inode {scalar_t__ nkern_readwriters; } ;
struct inode {int dummy; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 struct rpc_inode* RPC_I (struct inode*) ; 
 int __rpc_unlink (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  rpc_close_pipes (struct inode*) ; 

__attribute__((used)) static int __rpc_rmpipe(struct inode *dir, struct dentry *dentry)
{
	struct inode *inode = dentry->d_inode;
	struct rpc_inode *rpci = RPC_I(inode);

	rpci->nkern_readwriters--;
	if (rpci->nkern_readwriters != 0)
		return 0;
	rpc_close_pipes(inode);
	return __rpc_unlink(dir, dentry);
}