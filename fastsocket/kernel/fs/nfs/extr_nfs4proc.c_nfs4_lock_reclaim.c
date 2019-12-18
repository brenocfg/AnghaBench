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
struct nfs4_state {int /*<<< orphan*/  flags; int /*<<< orphan*/  inode; } ;
struct nfs4_exception {scalar_t__ retry; } ;
struct file_lock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_SETLK ; 
 int NFS4ERR_DELAY ; 
 int /*<<< orphan*/  NFS_DELEGATED_STATE ; 
 int /*<<< orphan*/  NFS_LOCK_RECLAIM ; 
 struct nfs_server* NFS_SERVER (int /*<<< orphan*/ ) ; 
 int _nfs4_do_setlk (struct nfs4_state*,int /*<<< orphan*/ ,struct file_lock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_handle_exception (struct nfs_server*,int,struct nfs4_exception*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs4_lock_reclaim(struct nfs4_state *state, struct file_lock *request)
{
	struct nfs_server *server = NFS_SERVER(state->inode);
	struct nfs4_exception exception = { };
	int err;

	do {
		/* Cache the lock if possible... */
		if (test_bit(NFS_DELEGATED_STATE, &state->flags) != 0)
			return 0;
		err = _nfs4_do_setlk(state, F_SETLK, request, NFS_LOCK_RECLAIM);
		if (err != -NFS4ERR_DELAY)
			break;
		nfs4_handle_exception(server, err, &exception);
	} while (exception.retry);
	return err;
}