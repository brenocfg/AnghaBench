#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rpc_message {struct nfs4_secinfo_res* rpc_resp; struct nfs4_secinfo_arg* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct qstr {int name; } ;
struct nfs4_secinfo_res {int /*<<< orphan*/  seq_res; struct nfs4_secinfo_flavors* flavors; } ;
struct nfs4_secinfo_flavors {int dummy; } ;
struct nfs4_secinfo_arg {int /*<<< orphan*/  seq_args; struct qstr const* name; int /*<<< orphan*/  dir_fh; } ;
struct inode {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 size_t NFSPROC4_CLNT_SECINFO ; 
 int /*<<< orphan*/  NFS_FH (struct inode*) ; 
 TYPE_1__* NFS_SERVER (struct inode*) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int nfs4_call_sync (int /*<<< orphan*/ ,TYPE_1__*,struct rpc_message*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nfs4_procedures ; 

__attribute__((used)) static int _nfs4_proc_secinfo(struct inode *dir, const struct qstr *name, struct nfs4_secinfo_flavors *flavors)
{
	int status;
	struct nfs4_secinfo_arg args = {
		.dir_fh = NFS_FH(dir),
		.name   = name,
	};
	struct nfs4_secinfo_res res = {
		.flavors     = flavors,
	};
	struct rpc_message msg = {
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_SECINFO],
		.rpc_argp = &args,
		.rpc_resp = &res,
	};

	dprintk("NFS call  secinfo %s\n", name->name);
	status = nfs4_call_sync(NFS_SERVER(dir)->client, NFS_SERVER(dir), &msg, &args.seq_args, &res.seq_res, 0);
	dprintk("NFS reply  secinfo: %d\n", status);
	return status;
}