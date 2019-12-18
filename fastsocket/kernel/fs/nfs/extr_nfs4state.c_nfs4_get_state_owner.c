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
struct nfs_server {struct nfs_client* nfs_client; } ;
struct nfs_client {int /*<<< orphan*/  cl_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  wait; } ;
struct nfs4_state_owner {TYPE_1__ so_sequence; struct rpc_cred* so_cred; struct nfs_server* so_server; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_rpccred (struct rpc_cred*) ; 
 int /*<<< orphan*/  kfree (struct nfs4_state_owner*) ; 
 struct nfs4_state_owner* nfs4_alloc_state_owner () ; 
 struct nfs4_state_owner* nfs4_find_state_owner_locked (struct nfs_server*,struct rpc_cred*) ; 
 int /*<<< orphan*/  nfs4_gc_state_owners (struct nfs_server*) ; 
 struct nfs4_state_owner* nfs4_insert_state_owner_locked (struct nfs4_state_owner*) ; 
 int /*<<< orphan*/  rpc_destroy_wait_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct nfs4_state_owner *nfs4_get_state_owner(struct nfs_server *server,
					      struct rpc_cred *cred)
{
	struct nfs_client *clp = server->nfs_client;
	struct nfs4_state_owner *sp, *new;

	spin_lock(&clp->cl_lock);
	sp = nfs4_find_state_owner_locked(server, cred);
	spin_unlock(&clp->cl_lock);
	if (sp != NULL)
		goto out;
	new = nfs4_alloc_state_owner();
	if (new == NULL)
		goto out;
	new->so_server = server;
	new->so_cred = cred;
	spin_lock(&clp->cl_lock);
	sp = nfs4_insert_state_owner_locked(new);
	spin_unlock(&clp->cl_lock);
	if (sp == new)
		get_rpccred(cred);
	else {
		rpc_destroy_wait_queue(&new->so_sequence.wait);
		kfree(new);
	}
out:
	nfs4_gc_state_owners(server);
	return sp;
}