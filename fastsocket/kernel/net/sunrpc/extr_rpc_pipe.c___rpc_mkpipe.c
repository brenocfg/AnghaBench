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
typedef  int umode_t ;
struct rpc_pipe_ops {int dummy; } ;
struct rpc_inode {int nkern_readwriters; int flags; struct rpc_pipe_ops const* ops; void* private; } ;
struct inode {int dummy; } ;
struct file_operations {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 struct rpc_inode* RPC_I (int /*<<< orphan*/ ) ; 
 int S_IFIFO ; 
 int __rpc_create_common (struct inode*,struct dentry*,int,struct file_operations const*,void*) ; 
 int /*<<< orphan*/  fsnotify_create (struct inode*,struct dentry*) ; 

__attribute__((used)) static int __rpc_mkpipe(struct inode *dir, struct dentry *dentry,
			umode_t mode,
			const struct file_operations *i_fop,
			void *private,
			const struct rpc_pipe_ops *ops,
			int flags)
{
	struct rpc_inode *rpci;
	int err;

	err = __rpc_create_common(dir, dentry, S_IFIFO | mode, i_fop, private);
	if (err)
		return err;
	rpci = RPC_I(dentry->d_inode);
	rpci->nkern_readwriters = 1;
	rpci->private = private;
	rpci->flags = flags;
	rpci->ops = ops;
	fsnotify_create(dir, dentry);
	return 0;
}