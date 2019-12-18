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
struct rpc_message {struct rpc_cred* rpc_cred; struct nfs_setattrres* rpc_resp; struct nfs_setattrargs* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct rpc_cred {int dummy; } ;
struct nfs_setattrres {int /*<<< orphan*/  seq_res; struct nfs_server* server; struct nfs_fattr* fattr; } ;
struct nfs_setattrargs {int /*<<< orphan*/  seq_args; int /*<<< orphan*/  stateid; int /*<<< orphan*/  bitmask; struct nfs_server* server; struct iattr* iap; int /*<<< orphan*/  fh; } ;
struct nfs_server {int /*<<< orphan*/  client; int /*<<< orphan*/  attr_bitmask; } ;
struct nfs_lockowner {int /*<<< orphan*/  l_pid; int /*<<< orphan*/  l_owner; } ;
struct nfs_fattr {int dummy; } ;
struct nfs4_state {int dummy; } ;
struct inode {int dummy; } ;
struct iattr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tgid; int /*<<< orphan*/  files; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMODE_WRITE ; 
 size_t NFSPROC4_CLNT_SETATTR ; 
 int /*<<< orphan*/  NFS_FH (struct inode*) ; 
 struct nfs_server* NFS_SERVER (struct inode*) ; 
 TYPE_1__* current ; 
 unsigned long jiffies ; 
 int nfs4_call_sync (int /*<<< orphan*/ ,struct nfs_server*,struct rpc_message*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ nfs4_copy_delegation_stateid (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nfs4_procedures ; 
 int /*<<< orphan*/  nfs4_select_rw_stateid (int /*<<< orphan*/ *,struct nfs4_state*,int /*<<< orphan*/ ,struct nfs_lockowner*) ; 
 int /*<<< orphan*/  nfs4_stateid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ nfs4_valid_open_stateid (struct nfs4_state*) ; 
 int /*<<< orphan*/  nfs_fattr_init (struct nfs_fattr*) ; 
 int /*<<< orphan*/  renew_lease (struct nfs_server*,unsigned long) ; 
 int /*<<< orphan*/  zero_stateid ; 

__attribute__((used)) static int _nfs4_do_setattr(struct inode *inode, struct rpc_cred *cred,
			    struct nfs_fattr *fattr, struct iattr *sattr,
			    struct nfs4_state *state)
{
	struct nfs_server *server = NFS_SERVER(inode);
        struct nfs_setattrargs  arg = {
                .fh             = NFS_FH(inode),
                .iap            = sattr,
		.server		= server,
		.bitmask = server->attr_bitmask,
        };
        struct nfs_setattrres  res = {
		.fattr		= fattr,
		.server		= server,
        };
        struct rpc_message msg = {
		.rpc_proc	= &nfs4_procedures[NFSPROC4_CLNT_SETATTR],
		.rpc_argp	= &arg,
		.rpc_resp	= &res,
		.rpc_cred	= cred,
        };
	unsigned long timestamp = jiffies;
	int status;

	nfs_fattr_init(fattr);

	if (state != NULL && nfs4_valid_open_stateid(state)) {
		struct nfs_lockowner lockowner = {
			.l_owner = current->files,
			.l_pid = current->tgid,
		};
		nfs4_select_rw_stateid(&arg.stateid, state, FMODE_WRITE,
				&lockowner);
	} else if (nfs4_copy_delegation_stateid(&arg.stateid, inode,
				FMODE_WRITE)) {
		/* Use that stateid */
	} else
		nfs4_stateid_copy(&arg.stateid, &zero_stateid);

	status = nfs4_call_sync(server->client, server, &msg, &arg.seq_args, &res.seq_res, 1);
	if (status == 0 && state != NULL)
		renew_lease(server, timestamp);
	return status;
}