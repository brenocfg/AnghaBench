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
struct rpc_message {struct nfs4_lookup_res* rpc_resp; struct nfs4_lookup_root_arg* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct nfs_server {int /*<<< orphan*/  client; } ;
struct nfs_fsinfo {int /*<<< orphan*/  fattr; } ;
struct nfs_fh {int dummy; } ;
struct nfs4_lookup_root_arg {int /*<<< orphan*/  seq_args; int /*<<< orphan*/  bitmask; } ;
struct nfs4_lookup_res {int /*<<< orphan*/  seq_res; struct nfs_fh* fh; int /*<<< orphan*/  fattr; struct nfs_server* server; } ;

/* Variables and functions */
 size_t NFSPROC4_CLNT_LOOKUP_ROOT ; 
 int nfs4_call_sync (int /*<<< orphan*/ ,struct nfs_server*,struct rpc_message*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_fattr_bitmap ; 
 int /*<<< orphan*/ * nfs4_procedures ; 
 int /*<<< orphan*/  nfs_fattr_init (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _nfs4_lookup_root(struct nfs_server *server, struct nfs_fh *fhandle,
		struct nfs_fsinfo *info)
{
	struct nfs4_lookup_root_arg args = {
		.bitmask = nfs4_fattr_bitmap,
	};
	struct nfs4_lookup_res res = {
		.server = server,
		.fattr = info->fattr,
		.fh = fhandle,
	};
	struct rpc_message msg = {
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_LOOKUP_ROOT],
		.rpc_argp = &args,
		.rpc_resp = &res,
	};

	nfs_fattr_init(info->fattr);
	return nfs4_call_sync(server->client, server, &msg, &args.seq_args, &res.seq_res, 0);
}