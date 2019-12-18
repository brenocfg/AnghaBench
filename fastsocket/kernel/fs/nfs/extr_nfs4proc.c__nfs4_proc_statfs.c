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
struct rpc_message {struct nfs4_statfs_res* rpc_resp; struct nfs4_statfs_arg* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct nfs_server {int /*<<< orphan*/  client; int /*<<< orphan*/  attr_bitmask; } ;
struct nfs_fsstat {int /*<<< orphan*/  fattr; } ;
struct nfs_fh {int dummy; } ;
struct nfs4_statfs_res {int /*<<< orphan*/  seq_res; struct nfs_fsstat* fsstat; } ;
struct nfs4_statfs_arg {int /*<<< orphan*/  seq_args; int /*<<< orphan*/  bitmask; struct nfs_fh* fh; } ;

/* Variables and functions */
 size_t NFSPROC4_CLNT_STATFS ; 
 int nfs4_call_sync (int /*<<< orphan*/ ,struct nfs_server*,struct rpc_message*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nfs4_procedures ; 
 int /*<<< orphan*/  nfs_fattr_init (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _nfs4_proc_statfs(struct nfs_server *server, struct nfs_fh *fhandle,
		 struct nfs_fsstat *fsstat)
{
	struct nfs4_statfs_arg args = {
		.fh = fhandle,
		.bitmask = server->attr_bitmask,
	};
	struct nfs4_statfs_res res = {
		.fsstat = fsstat,
	};
	struct rpc_message msg = {
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_STATFS],
		.rpc_argp = &args,
		.rpc_resp = &res,
	};

	nfs_fattr_init(fsstat->fattr);
	return  nfs4_call_sync(server->client, server, &msg, &args.seq_args, &res.seq_res, 0);
}