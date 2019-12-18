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
struct rpc_clnt {int dummy; } ;
struct qstr {int dummy; } ;
struct nfs_fh {int dummy; } ;
struct nfs_fattr {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 struct rpc_clnt* ERR_PTR (int) ; 
 struct rpc_clnt* NFS_CLIENT (struct inode*) ; 
 int nfs4_proc_lookup_common (struct rpc_clnt**,struct inode*,struct qstr*,struct nfs_fh*,struct nfs_fattr*) ; 
 struct rpc_clnt* rpc_clone_client (struct rpc_clnt*) ; 

struct rpc_clnt *
nfs4_proc_lookup_mountpoint(struct inode *dir, struct qstr *name,
			    struct nfs_fh *fhandle, struct nfs_fattr *fattr)
{
	struct rpc_clnt *client = NFS_CLIENT(dir);
	int status;

	status = nfs4_proc_lookup_common(&client, dir, name, fhandle, fattr);
	if (status < 0)
		return ERR_PTR(status);
	return (client == NFS_CLIENT(dir)) ? rpc_clone_client(client) : client;
}