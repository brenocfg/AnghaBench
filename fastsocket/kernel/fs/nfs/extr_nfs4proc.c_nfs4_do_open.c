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
struct rpc_cred {int dummy; } ;
struct nfs_server {TYPE_1__* nfs_client; } ;
struct nfs4_state {int dummy; } ;
struct nfs4_exception {int retry; } ;
struct inode {int dummy; } ;
struct iattr {int dummy; } ;
struct dentry {int dummy; } ;
typedef  int fmode_t ;
struct TYPE_2__ {int /*<<< orphan*/  cl_hostname; } ;

/* Variables and functions */
 int EAGAIN ; 
 struct nfs4_state* ERR_PTR (int /*<<< orphan*/ ) ; 
 int FMODE_EXEC ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int NFS4ERR_BAD_SEQID ; 
 int NFS4ERR_BAD_STATEID ; 
 struct nfs_server* NFS_SERVER (struct inode*) ; 
 int _nfs4_do_open (struct inode*,struct dentry*,int,int,struct iattr*,struct rpc_cred*,struct nfs4_state**) ; 
 scalar_t__ nfs4_clear_cap_atomic_open_v1 (struct nfs_server*,int,struct nfs4_exception*) ; 
 int /*<<< orphan*/  nfs4_handle_exception (struct nfs_server*,int,struct nfs4_exception*) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nfs4_state *nfs4_do_open(struct inode *dir, struct dentry *dentry, fmode_t fmode, int flags, struct iattr *sattr, struct rpc_cred *cred)
{
	struct nfs_server *server = NFS_SERVER(dir);
	struct nfs4_exception exception = { };
	struct nfs4_state *res;
	int status;

	fmode &= FMODE_READ|FMODE_WRITE|FMODE_EXEC;
	do {
		status = _nfs4_do_open(dir, dentry, fmode, flags, sattr, cred, &res);
		if (status == 0)
			break;
		/* NOTE: BAD_SEQID means the server and client disagree about the
		 * book-keeping w.r.t. state-changing operations
		 * (OPEN/CLOSE/LOCK/LOCKU...)
		 * It is actually a sign of a bug on the client or on the server.
		 *
		 * If we receive a BAD_SEQID error in the particular case of
		 * doing an OPEN, we assume that nfs_increment_open_seqid() will
		 * have unhashed the old state_owner for us, and that we can
		 * therefore safely retry using a new one. We should still warn
		 * the user though...
		 */
		if (status == -NFS4ERR_BAD_SEQID) {
			pr_warn_ratelimited("NFS: v4 server %s "
					" returned a bad sequence-id error!\n",
					NFS_SERVER(dir)->nfs_client->cl_hostname);
			exception.retry = 1;
			continue;
		}
		/*
		 * BAD_STATEID on OPEN means that the server cancelled our
		 * state before it received the OPEN_CONFIRM.
		 * Recover by retrying the request as per the discussion
		 * on Page 181 of RFC3530.
		 */
		if (status == -NFS4ERR_BAD_STATEID) {
			exception.retry = 1;
			continue;
		}
		if (status == -EAGAIN) {
			/* We must have found a delegation */
			exception.retry = 1;
			continue;
		}
		if (nfs4_clear_cap_atomic_open_v1(server, status, &exception))
			continue;
		res = ERR_PTR(nfs4_handle_exception(server,
					status, &exception));
	} while (exception.retry);
	return res;
}