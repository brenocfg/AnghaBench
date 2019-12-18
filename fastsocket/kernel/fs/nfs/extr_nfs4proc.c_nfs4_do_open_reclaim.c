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
struct nfs_server {int dummy; } ;
struct nfs_open_context {int dummy; } ;
struct nfs4_state {int /*<<< orphan*/  inode; } ;
struct nfs4_exception {scalar_t__ retry; } ;

/* Variables and functions */
 int NFS4ERR_DELAY ; 
 struct nfs_server* NFS_SERVER (int /*<<< orphan*/ ) ; 
 int _nfs4_do_open_reclaim (struct nfs_open_context*,struct nfs4_state*) ; 
 scalar_t__ nfs4_clear_cap_atomic_open_v1 (struct nfs_server*,int,struct nfs4_exception*) ; 
 int /*<<< orphan*/  nfs4_handle_exception (struct nfs_server*,int,struct nfs4_exception*) ; 

__attribute__((used)) static int nfs4_do_open_reclaim(struct nfs_open_context *ctx, struct nfs4_state *state)
{
	struct nfs_server *server = NFS_SERVER(state->inode);
	struct nfs4_exception exception = { };
	int err;
	do {
		err = _nfs4_do_open_reclaim(ctx, state);
		if (nfs4_clear_cap_atomic_open_v1(server, err, &exception))
			continue;
		if (err != -NFS4ERR_DELAY)
			break;
		nfs4_handle_exception(server, err, &exception);
	} while (exception.retry);
	return err;
}