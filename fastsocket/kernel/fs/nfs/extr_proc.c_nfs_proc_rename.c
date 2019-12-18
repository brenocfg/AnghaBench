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
struct rpc_message {struct nfs_renameargs* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct qstr {int /*<<< orphan*/  name; } ;
struct nfs_renameargs {struct qstr* new_name; int /*<<< orphan*/  new_dir; struct qstr* old_name; int /*<<< orphan*/  old_dir; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 size_t NFSPROC_RENAME ; 
 int /*<<< orphan*/  NFS_CLIENT (struct inode*) ; 
 int /*<<< orphan*/  NFS_FH (struct inode*) ; 
 int /*<<< orphan*/  dprintk (char*,int,...) ; 
 int /*<<< orphan*/  nfs_mark_for_revalidate (struct inode*) ; 
 int /*<<< orphan*/ * nfs_procedures ; 
 int rpc_call_sync (int /*<<< orphan*/ ,struct rpc_message*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs_proc_rename(struct inode *old_dir, struct qstr *old_name,
		struct inode *new_dir, struct qstr *new_name)
{
	struct nfs_renameargs	arg = {
		.old_dir	= NFS_FH(old_dir),
		.old_name	= old_name,
		.new_dir	= NFS_FH(new_dir),
		.new_name	= new_name,
	};
	struct rpc_message msg = {
		.rpc_proc	= &nfs_procedures[NFSPROC_RENAME],
		.rpc_argp	= &arg,
	};
	int			status;

	dprintk("NFS call  rename %s -> %s\n", old_name->name, new_name->name);
	status = rpc_call_sync(NFS_CLIENT(old_dir), &msg, 0);
	nfs_mark_for_revalidate(old_dir);
	nfs_mark_for_revalidate(new_dir);
	dprintk("NFS reply rename: %d\n", status);
	return status;
}